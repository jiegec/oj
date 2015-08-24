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
      'uva': 'https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem='}
for k, v in oj.items():
    for file in glob.glob("%s/%s*" % (k, k)):
        if 'html' in file or 'exe' in file:
            continue
        problemId = os.path.basename(file)[len(k):].split('.')[0]
        if os.path.exists('%s/%s%s.html' % (k, k, problemId)):
            continue
        print('Processing %s %s.' % (k, problemId))
        content = urllib.request.urlopen(v + problemId).read()
        with open('%s/%s%s.html' % (k, k, problemId), 'wb') as f:
            f.write(content)
