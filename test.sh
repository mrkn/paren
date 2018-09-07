#! /bin/sh

result=$(echo '()' | ./src/paren -)
if test "$result" = "nil"; then
  echo "PASS"
else
  echo "FAILED"
  exit 1
fi
