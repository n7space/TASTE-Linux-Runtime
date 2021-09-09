#!/bin/bash

PREFIX=/home/taste/tool-inst
SOURCES=$(dirname $0)

mkdir -p "${PREFIX}/include/TASTE-Linux-Runtime/src"
cp -r "${SOURCES}/src" "${PREFIX}/include/TASTE-Linux-Runtime"

