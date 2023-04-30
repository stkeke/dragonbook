/* postfix.cpp - translate simple infix expression to postfix expression  */

/* simple expression: arithmetic expression consisting of digits separated by
 * plus (+) and minus (-) signs, such as 9-5+2, no space or other operations
 * like multiplication or division supported so far.
 * infix: 9-5+2 ==> postfix: 95-2+
 */

/* translation scheme for postfix:
 * expr->term rest
 * Rest->+term {print('+')} rest
 *     | -term {print('-')} rest
 *     | epsilon
 * term->0 {print('0')}
 * term->1 {print('1')}
 * ...
 * term->9 {print('9')}
 */

#include <string>
#include <iostream>

class Postfix {
private:
    std::string input{};
    char lookahead;
    int index{0};

public:
    Postfix(std::string s) {
        input = s;
        lookahead = input[index];
    }

    void expr() {
        term();
        rest();
    }

    void rest() {
        // consumed all characters in input
        if (index >= input.length()) return;

        if (lookahead == '+') {
            match('+'); term(); std::cout << "+"; rest();
        } else if (lookahead == '-') {
            match('-'); term(); std::cout << '-'; rest();
        } else {} // do nothing
    }

    void term() {
        int la = lookahead - '0'; // convert char to int
        if ( 0 <= la && la <= 9 ) {
            char t = lookahead;
            lookahead = input[++index];
            std::cout << t;
        } else {
            std::cerr << "Syntax Error\n";
            std::exit(1);
        }
    }

    void match(char ch) {
        if (ch == lookahead) {
            lookahead = input[++index];
        } else {
            std::cerr << "Syntax Error\n";
            std::exit(1);
        }
    }
};

class Parser {
public:
    void postfix_translate(std::string s) {
        Postfix* pf = new Postfix(s);
        pf->expr();
    }
};

int main(void)
{
    std::string input;
    Parser *p = new Parser();
    while(true) {
        std::cout << "Enter an infix expression (Hit 'Ctrl+D' to exit): ";
        std::cin >> input;
        if (input.empty()) {
            std::cout << "Bye bye ...\n";
            break;
        }
        p->postfix_translate(input);
        std::cout << "\n";
    }
}