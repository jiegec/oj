#!/usr/bin/env python3
# Automatic download the question html.
import glob
import os
import urllib.request
import requests

oj = {'rqnoj': 'http://www.rqnoj.cn/problem/',
      'hdu': 'http://acm.hdu.edu.cn/showproblem.php?pid=',
      'zoj': 'http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=',
      'hoj': 'http://acm.hit.edu.cn/hoj/problem/view?id=',
      'poj': 'http://poj.org/problem?id=',
      'uoj': 'http://uoj.ac/problem/',
      'uva': 'https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=',
      'ts': 'http://oj.tsinsen.com/',
      'loj': 'https://loj.ac/problem/',
      'codeforces': 'https://codeforces.com/contest'}
for k, v in oj.items():
  with open('%s/CMakeLists.txt' % k, 'w') as f:
    f.write('cmake_minimum_required(VERSION 3.3)\nproject(%s)\n\n' % k)
    for file in sorted(list(glob.glob("%s/%s*" % (k, k)))):
      file_name = os.path.basename(file)
      (root, ext) = os.path.splitext(file_name)
      if ext == '.html' or ext == '.exe' or len(ext) == 0:
        continue
      problemId = os.path.basename(file)[len(k):].split('.')[0]

      link = v + problemId
      if k == 'codeforces':
        link = v + problemId[:-1] + '/problem/' + problemId[-1]

      if ext == '.cpp':
        comment = '// ' + link + '\n'
        lines = open(file).readlines()
        if len(lines) == 0 or lines[0] != comment: 
          lines.insert(0, comment)
          open(file, 'w').writelines(lines)
        f.write('add_executable(%s %s)\n' % (root, file_name))

with open('CMakeLists.txt', 'w') as f:
  f.write('cmake_minimum_required(VERSION 3.3)\nproject(oj)\n\nset(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")\n\n')
  f.write('add_subdirectory(custom)\n')
  f.write('add_subdirectory(templates)\n')
  for k in oj:
    f.write('add_subdirectory(%s)\n' % k)
