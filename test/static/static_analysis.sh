#!/bin/bash

if [ -z "$1" ] || [ -z "$2" ] ; then
  echo "Usage: static_analysis.sh <source directory> <built source directory>"
fi

srcDir="$1"
buildSrcDir="$2"

cppcheck --verbose --suppress=missingIncludeSystem --suppress="*:${srcDir}/tclap/*" --inline-suppr -i "${srcDir}/tclap" -I "${srcDir}" -I "${buildSrcDir}" --enable=all "${srcDir}"
analysisResult=$?

if (($analysisResult == 0)) ; then
  echo "Static analysis PASSED!"
  exit 0
else
  echo "Static analysis FAILED"
  exit 1
fi

