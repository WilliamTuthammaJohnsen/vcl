#!/bin/bash
ENGINE=g++
MAIN_FILE=ignition.cpp
LANG_FILE=language.cpp
UTIL_FILE=stringUtils.cpp

$ENGINE $MAIN_FILE $LANG_FILE $UTIL_FILE -o build