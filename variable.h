#ifndef VARIABLE_H
#define VARIABLE_H
#include <vector>
#include <string>

void right_key(int &, int &, int &, std::vector<std::string>&);
void left_key(int &, int&, std::vector<std::string>&);
void up_key(int &, int &, int &, int&, std::vector<std::string>&);
void down_key(int &, int &, int &, int&, std::vector<std::string>&);
void backspace_key(int &, int&, int& , int&, int&, int&, int& , int&, std::vector<std::string>&, std::string&);
void newline(int &, int&, int& , int&, int&, int&, int& , int&, std::vector<std::string>&, std::string&);
void other_char(int &, int&, int& , int&, int&, int&, int& , int&, std::vector<std::string>&);

#endif
