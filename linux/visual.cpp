#include <iostream>
#include <vector>
#include <string>
#include "variable.h"
#include "copy_variable.h"

void right_key_visual(int& cursor_position_y, int& cursor_position_x, int& xMax, int& yMax, int& first_line_print, int& last_line_print, std::vector<std::string>& text, Visual_struct& visual_structure)
{
                      right_key_write(cursor_position_y, cursor_position_x, xMax, yMax, first_line_print, last_line_print, text);
		      
		      visual_structure.change_last_line(cursor_position_y);
		      visual_structure.change_x_position_last(cursor_position_x);
}

void left_key_visual(int& cursor_position_x, int& cursor_position_y, int& yMax, int& first_line_print, int& last_line_print, std::vector<std::string>& text,
Visual_struct& visual_structure)
{
	              left_key_write(cursor_position_x, cursor_position_y, yMax, first_line_print, last_line_print, text);

		      visual_structure.change_first_line(cursor_position_y);
		      visual_structure.change_x_position_first(cursor_position_x);
}

