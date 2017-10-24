#!/usr/bin/env python3
# Automatic download the question html.
import glob
import os
import urllib.request
oj = {'rqnoj': 'http://www.rqnoj.cn/problem/',
      'hdu': 'http://acm.hdu.edu.cn/showproblem.php?pid=',
      'zoj': 'http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=',
      'hoj': 'http://acm.hit.edu.cn/hoj/problem/view?id=',
      'poj': 'http://poj.org/problem?id=',
      'uoj': 'http://uoj.ac/problem/',
      'uva': 'https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=',
      'ts': 'http://www.tsinsen.com/',
      'loj': 'https://loj.ac/problem/'}
for k, v in oj.items():
  with open('%s/CMakeLists.txt' % k, 'w') as f:
    f.write('cmake_minimum_required(VERSION 3.3)\nproject(%s)\n\n' % k)
    for file in glob.glob("%s/%s*" % (k, k)):
      file_name = os.path.basename(file)
      (root, ext) = os.path.splitext(file_name)
      if 'html' in file or 'exe' in file or len(ext) == 0:
        continue
      if 'py' not in file and 'java' not in file:
        f.write('add_executable(%s %s)\n' % (root, file_name))
      problemId = os.path.basename(file)[len(k):].split('.')[0]
      if os.path.exists('%s/%s%s.html' % (k, k, problemId)):
        continue
      print('Processing %s %s.' % (k, problemId))
      content = urllib.request.urlopen(v + problemId).read()
      with open('%s/%s%s.html' % (k, k, problemId), 'wb') as ff:
        ff.write(content)

with open('CMakeLists.txt', 'w') as f:
  f.write('cmake_minimum_required(VERSION 3.3)\nproject(oj)\n\nset(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")\n\n')
  f.write('add_subdirectory(custom)\n')
  for k in oj:
    f.write('add_subdirectory(%s)\n' % k)
