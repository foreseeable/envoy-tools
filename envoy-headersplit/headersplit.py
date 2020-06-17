# Lint as: python3
"""TODO(mugechen): DO NOT SUBMIT without one-line documentation for headersplit.

TODO(mugechen): DO NOT SUBMIT without a detailed description of headersplit.
"""


from __future__ import print_function

import argparse

import clang.cindex
from clang.cindex import *
# TODO: fix the hard coded path
clang.cindex.Config.set_library_path("/opt/llvm/lib")


def get_headers(translation_unit):
    cursor = translation_unit.cursor
    for i in cursor.walk_preorder():
        if i.location.file!=None and i.location.file.name == cursor.displayname:
            filename = i.location.file.name
            with open(filename, 'r') as fh:
                contents = fh.read()
            headers = contents[:i.extent.start.offset]
            return headers

    return ""


def class_definitions(cursor):
    for i in cursor.walk_preorder():
        if i.kind != CursorKind.CLASS_DECL:
            continue
        if not i.is_definition():
            continue
        if i.semantic_parent.kind!=CursorKind.NAMESPACE:
            continue
        yield i


#def class_implementations(cursor):
#    for i in cursor.walk_preorder():
#        if i.kind != CursorKind.CLASS_DECL:
#            continue
#        print(i.location.file.name)
#        yield i
#


def extract_definition(cursor):
    filename = cursor.location.file.name
    with open(filename, 'r') as fh:
        contents = fh.read()
    class_name = cursor.spelling
    class_defn = contents[cursor.extent.start.offset:cursor.extent.end.offset]+";"
    # need to know enclosed semantic parents
    #print(cursor.spelling)
    pc = cursor.semantic_parent
    print(pc.kind,pc.spelling)
    while pc.kind == CursorKind.NAMESPACE:
        if pc.spelling == "":
            break
        class_defn = "namespace {} {{\n".format(pc.spelling) + class_defn + "\n}\n"
        pc = pc.semantic_parent
    return class_name, class_defn


#def extract_implementation(cursor):
#    filename = cursor.location.file.name
#    with open(filename, 'r') as fh:
#        contents = fh.read()
#    impl_name = cursor.spelling
#    print(filename)
#    print(impl_name)
#    print(contents[cursor.extent.start.offset:cursor.extent.end.offset])
#    return impl_name, contents[cursor.extent.start.offset:cursor.extent.end.
#                               offset]
#


"""
TODO: resolve class dependency issues
TODO: resolve over-inclusion issues
TODO: formatting 
"""

def main(args):
  idx = Index.create()
  source_translation_unit = TranslationUnit.from_source(
      "mocks.h"
  )

  decl_includes = get_headers(source_translation_unit)
  tu = idx.parse('mocks.h', ['-x', 'c++'])
  defns = class_definitions(tu.cursor)
  #idx2 = Index.create()
  #tu2 = idx2.parse('mocks.cc', ['-x', 'c++'])
  #impls = class_implementations(tu2.cursor)

  classname_to_impl = dict()

  #for impl in impls:
  #    classname, impl = extract_implementation(impl)
  #    try:
  #        classname_to_impl[classname] += impl
  #    except:
  #        classname_to_impl[classname] = impl
  for defn in defns:
      print("---")
      #print(extract_definition(defn))
      class_name,class_defn = extract_definition(defn)
      with open("mockclass/{}.h".format(class_name),"w") as f:
        f.write(decl_includes+class_defn)
      

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  main(vars(parser.parse_args()))

  
