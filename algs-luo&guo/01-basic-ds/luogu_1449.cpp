#include <bits/stdc++.h>

enum TokenType {
    tok_eof = -1,
    tok_op = -2,
    tok_int = -3,
};

struct Token {
    TokenType type;
    int lexeme;
    explicit Token(TokenType type = tok_int, int lexeme = 0)
        : type(type), lexeme(lexeme) {}
};

std::ostream& operator<<(std::ostream& out, const Token& tok) {
    if (tok.type == tok_int)
        out << tok.lexeme;
    else
        out << static_cast<char>(tok.lexeme);
    return out;
}

Token curtok;

static int 
getNextTok() {
    int ret, c;
    c = getchar();
    if (isdigit(c) != 0) {
        curtok.lexeme = c - '0';
        while ((c = getchar()) != '.' && (isdigit(c) != 0))
            curtok.lexeme = curtok.lexeme * 10 + (c - '0');
        curtok.type = tok_int;
        ret = tok_int;
    } else if (c == '@') {
        curtok.lexeme = c;
        curtok.type = tok_eof;
        ret = tok_eof;
    } else {
        curtok.lexeme = c;
        curtok.type = tok_op;
        ret = tok_op;
    }
    return ret;
}


int 
main(int argc, char const *argv[])
{
    std::stack<Token> s, s1;
    
    while (getNextTok() != tok_eof)
        s.push(curtok);

    while (!s.empty()) {
        s1.push(s.top());
        s.pop();
    }

    // while (!s1.empty())
    // {
    //     std::cout << s1.top();
    //     s.push(s1.top());
    //     s1.pop();
    //     std::cout << (s1.empty() ? '\n' : ' ');
    // }

    // while (!s.empty()) {
    //     s1.push(s.top());
    //     s.pop();
    // }

    while (!s1.empty()) {
        Token t = s1.top();
        if (t.type == tok_op) {
            int rhs, lhs, result;
            rhs = s.top().lexeme; s.pop();
            lhs = s.top().lexeme; s.pop();
            switch (t.lexeme)
            {
            case '+':
                result = lhs + rhs;
                break;
            case '-':
                result = lhs - rhs;
                break;
            case '*':
                result = lhs * rhs;
                break;
            case '/':
                result = lhs / rhs;
            default:
                break;
            }
            s1.pop();
            s.emplace(tok_int, result);
        } else {
            s.push(t);
            s1.pop();
        }
    }

    std::cout << s.top().lexeme << std::endl;

    return 0;
}
