#!/bin/bash

valgrind --error-exitcode=101 --tool=memcheck --leak-check=yes --show-leak-kinds=definite,possible --track-origins=yes "$@"

results=$?

if (($results == 101)) ; then
  echo "Dynamic analysis FAILED"
else
  echo "Dynamic analysis PASSED"
fi

exit $results

