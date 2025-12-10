#include <iostream>
#include <string>
#include "stack.h"

// Функция приоритета операторов
int precedence(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        default:  return 0;
    }
}

// Проверка — является ли символ оператором
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Основная функция преобразования инфиксной записи в постфиксную
std::string infixToPostfix(const std::string& infix) {
    StackStr* stack = createStackStr();
    std::string postfix;

    for (char token : infix) {
        if (isspace(token)) continue; // пропускаем пробелы

        if (isalnum(token)) {
            // если операнд (буква или цифра)
            postfix += token;
        }
        else if (token == '(') {
            pushStr(stack, std::string(1, token));
        }
        else if (token == ')') {
            // выталкиваем всё до '('
            bool foundOpening = false;
            while (stack->top) {
                if (peekStr(stack) == "(") {
                    popStr(stack);
                    foundOpening = true;
                    break;
                } else {
                    postfix += peekStr(stack);
                    popStr(stack);
                }
            }
            if (!foundOpening) {
                std::cerr << "Ошибка: несбалансированные скобки\n";
                freeStackStr(stack);
                return ""; // ошибка
            }
        }
        else if (isOperator(token)) {
            // пока сверху оператор с приоритетом >= текущего, выталкиваем его
            while (stack->top && isOperator(peekStr(stack)[0]) &&
                   precedence(peekStr(stack)[0]) >= precedence(token)) {
                postfix += peekStr(stack);
                popStr(stack);
            }
            pushStr(stack, std::string(1, token));
        }
        else {
            std::cerr << "Ошибка: недопустимый символ '" << token << "'\n";
            freeStackStr(stack);
            return ""; // ошибка
        }
    }

    // вытолкнуть оставшиеся операторы из стека
    while (stack->top) {
        if (peekStr(stack) == "(" || peekStr(stack) == ")") {
            std::cerr << "Ошибка: несбалансированные скобки\n";
            freeStackStr(stack);
            return ""; // ошибка
        }
        postfix += peekStr(stack);
        popStr(stack);
    }

    freeStackStr(stack);
    return postfix;
}

// Тест
int main() {
    std::string expr;
    std::cout << "Введите инфиксное выражение: ";
    std::getline(std::cin, expr);

    std::string postfix = infixToPostfix(expr);
    if (!postfix.empty()) {
        std::cout << "Постфиксная форма: " << postfix << "\n";
    }

    return 0;
}
