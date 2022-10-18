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

struct Undo_struct
{
	int undo_first_line_print;
	int undo_last_line_print;
	int undo_level;
	int undo_cursor_position_y;
	int undo_cursor_position_x;
        int what_operation;
	char what_char_delete;

	void save_current_parameters_to_stack(int& first_line_print, int& last_line_print, int& level, int& cursor_position_y, int& cursor_position_x)
	{
                    undo_first_line_print = first_line_print;
		    undo_last_line_print = last_line_print;
		    undo_level = level;
		    undo_cursor_position_y = cursor_position_y;
		    undo_cursor_position_x = cursor_position_x;
        }
};

//Functions in write_mode
void right_key_write(int &, int &, int &, int&, int&, int&, std::vector<std::string>&);
void left_key_write(int &, int&, int&, int&, int&, std::vector<std::string>&);
void up_key_write(int &, int &, int &, int&, int&, std::vector<std::string>&);
void down_key_write(int &, int &, int &, int&, std::vector<std::string>&);
void backspace_key_write(int &, int&, int& , int&, int&, int&, int& , int&, std::vector<std::string>&, std::string&, std::stack<Undo_struct>&);
void newline_write(int &, int&, int& , int&, int&, int&, int& , int&, std::vector<std::string>&, std::string&, std::stack<Undo_struct>&);
void other_char_write(int &, int&, int& , int&, int&, int&, int& , int&, std::vector<std::string>&, std::stack<Undo_struct>&);
void undo(int&, int&, int&, int&, int&, int&, int&, std::vector<std::string>&, std::stack<Undo_struct>&);

//Functions to read file and write to file
void open_file(std::string& , std::vector<std::string>& , int& , int& , int&);
void write_file(std::string& , std::vector<std::string>&);

#endif
