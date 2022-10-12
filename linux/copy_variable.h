#ifndef COPY_VARIABLE_H
#define COPY_VARIABLE_H

#include <vector>
#include <string>

//struct with value needed to copy or delete text

class Visual_struct
{       
	private:
	int visual_first_line;
	int visual_last_line;
	int visual_x_position_first;
	int visual_x_position_last;
	
	public:
	std::vector<std::string> copied_text;

	void change_first_line(int value)
	{
		visual_first_line = value;
	}

	void change_last_line(int value)
	{
		visual_last_line = value;
	}

	void change_x_position_first(int value)
	{
		visual_x_position_first = value;
	}

	void change_x_position_last(int value)
	{
		visual_x_position_last = value;
	}

	int get_first_line()
	{
		return visual_first_line;
	}

	int get_last_line()
	{
		return visual_last_line;
	}

	int get_x_first()
	{
		return visual_x_position_first;
	}

	int get_x_last()
	{
		return visual_x_position_last;
	}
};

//function to selected text
void right_key_visual(int &, int &, int &, int&, int&, int&, std::vector<std::string>&, Visual_struct&);
void left_key_visual(int &, int &, int&, int&, int&, std::vector<std::string>&, Visual_struct&);
void up_key_visual(int &, int &, int &, int &, std::vector<std::string>&, Visual_struct&);
void down_key_visual(int &, int &, int &, int &, std::vector<std::string>&, Visual_struct&);
void copy_to_buffer_visual(Visual_struct&);

#endif
