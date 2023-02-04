#ifndef SYNTAX_HIGHLIGHTER_H
#define SYNTAX_HIGHLIGHTER_H
#include <string>
#include <vector>

std::vector<std::string> variable_types_cpp = {"int", "std::string", "short", "double", "float", "char", "long long", "void", "struct", "class"};
std::vector<std::string> word_reserved_cpp = {"if", "while", "for", "switch", "case"};
std::vector<std::string> macro_cpp = {"#define", "#ifndef", "#endif", "#pragma", "#include"};

#endif 
