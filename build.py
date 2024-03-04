#!/usr/bin/env python3

import os
import sys

if not os.path.exists('build'):
    os.makedirs('build')
os.chdir('build')


if '--release' in sys.argv:
    os.system('cmake -DCMAKE_BUILD_TYPE=Release ..')
else:
    os.system('cmake ..')

os.system('make -j`nproc`')

