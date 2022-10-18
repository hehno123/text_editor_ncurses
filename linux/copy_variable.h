#ifndef COPY_VARIABLE_H
#define COPY_VARIABLE_H

#include <vector>
#include <string>

//struct with value needed to copy or delete text

class Visual_struct
{       
	private:
	int visual_line_static;
	int visual_line_non_static;
	int visual_x_position_static;
	int visual_x_position_non_static;
	int first_line_print_in_delete;
	
	public:
	std::vector<std::string> copied_text;

	void change_first_line_print(int value)
	{
		first_line_print_in_delete = value;
	}

	void change_line_static(int value)
	{
		visual_line_static = value;
	}

	void change_line_non_static(int value)
	{
		visual_line_non_static = value;
	}

	void change_x_position_static(int value)
	{
		visual_x_position_static = value;
	}

	void change_x_position_non_static(int value)
	{
		visual_x_position_non_static = value;
	}

	int get_line_static()
	{
		return visual_line_static;
	}

	int get_line_non_static()
	{
		return visual_line_non_static;
	}

	int get_x_static()
	{
		return visual_x_position_static;
	}

	int get_x_non_static()
	{
		return visual_x_position_non_static;
	}

	int get_first_line()
	{
		return first_line_print_in_delete;
	}

	void max_value_visual(int& max_value_line, int& min_value_line, int& max_value_x, int& min_value_x)
        {
		max_value_line = std::max(visual_line_static, visual_line_non_static);
		min_value_line = std::min(visual_line_static, visual_line_non_static);

                if(max_value_line == min_value_line)
		{
		      min_value_x = std::min(visual_x_position_static, visual_x_position_non_static);
		      max_value_x = std::max(visual_x_position_static, visual_x_position_non_static);
                }

		else if(max_value_line == visual_line_static)
	        {
		      min_value_x = visual_x_position_non_static;
		      max_value_x = visual_x_position_static;
		}

		else if(max_value_line == visual_line_non_static)
		{
		      min_value_x = visual_x_position_static;
		      max_value_x = visual_x_position_non_static;
		}
	}
};

//function to selected text
void right_key_visual(int &, int &, int &, int&, int&, int&, std::vector<std::string>&, Visual_struct&);
void left_key_visual(int &, int &, int&, int&, int&, std::vector<std::string>&, Visual_struct&);
void up_key_visual(int &, int &, int &, int &, int &, std::vector<std::string>&, Visual_struct&);
void down_key_visual(int &, int &, int &, int &, std::vector<std::string>&, Visual_struct&);
void copy_to_buffer_visual(std::vector<std::string>&, Visual_struct&);
void paste_visual(int&, int&, int&, int&, int&, std::vector<std::string>&, Visual_struct&);
void delete_visual(int&, int&, int&, int&, int&, std::vector<std::string>& , Visual_struct&);
void search_in_text(int&, int&, int&, int&, int&, int&, std::string&, std::vector<std::string>&);

#endif
