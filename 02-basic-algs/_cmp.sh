#! /bin/bash
file=hdu_5358
g++ -Wall -Wextra -Werror -Wno-unused-result -O2 "$file"_gen.cpp
./a.out > "$file.cmp.in"
g++ -Wall -Wextra -Werror -Wno-unused-result -O2 "$file.cpp"
echo my_out
./a.out < "$file.cmp.in"
g++ -Wall -Wextra -Werror -Wno-unused-result -O2 "$file"_ac.cpp
echo ac_out
./a.out < "$file.cmp.in"