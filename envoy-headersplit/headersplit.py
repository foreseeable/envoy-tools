# Lint as: python3
"""TODO(mugechen): DO NOT SUBMIT without one-line documentation for headersplit.

TODO(mugechen): DO NOT SUBMIT without a detailed description of headersplit.
"""


from __future__ import print_function
from ctypes import c_uint, c_int

import argparse

import clang.cindex
from clang.cindex import Type, TranslationUnit, Index, CursorKind

import cymbal

# TODO: fix the hard coded path
clang.cindex.Config.set_library_path("/opt/llvm/lib")

cymbal.monkeypatch_type('get_template_argument_type',
                        'clang_Type_getTemplateArgumentAsType',
                        [Type, c_uint],
                        Type)

cymbal.monkeypatch_type('get_num_template_arguments',
                        'clang_Type_getNumTemplateArguments',
                        [Type],
                        c_int)


# check if the cursor's type is a template
def is_template(node):
    return hasattr(node, 'type') and node.type.get_num_template_arguments() != -1


def get_headers(translation_unit):
    cursor = translation_unit.cursor
    for i in cursor.walk_preorder():
        if i.location.file is not None and i.location.file.name == cursor.displayname:
            filename = i.location.file.name
            with open(filename, 'r') as fh:
                contents = fh.read()
            headers = contents[:i.extent.start.offset]
            return headers

    return ""


def class_definitions(cursor):
    class_cursors = []
    for i in cursor.walk_preorder():
        if i.location.file is None:
            continue
        if i.location.file.name != cursor.displayname:
            continue
        if i.kind != CursorKind.CLASS_DECL:
            continue
        if not i.is_definition():
            continue
        if i.semantic_parent.kind != CursorKind.NAMESPACE:
            continue
        class_cursors.append(i)
    return class_cursors


def class_implementations(cursor):
    #print(cursor.displayname)
    flag = False
    for i in cursor.walk_preorder():
        if i.location.file is None:
            continue
        if i.location.file.name != cursor.displayname:
            continue

        if i.kind != CursorKind.NAMESPACE and i.semantic_parent is not None and i.semantic_parent.kind == CursorKind.CLASS_DECL:
            yield i


def extract_definition(cursor, fullclassnames):
    filename = cursor.location.file.name
    with open(filename, 'r') as fh:
        contents = fh.read()
    class_name = cursor.spelling
    class_defn = contents[cursor.extent.start.offset:cursor.extent.end.offset]+";"
    # need to know enclosed semantic parents
    #print(cursor.spelling)
    pc = cursor.semantic_parent
    while pc.kind == CursorKind.NAMESPACE:
        if pc.spelling == "":
            break
        class_defn = "namespace {} {{\n".format(
            pc.spelling) + class_defn + "\n}\n"
        pc = pc.semantic_parent
    #resolve dependency

    deps = set()
    for i in cursor.walk_preorder():
        if i.kind == CursorKind.CXX_BASE_SPECIFIER or i.kind == CursorKind.TYPE_REF:
            if i.spelling in fullclassnames:
                depname = i.spelling.split(':')[-1]
                if depname != class_name:
                    deps.add(depname)

    return class_name, class_defn, deps


def extract_implementation(cursor):
    filename = cursor.location.file.name
    with open(filename, 'r') as fh:
        contents = fh.readlines()
    class_name = cursor.semantic_parent.spelling
    return class_name, "".join(contents[cursor.extent.start.line-1:cursor.extent.end.
                                        line])


"""
TODO: resolve class dependency issues
TODO: resolve over-inclusion issues
TODO: formatting 
"""


def main(args):
    decl_filename = args["decl"]
    impl_filename = args["impl"]
    idx = Index.create()

    source_translation_unit = TranslationUnit.from_source(
        decl_filename
    )

    impl_translation_unit = TranslationUnit.from_source(
        impl_filename
    )

    decl_includes = get_headers(source_translation_unit)
    impl_includes = get_headers(impl_translation_unit)

    tu = idx.parse(decl_filename, ['-x', 'c++'])
    defns = class_definitions(tu.cursor)

    impls = class_implementations(impl_translation_unit.cursor)

    classname_to_impl = dict()

    for cursor in impls:
        classname, impl = extract_implementation(cursor)
        try:
            classname_to_impl[classname] += impl + "\n"
        except:
            classname_to_impl[classname] = impl + "\n"

    classnames = [cursor.spelling for cursor in defns]
    fullclassnames = []
    for cursor in defns:
        classname = cursor.spelling

        pc = cursor.semantic_parent
        while pc.kind == CursorKind.NAMESPACE:
            if pc.spelling == "":
                break
            classname = pc.spelling + "::"+classname
            pc = pc.semantic_parent

        fullclassname = "class "+classname
        fullclassnames.append(fullclassname)
    for defn in defns:
        #print("---")
        #print(extract_definition(defn))
        class_name, class_defn, deps = extract_definition(defn, fullclassnames)
        #print(deps)
        includes = ""
        for name in classnames:
            includes += '#include "{}.h"\n'.format(name)
        class_impl = ""
        try:
            impl_includes = impl_includes.replace(decl_filename, '{}.h'.format(class_name))
            namespace_prefix = ""
            namespace_suffix = ""
            pc = defn.semantic_parent
            while pc.kind == CursorKind.NAMESPACE:
                if pc.spelling == "":
                    break
                namespace_prefix += "namespace {} {{\n".format(
                    pc.spelling)
                namespace_suffix += "\n}\n"
                pc = pc.semantic_parent
            class_impl = impl_includes + namespace_prefix + \
                classname_to_impl[class_name] + namespace_suffix

        except:
            print("Warning: empty class {}".format(class_name))
            class_impl = ""
        with open("mockclass/{}.h".format(class_name), "w") as f:
            f.write(decl_includes+includes+class_defn)
        with open("mockclass/{}.cc".format(class_name), "w") as f:
            f.write(class_impl)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '-d', '--decl', default='mocks.h',
        help="Path to the monolith header .h file that needs to be splitted",
    )
    parser.add_argument(
        '-i', '--impl', default='mocks.cc',
        help="Path to the impl code .cc file that needs to be splitted",
    )
    main(vars(parser.parse_args()))
