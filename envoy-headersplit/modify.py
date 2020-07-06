# Lint as: python3
"""TODO(mugechen): DO NOT SUBMIT without one-line documentation for modify.

TODO(mugechen): DO NOT SUBMIT without a detailed description of modify.
"""

# get class names and filename

from pathlib import Path

dir = Path("test/mocks/server/")
filenames = list(map(str,dir.glob('*.h')))
classnames = []
classname2filename = dict()
classname2bazelname = dict()
for filename in filenames:
  classname_tokens = filename.split('/')[-1].replace('.h','').split('_')
  classname = "Mock" + ''.join(map(lambda x: x[:1].upper()+x[1:],classname_tokens))
  classnames.append(classname)
  classname2filename[classname]=filename
  bazelname = "//test/mocks/server:"+filename.split('/')[-1].replace('.h','')+'_mocks'
  classname2bazelname[classname]=bazelname

print(classnames)

p = Path('./test')

# walk through all files and check files that contains "server/mocks.h"
# don't forget change dependency on bazel
for i in p.glob('**/*.cc'):
  replace_includes = ""
  flag = False
  used = ""
  with i.open() as f:
    content = f.read()
    if '#include "test/mocks/server/mocks.h"' in content:
      flag = True
      replace_includes = ""
      for classname in classnames:
        if classname in content:
          if "Server::{}".format(classname) in content or "Server::Configuration::{}".format(classname):
            replace_includes += '#include "{}"\n'.format(classname2filename[classname])
            used+= '"{}",'.format(classname2bazelname[classname])
          else:
            print(i,classname)
  if flag:
    with i.open(mode='w') as f:
      f.write(content.replace('#include "test/mocks/server/mocks.h"',replace_includes))
    with (i.parent / 'BUILD').open() as f:
      # write building files
      content = f.read()
      content = content.replace('"//test/mocks/server:server_mocks",',used)
    with (i.parent / 'BUILD').open('w') as f:
      f.write(content)





