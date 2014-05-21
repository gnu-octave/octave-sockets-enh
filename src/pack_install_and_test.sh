#!/bin/bash

## 09.05.2014 Andreas Weber

make
cd ../../
tar czf sockets.tar.gz octave-sockets
octave -q --eval "pkg install sockets.tar.gz"
cd -
octave -q --eval "pkg load sockets; test socket"
