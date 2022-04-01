#!/bin/bash
cat words.txt | tr -s ' ' '\n' | sort | uniq -c | sort -r | awk '{print $2" "$1}'
# cat file.txt | sed 's/ /\n/g' | sed '/^$/d' | sort | uniq -c | sort -r | awk '{print $2" "$1}'