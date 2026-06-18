#!/bin/bash

javac *.java -d classes/ -cp $ANDROID_HOME/platforms/android-30/android.jar
d8 classes/net/deviceblack/fastboot/*.class
xxd -i classes.dex > ../classes.hpp
rm -rf classes classes.dex
