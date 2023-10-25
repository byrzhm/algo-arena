#! /bin/bash

file=$1

touch "$file".cpp
echo "#include <bits/stdc++.h>" > "$file".cpp
touch "$file".in