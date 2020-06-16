# Lint as: python3
"""TODO(mugechen): DO NOT SUBMIT without one-line documentation for headersplit.

TODO(mugechen): DO NOT SUBMIT without a detailed description of headersplit.
"""

from __future__ import absolute_import
from __future__ import division
from __future__ import google_type_annotations
from __future__ import print_function

from absl import app
from absl import flags

import clang.cindex
from clang.cindex import *
clang.cindex.Config.set_library_path("/usr/local/opt/llvm/lib")


FLAGS = flags.FLAGS


def class_definitions(cursor):
    for i in cursor.walk_preorder():
        if i.kind != CursorKind.CLASS_DECL:
            continue
        if not i.is_definition():
            continue
        yield i


def class_implementations(cursor):
    for i in cursor.walk_preorder():
        if i.kind != CursorKind.CXX_METHOD:
            continue
        print(i.location.file.name)
        yield i


def extract_definition(cursor):
    filename = cursor.location.file.name
    with open(filename, 'r') as fh:
        contents = fh.read()
    class_name = cursor.spelling
    class_defn = contents[cursor.extent.start.offset:cursor.extent.end.offset]
    #print(cursor.spelling)
    #pc = cursor.semantic_parent
    #print(contents[pc.extent.start.offset:pc.extent.start.offset + 100])
    return contents[cursor.extent.start.offset:cursor.extent.end.offset]


def extract_implementation(cursor):
    filename = cursor.location.file.name
    with open(filename, 'r') as fh:
        contents = fh.read()
    impl_name = cursor.spelling
    print(filename)
    print(impl_name)
    print(contents[cursor.extent.start.offset:cursor.extent.end.offset])
    return impl_name, contents[cursor.extent.start.offset:cursor.extent.end.
                               offset]



"""
TODO: resolve class dependency issues
TODO: resolve over-inclusion issues
TODO: formatting 
"""

def main(argv):
  if len(argv) > 1:
    raise app.UsageError('Too many command-line arguments.')
  idx2 = Index.create()
  tu2 = idx2.parse('mocks.cc', ['-x', 'c++'])
  impls = class_implementations(tu2.cursor)
  """
  idx = Index.create()
  tu = idx.parse('mocks.h', ['-x', 'c++'])
  defns = class_definitions(tu.cursor)
  """

  classname_to_impl = dict()

  for impl in impls:
      classname, impl = extract_implementation(impl)
      try:
          classname_to_impl[classname] += impl
      except:
          classname_to_impl[classname] = impl
  for defn in defns:
      print("---")
      #print(extract_definition(defn))
      class_name,class_defn = extract_definition(defn)
      with open("mockclass/{}.h".format(class_name),"w") as f:
        f.write(class_defn)
      

if __name__ == '__main__':
  app.run(main)
