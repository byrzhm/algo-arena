#include <bits/stdc++.h>

char chr;
char buf[sizeof(int) * 8 + 1];

void 
getnum(int64_t& num)
{
    int idx = 0;
    buf[idx++] = chr;
    
    while (isdigit(chr = getchar()))
        buf[idx++] = chr;
    buf[idx] = 0;
    num = atoi(buf);
}

int 
main(int argc, char const *argv[])
{
    int64_t num, tmp;
    std::stack<int64_t> s;
    
    chr = getchar();
    while (chr != '\n') {
        if (isdigit(chr)) {
            getnum(num);
            s.push(num);
        } else if (chr == '*') {
            assert(isdigit(chr = getchar()));
            assert(!s.empty());
            getnum(num);
            tmp = (num * s.top()) % 10000;
            s.pop();
            s.push(tmp);
        } else if (chr == '+') {
            assert(isdigit(chr = getchar()));
            getnum(num);
            s.push(num);
        }
    }
    
    while (s.size() != 1) {
        num = s.top();
        s.pop();
        num = (num + s.top()) % 10000;
        s.pop();
        s.push(num);
    }

    std::cout << s.top() % 10000 << std::endl;
    
    return 0;
}
