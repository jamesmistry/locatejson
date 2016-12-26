#!/bin/bash

valgrind --error-exitcode=101 --tool=memcheck --leak-check=yes --show-leak-kinds=all --track-origins=yes $1

results=$?

if (($results == 101)) ; then
  echo "Test failed due to dynamic analysis errors"
elif (($results != 0)) ; then
  echo "Test failed because application returned non-zero exit code"
fi

exit $results

