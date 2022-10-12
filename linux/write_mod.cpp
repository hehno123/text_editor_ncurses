#include "variable.h"
#include "copy_variable.h"
#include <iostream>
#include <vector>
#include <string>

void right_key_write(int& cursor_position_y, int& cursor_position_x, int& xMax, int& yMax, int& first_line_print, int& last_line_print, std::vector<std::string>& text)
{
                        if(cursor_position_x < text[cursor_position_y].size())
			{
			     if(cursor_position_x == xMax && text.size() - 1 != cursor_position_y)
		             {
				     cursor_position_x = 0;
				     cursor_position_y++;

				     if(yMax == cursor_position_y)
				     {
					     first_line_print++;
					     last_line_print++;
			             }
		             }
			     
			     else
		             {
                                     cursor_position_x++;
			     }

			     return;
		        }

			else
			{
				if(cursor_position_y < text.size() - 1)
				{
					cursor_position_x = 0;
					cursor_position_y++;
				}
			}

			return;
}

void left_key_write(int& cursor_position_x, int& cursor_position_y, int& yMax, int& first_line_print, int& last_line_print, std::vector<std::string>& text)
{
                        if(cursor_position_x == 0 && cursor_position_y > 0)
			{
				if(first_line_print == cursor_position_y)
				{
				      first_line_print--;
			              last_line_print--;
		                }

				cursor_position_y--;
				cursor_position_x = text[cursor_position_y].size();
				return;
			}

			if(cursor_position_x > 0)
			{
				cursor_position_x--;
			}

			return ;
}

void up_key_write(int& cursor_position_y, int& first_line_print, int& last_line_print, int& cursor_position_x, std::vector<std::string>& text)
{
                        if(cursor_position_y > 0)
			{
				if(cursor_position_y == first_line_print)
				{
				    if(first_line_print > 0)
				    {
				           last_line_print--;
					       first_line_print--;
				    }				   
				}

				if(cursor_position_x > text[cursor_position_y -1].size())
				{
					cursor_position_y--;
					cursor_position_x = text[cursor_position_y].size();
					return;
				}

				cursor_position_y--;	
			}

			return;
}

void down_key_write(int& cursor_position_y, int& first_line_print, int& last_line_print, int& cursor_position_x, std::vector<std::string>& text)
{
                        if(text.size() > cursor_position_y + 1)
			{
				if(cursor_position_y == last_line_print)
				{
		                        last_line_print++;
					first_line_print++;
				}

		                if(cursor_position_x > text[cursor_position_y + 1].size())
		                {
			                cursor_position_y++;
				        cursor_position_x = text[cursor_position_y].size();
					return;
		                }

			    cursor_position_y++;
			}

			return;
}

void backspace_key_write(int& level, int& c, int& cursor_position_x, int& cursor_position_y, int& xMax, int& yMax, int& first_line_print, int& last_line_print, std::vector<std::string>& text, std::string& add, std::stack<Undo_struct>& text_history)
{
	            Undo_struct undo;
		    undo.undo_first_line_print = first_line_print;
		    undo.undo_last_line_print = last_line_print;
		    undo.undo_level = level;
		    undo.undo_cursor_position_y = cursor_position_y;
		    undo.undo_cursor_position_x = cursor_position_x;
      
		    if(cursor_position_x == 0 && cursor_position_y == 0)
		    {
				cursor_position_x = 0; 
			        cursor_position_y = 0;
				return;
		    }

		    if(cursor_position_x == 0 && cursor_position_y > 0)
		    { 
			     undo.what_operation = backspace_x_greater;

			     for(int i = 0; i < text[cursor_position_y].size(); i++)
			     {
				      text[cursor_position_y - 1].push_back(text[cursor_position_y][i]);
			     }
                             
                             if(cursor_position_y == first_line_print && first_line_print > 0)
		             {
					           first_line_print--;
						   last_line_print--;
			     }

			     else if(last_line_print + 1 == text.size())
			     {
				     last_line_print--;
			     }
 
			     level--;
			     cursor_position_x = text[cursor_position_y - 1].size() - text[cursor_position_y].size();
                             text.erase(text.begin() + cursor_position_y);
			     cursor_position_y--;
			     return;
		    }

		        
		    if(cursor_position_x > 0 && cursor_position_y >= 0)
		    {
				undo.what_operation = backspace_x_greater_size_greater_0;
			        cursor_position_x--;
		                text[cursor_position_y].erase(text[cursor_position_y].begin() + cursor_position_x);
			        return;
		    }

		    return;
}

void newline_write(int& level, int& c, int& cursor_position_x, int& cursor_position_y, int& xMax, int& yMax, int& first_line_print, int& last_line_print,std::vector<std::string>& text, std::string& add, std::stack<Undo_struct>& text_history)
{
	                        Undo_struct undo;
		                undo.undo_first_line_print = first_line_print;
		                undo.undo_last_line_print = last_line_print;
		                undo.undo_level = level;
		                undo.undo_cursor_position_y = cursor_position_y;
		                undo.undo_cursor_position_x = cursor_position_x;
                                
                                if(text.size() < yMax)
		                {
			                last_line_print++;
		                }

				else if(text.size() >= yMax)
				{
				           last_line_print++;
				           first_line_print++;
				} 

                                if(last_line_print - yMax == first_line_print)
			        {  
			                   first_line_print++;
			        } 


      		                for(int i = cursor_position_x; i < text[cursor_position_y].size(); i++)
			        {
				    add.push_back(text[cursor_position_y][i]);
			        }

			        for(int i = 1; i <= add.size(); i++)
			        {
				    text[cursor_position_y].pop_back();	
			        }
	
			        undo.what_operation = newline_text_smaller_x_smaller;
			        cursor_position_x = 0;
			        cursor_position_y++;
			        text.insert(text.begin() + cursor_position_y,add);
				add.clear();
				add.resize(1);
			        return;
}

void other_char_write(int& level, int& c, int& cursor_position_x, int& cursor_position_y, int& xMax, int& yMax, int& first_line_print, int& last_line_print, std::vector<std::string>& text)
{
                             if(cursor_position_x + 1 == xMax)
		             {
			         if(cursor_position_y + 1 == text.size())
		                 {
					std::string add = {};
				        level++;
				        add[0] = static_cast<char>(c);
				        text.push_back(add);
                                        last_line_print++;
				        cursor_position_x = 0;
				        cursor_position_y++;

				        if(last_line_print - yMax + 1 > first_line_print)
				        {
					        first_line_print++;
				        }
                                        
				        return;
			         }
			     
			         else
		                 {
			             std::string add;
				     add[0] = static_cast<char>(c);
			             cursor_position_y++;
			             text.insert(text.begin() + cursor_position_y, add);
			             cursor_position_x++;
			         }
			       }
			    
			
			else
		        {
		             text[cursor_position_y].insert(text[cursor_position_y].begin() + cursor_position_x, c);
			     cursor_position_x++;
		        }
		       
			return;
}
