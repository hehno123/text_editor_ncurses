#ifndef VARIABLE_H
#define VARIABLE_H
#include <vector>
#include <string>
#include <stack>

#define write_mode 1
#define edit_mode 2
#define visual_mode 3
#define search_mode 4

#define backspace_undo 1
#define newline_undo 2
#define new_char_undo 3
#define del_char_undo 4
#define left_key_undo 5
#define right_key_undo 6
#define up_key_undo 7
#define down_key_undo 8

struct Undo_struct
{
 	int what_operation;
	int what_char_delete;	
};

//Functions in write_mode
void right_key_write(int &, int &, int &, int&, int&, int&, std::vector<std::string>&);
void left_key_write(int &, int&, int&, int&, int&, std::vector<std::string>&);
void up_key_write(int &, int &, int &, int&, int&, std::vector<std::string>&);
void down_key_write(int &, int &, int &, int&, std::vector<std::string>&);
void backspace_key_write(int &, int&, int& , int&, int&, int&, int& , int&, std::vector<std::string>&, std::string&, std::stack<Undo_struct>&);
void newline_write(int &, int&, int& , int&, int&, int&, int& , int&, std::vector<std::string>&, std::string&, std::stack<Undo_struct>&);
void other_char_write(int &, int&, int& , int& , int&, int&, int&, int& , int&, std::vector<std::string>&, std::stack<Undo_struct>&);
void undo(int&, int&, int&, int&, int&, int&, int&, std::vector<std::string>&, std::stack<Undo_struct>&);

//Functions to read file and write to file
void open_file(std::string& , std::vector<std::string>& , int& , int& , int&);
void write_file(std::string& , std::vector<std::string>&);

#endif
