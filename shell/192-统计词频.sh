#! /bin/bash

# Read from the file words.txt and output the word frequency list to stdout.
tr -s '[:space:]' '\n' < words.txt | sort | uniq -c | sort -nr | awk '{print $2, $1}'

# tr -s '[:space:]' '\n': Replace consecutive whitespace characters with newline.
#
# > tr -s '[:space:]' '\n' < words.txt 
# the
# day
# is
# sunny
# the
# the
# the
# sunny
# is
# is

# sort: Sort the words.
# > tr -s '[:space:]' '\n' < words.txt | sort
# day
# is
# is
# is
# sunny
# sunny
# the
# the
# the
# the

# uniq -c: Count unique occurrences of each word.
# tr -s '[:space:]' '\n' < words.txt | sort | uniq -c
#       1 day
#       3 is
#       2 sunny
#       4 the

# sort -nr: Sort by frequency in descending order.
# tr -s '[:space:]' '\n' < words.txt | sort | uniq -c | sort -nr
#       4 the
#       3 is
#       2 sunny
#       1 day

# awk '{print $2, $1}': Print the first two columns.
# > tr -s '[:space:]' '\n' < words.txt | sort | uniq -c | sort -nr | awk '{print $2, $1}'
# the 4
# is 3
# sunny 2
# day 1