#!/bin/bash

if [ -z "$1" ] || [ -z "$2" ] ; then
  echo "Usage: $0 <test subject> <test name>"
  exit 1
fi

subject="$1"
name="test_$2"

myDir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
targetTest="$myDir/${name}.sh"

bash -c "$targetTest \"$subject\""
cmdExit=$?
if (($cmdExit == 0)) ; then
  echo "Test PASSED!"
else
  echo "Test FAILED!"
fi

exit $cmdExit
