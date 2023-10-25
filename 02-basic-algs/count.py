#! /usr/bin/python3
with open('./P1102_3.in') as f:
    lines = f.readlines()

line = lines[1]
line = line.strip()
characters = line.split(' ')
print(len(characters))
print(f"1: {characters.count('1')}")
print(f"2: {characters.count('2')}")