#!/bin/bash

echo "Test case: invalid"
echo ""

if [ -z "$1" ] ; then
  exit 1
fi

myDir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
tmpOut="$(mktemp)"

function dtor
{
  rm -f "${tmpOut}"
}
trap dtor EXIT

bash -c "\"$myDir/dynamic_analysis_wrapper.sh\" \"$1\" -n \"test-host\" -i \"$myDir/invalid.db\" -o \"$tmpOut\""
cmdExit=$?

if (($cmdExit != 1)) ; then
  echo "Subject exited with unexpected exit code"
  exit $cmdExit
fi

exit 0
