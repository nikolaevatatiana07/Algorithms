#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include "stack.h"

static int priority(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

static bool is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool convert_to_rpn(const std::string& input, std::string& output)
{
    if (input.empty()) return false;

    Stack* stack = stack_create();
    output.clear();

    bool operand = true;
    bool ok = true;

    for (size_t i = 0; i < input.length() && ok; ++i)
    {
        char c = input[i];
        if (std::isspace(static_cast<unsigned char>(c))) continue;

        if (std::isalpha(static_cast<unsigned char>(c)))
        {
            if (!operand) { ok = false; break; }
            output += c;
            operand = false;
        }
        else if (c == '(')
        {
            if (!operand) { ok = false; break; }
            stack_push(stack, c);
            operand = true;
        }
        else if (c == ')')
        {
            if (operand) { ok = false; break; }
            bool found_paren = false;
            while (!stack_empty(stack)) {
                char top = static_cast<char>(stack_get(stack));
                if (top == '(') {
                    found_paren = true;
                    stack_pop(stack);
                    break;
                }
                output += top;
                stack_pop(stack);
            }
            if (!found_paren) { ok = false; break; }
            operand = false;
        }
        else if (is_operator(c))
        {
            if (operand) { ok = false; break; }
            while (!stack_empty(stack) && is_operator(static_cast<char>(stack_get(stack))))
            {
                char top_op = static_cast<char>(stack_get(stack));
                if (priority(top_op) >= priority(c)) {
                    output += top_op;
                    stack_pop(stack);
                }
                else { break; }
            }
            stack_push(stack, c);
            operand = true;
        }
        else { ok = false; break; }
    }

    if (ok) {
        while (!stack_empty(stack)) {
            char top = static_cast<char>(stack_get(stack));
            if (top == '(' || top == ')') { ok = false; break; }
            output += top;
            stack_pop(stack);
        }
    }

    if (ok && operand) {
        ok = false;
    }

    stack_delete(stack);
    return ok;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        return 1;
    }

    std::ifstream file(argv[1]);

    if (!file.is_open()) {
        return 1;
    }

    std::string input;
    std::string output;

    while (std::getline(file, input))
    {
        bool is_empty = true;
        for (unsigned char c : input) {
            if (!std::isspace(c)) {
                is_empty = false;
                break;
            }
        }
        if (is_empty) continue;
        if (convert_to_rpn(input, output)) {
            std::cout << output << "\n";
        }
        else {
            std::cout << "Error\n";
        }
    }
    return 0;
}