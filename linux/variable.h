#ifndef VARIABLE_H
#define VARIABLE_H
#include <vector>
#include <string>
#include <stack>

#define write_mode 1
#define edit_mode 2
#define visual_mode 3

#define backspace_text_size_equal 1
#define backspace_text_size_smaller 2
#define backspace_x_greater 3
#define backspace_x_greater_size_greater_0 4

#define newline_text_size_equal 5
#define newline_text_smaller_x_equal 6
#define newline_text_equal_x_smaller 7
#define newline_text_smaller_x_smaller 8

struct Undo_struct
{
	int undo_first_line_print;
	int undo_last_line_print;
	int undo_level;
	int undo_cursor_position_y;
	int undo_cursor_position_x;
        int what_operation;
};

//Functions in write_mode
void right_key_write(int &, int &, int &, int&, int&, int&, std::vector<std::string>&);
void left_key_write(int &, int&, int&, int&, int&, std::vector<std::string>&);
void up_key_write(int &, int &, int &, int&, std::vector<std::string>&);
void down_key_write(int &, int &, int &, int&, std::vector<std::string>&);
void backspace_key_write(int &, int&, int& , int&, int&, int&, int& , int&, std::vector<std::string>&, std::string&, std::stack<Undo_struct>&);
void newline_write(int &, int&, int& , int&, int&, int&, int& , int&, std::vector<std::string>&, std::string&, std::stack<Undo_struct>&);
void other_char_write(int &, int&, int& , int&, int&, int&, int& , int&, std::vector<std::string>&);

//Functions to read file and write to file
void open_file(std::string& , std::vector<std::string>& , int& , int& , int&);
void write_file(std::string& , std::vector<std::string>&);

#endif
