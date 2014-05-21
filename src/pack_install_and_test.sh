#!/bin/bash

## 09.05.2014 Andreas Weber

make
cd ../../
tar czf sockets-enh.tar.gz octave-sockets-enh
octave -q --eval "pkg install sockets-enh.tar.gz"
cd -
octave -q --eval "pkg load sockets-enh; test socket"
