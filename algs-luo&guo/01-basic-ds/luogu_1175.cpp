#include <bits/stdc++.h>

enum TokenType {
    Integer = -1,
    Operator = -2
};

struct Token
{
    TokenType type;
    int lexeme;
    Token(TokenType type, int lexeme) : type(type), lexeme(lexeme) {}
};

std::ostream& operator<<(std::ostream& out, const Token& tok) {
    if (tok.type == Integer)
        out << tok.lexeme;
    else
        out << static_cast<char>(tok.lexeme);
    return out;
}

std::stack<int> s;
std::stack<Token> s1, s2;
std::unordered_map<int, int> prece;
char chr;
int opnum;

static inline void in2post() {
    while ((chr = getchar()) != '\n') {
        switch (chr)
        {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            s1.emplace(Integer, chr - '0');
            break;

        case '+': case '-': case '*': case '/': case '^':
            opnum++;
            if (s.empty() || s.top() == '(')
                s.push(chr);
            else {
                if (chr == '^') {
                    while (!s.empty() && prece[s.top()] > prece[chr]) {
                        s1.emplace(Operator, s.top());
                        s.pop();
                    }
                } else {
                    while (!s.empty() && prece[s.top()] >= prece[chr]) {
                        s1.emplace(Operator, s.top());
                        s.pop();
                    }
                }
                s.push(chr);
            }
            break;

        case '(':
            s.push(chr);
            break;

        case ')':
            while (!s.empty() && s.top() != '(') {
                s1.emplace(Operator, s.top());
                s.pop();
            }
            if (!s.empty() && s.top() == '(')
                s.pop();
            else
                fprintf(stderr, "Parentheses mismatch!\n");
            break;

        default:
            fprintf(stderr, "Unexpected character!\n");
            break;
        }
    }
    while (!s.empty()) {
        assert(s.top() != '(');
        s1.emplace(Operator, s.top());
        s.pop();
    }

}

static inline void printout() {
    while (!s1.empty()) {
        s2.push(s1.top());
        s1.pop();
    }
    while (!s2.empty()) {
        std::cout << s2.top();
        s1.push(s2.top());
        s2.pop();
        std::cout << (s2.empty() ? '\n' : ' ');
    }
}

int
main(int argc, char const *argv[])
{

    prece['+'] = 10; prece['-'] = 10;
    prece['*'] = 20; prece['/'] = 20;
    prece['^'] = 30;

    in2post();
    printout();

    for (int i = 0; i < opnum; i++) {
        while (!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }

        while (!s2.empty()) {
            Token t = s2.top();
            if (t.type == Operator) {
                int rhs, lhs, result;
                rhs = s1.top().lexeme; s1.pop();
                lhs = s1.top().lexeme; s1.pop();
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
                    break;
                case '^':
                    result = static_cast<int>(pow(lhs, rhs));
                default:
                    break;
                }
                s1.emplace(Integer, result);
                s2.pop();
                break;
            }   
            s1.push(t);
            s2.pop();
        }

        printout();
    }

    return 0;
}
