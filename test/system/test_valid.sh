#!/bin/bash

echo "Test case: valid"
echo ""

if [ -z "$1" ] ; then
  exit 1
fi

myDir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
tmpOut="$(tempfile)"

function dtor
{
  rm -f "${tmpOut}"
}
trap dtor EXIT

bash -c "\"$myDir/dynamic_analysis_wrapper.sh\" \"$1\" -n \"test-host\" -i \"$myDir/valid.db\" -o \"$tmpOut\""
cmdExit=$?

if (($cmdExit != 0)) ; then
  echo "Subject exited with non-zero exit code"
  exit $cmdExit
fi

diff "$tmpOut" "$myDir/valid_expected.json"
cmdExit=$?

if (($cmdExit != 0)) ; then
  echo "Test results not as expected"
  exit 1
fi
