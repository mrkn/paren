#! /bin/sh

result=$(echo '()' | ./paren -)
if test "$result" = "nil"; then
  echo "PASS"
else
  echo "FAILED"
  exit 1
fi
