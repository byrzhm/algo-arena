#! /bin/bash
file=uva_11572
g++ -g -Wall -Wextra -Werror -Wno-unused-result -O2 "$file".cpp
# echo my_out
./a.out < "$file".in
# g++ -Wall -Wextra -Werror -Wno-unused-result -O2 "$file"_ac.cpp
# echo ac_out
# ./a.out < "$file.in"