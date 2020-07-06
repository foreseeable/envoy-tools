# Lint as: python3
"""TODO(mugechen): DO NOT SUBMIT without one-line documentation for profile.

TODO(mugechen): DO NOT SUBMIT without a detailed description of profile.
"""
import subprocess
import os
from subprocess import Popen, PIPE, STDOUT


d = dict()
with open("changed.txt") as changed_tests_file:
  changed_tests = changed_tests_file.readlines()
  for test in changed_tests:
    test=test.strip()
    test = "//"+test[:-3]
    last_slash = 0
    for i,c in enumerate(test):
      if c=='/':
        last_slash=i
    test = list(test)
    test[last_slash]=':'
    test = ''.join(test)
    os.system("git checkout refactor_server")
    os.system("bazel clean --expunge")
    os.system("bazel build //source/exe:envoy-static")

    output = subprocess.run(["bazel", "build", test,"--noremote_accept_cached"],capture_output=True).stderr #.split('\n')
    output = output.decode().split('\n')

    d[test] = [0,0]
    for line in output:
      if "Elapse" in line:
        d[test][0] = line.split('s,')[0].split(' ')[-1]
    os.system("git checkout origin/master")
    os.system("bazel clean --expunge")
    os.system("bazel build //source/exe:envoy-static")

    output = subprocess.run(["bazel", "build", test,"--noremote_accept_cached"],capture_output=True).stderr #.split('\n')
    output = output.decode().split('\n')

    for line in output:
      if "Elapse" in line:
        d[test][1] = line.split('s,')[0].split(' ')[-1]

    print(test,d[test])


print(d)

with open("result.txt","w") as f:
  f.write(str(d))

