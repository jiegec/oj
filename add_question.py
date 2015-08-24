#!/usr/bin/env python3
import glob
import os
import urllib.request
oj = {'rqnoj': 'http://www.rqnoj.cn/problem/',
'hdu': 'http://acm.hdu.edu.cn/showproblem.php?pid=',
'zoj': 'http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=',
'hoj': 'http://acm.hit.edu.cn/hoj/problem/view?id=',
'poj': 'http://poj.org/problem?id='}
for k, v in oj.items():
    for file in glob.glob("%s/%s*" % (k, k)):
        if 'html' in file or 'exe' in file:
            continue
        id = os.path.basename(file)[len(k):].split('.')[0]
        if os.path.exists('%s/%s%s.html' % (k, k, id)):
            continue
        print('Processing %s %s.' % (k, id))
        content = urllib.request.urlopen(v + id).read()
        with open('%s/%s%s.html' % (k, k, id), 'wb') as f:
            f.write(content)

