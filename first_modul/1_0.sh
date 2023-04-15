#!/usr/bin/env bash

IFS=:
while read func
do
  answer="---"
  pattern='^\.B #include <\([a-zA-Z0-9._]*\)>'
  for dir in $MANPATH
  do
    for path_to_man3 in $dir
    do
      archieve_file="$path_to_man3/man3/$func.3.gz"
      ordinary_file="$path_to_man3/man3/$func.3"
      text=""
      if [ -f "$archieve_file" ] 
      then
        text=$(gunzip -c "$archieve_file")
        answer=$(echo "$text" | sed -n "s/$pattern/\1/p")
        continue 
      fi 
      if [ -f "$ordinary_file" ]
      then
        text=$(sed '' "$ordinary_file")
        answer=$(echo "$text" | sed -n "s/$pattern/\1/p")
        continue
      fi
    done
  done  
  echo "$answer"
done
