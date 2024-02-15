#include <bits/stdc++.h>

void
prestr(const std::string& instr, const std::string&postr)
{
    if (!instr.empty()) {
        std::cout << postr.back();
        int pos = instr.find(postr.back());
        prestr(instr.substr(0, pos), postr.substr(0, pos));
        prestr(instr.substr(pos + 1, instr.size() - pos - 1), postr.substr(pos, postr.size() - pos - 1));
    }
}

int
main()
{
    std::string instr, postr;
    std::cin >> instr;
    std::cin >> postr;
    prestr(instr, postr);
    std::cout << std::endl;
}