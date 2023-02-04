#include "variable.h"
#include "copy_variable.h"
#include <iostream>
#include <vector>
#include <string>

void right_key_write(int& cursor_position_y, int& cursor_position_x, int& xMax, int& yMax, int& first_line_print, int& last_line_print, std::vector<std::string>& text)
{
                        if(cursor_position_x < text[cursor_position_y].size())
			{
			     if(cursor_position_x == text[cursor_position_y].size() - 1 && text.size() - 1 != cursor_position_y)
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

void up_key_write(int& cursor_position_y, int& first_line_print, int& last_line_print, int& cursor_position_x, int& yMax, std::vector<std::string>& text)
{
                        if(cursor_position_y > 0)
			{
				if(cursor_position_y == first_line_print && first_line_print > 0)
				{
				     if(last_line_print - first_line_print == yMax - 1)
				     {
					     last_line_print--;
				     }

				     first_line_print--;		   
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

	            if(cursor_position_x == 0 && cursor_position_y == 0)
		    {
				cursor_position_x = 0; 
			        cursor_position_y = 0;
				return;
		    }

		    if(cursor_position_x == 0 && cursor_position_y > 0)
		    { 
			     
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

                             if(static_cast<char>(c) != 'u')
                             {
                                    undo.what_operation = backspace_undo;
			            text_history.push(undo);
		             }
			     return;
		    }

		        
		    if(cursor_position_x > 0 && cursor_position_y >= 0)
		    {
			        cursor_position_x--;
				undo.what_char_delete = text[cursor_position_y][cursor_position_x];
		                text[cursor_position_y].erase(text[cursor_position_y].begin() + cursor_position_x);

                                if(static_cast<char>(c) != 'u')
                                {
				         undo.what_operation = del_char_undo;
				         text_history.push(undo);
			        }

			        return;
		    }

		    return;
}

void newline_write(int& level, int& c, int& cursor_position_x, int& cursor_position_y, int& xMax, int& yMax, int& first_line_print, int& last_line_print,std::vector<std::string>& text, std::string& add, std::stack<Undo_struct>& text_history)
{
	                        if(static_cast<char>(c) != 'u')
                                {
	                               Undo_struct undo;
				       undo.what_operation = newline_undo;
				       text_history.push(undo);
				}

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

			        cursor_position_x = 0;
			        cursor_position_y++;
			        text.insert(text.begin() + cursor_position_y,add);
				add.clear();
				add.resize(1);
			        return;
}

void other_char_write(int& level, int& c, int& what_mode, int& cursor_position_x, int& cursor_position_y, int& xMax, int& yMax, int& first_line_print, int& last_line_print, std::vector<std::string>& text, std::stack<Undo_struct>& text_history)
{
	                     if(what_mode == write_mode)
		             {
	                           Undo_struct undo;
	                           undo.what_operation = new_char_undo;
				   undo.what_char_delete = c;
			           text_history.push(undo);
		             }
			    
                             /*if(cursor_position_x + 1 == xMax)
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
			       }*/
		
		             text[cursor_position_y].insert(text[cursor_position_y].begin() + cursor_position_x, c);
			     cursor_position_x++;
}

void undo_change(int& first_line_print, int& last_line_print, int& cursor_position_y, int& cursor_position_x, int& level, int& yMax, int& xMax, std::vector<std::string>& text, std::stack<Undo_struct>& text_history)
{
	 Undo_struct undo;

	 if(!text_history.empty())
         {
	     undo = text_history.top();
             std::string additional;
             int input_key_char = 'u';
             int mode = edit_mode;

	     switch(undo.what_operation)
             {
		     case 1: //case for backspace char.
                     newline_write(level, input_key_char, cursor_position_x, cursor_position_y, xMax, yMax, first_line_print, last_line_print, text, additional,text_history);
		     text_history.pop();
		     break;
                     
		     case 2: //case for newline char.
                        backspace_key_write(level, input_key_char, cursor_position_x, cursor_position_y, xMax, yMax, first_line_print, last_line_print, text, additional, text_history);
		        text_history.pop();
		     break;

		     case 3: //case for write char
                     additional = {};
		     input_key_char = 'u';
                     backspace_key_write(level, input_key_char, cursor_position_x, cursor_position_y, xMax, yMax, first_line_print, last_line_print, text, additional, text_history);
		     text_history.pop();
		     break;

		     case 4: // case for delete char
                     other_char_write(level, undo.what_char_delete, mode, cursor_position_x, cursor_position_y, xMax, yMax, first_line_print, last_line_print, text, text_history);
		     text_history.pop();
		     break;

		     case 5: // case for right key
                     left_key_write(cursor_position_x, cursor_position_y, yMax, first_line_print, last_line_print, text);
                     text_history.pop();
                     undo_change(first_line_print, last_line_print, cursor_position_y, cursor_position_x, level, yMax, xMax, text, text_history);
                     break;

		     case 6: // case for left key
                     right_key_write(cursor_position_y, cursor_position_x, xMax, yMax, first_line_print, last_line_print, text);
                     text_history.pop();
                     undo_change(first_line_print, last_line_print, cursor_position_y, cursor_position_x, level, yMax, xMax, text, text_history);
                     break;
                     
		     case 7: // case for up key
	             down_key_write(cursor_position_y, first_line_print, last_line_print, cursor_position_x, text);
		     text_history.pop();
                     undo_change(first_line_print, last_line_print, cursor_position_y, cursor_position_x, level, yMax, xMax, text, text_history);
                     break;

		     case 8: // case for down key
	             up_key_write(cursor_position_y, first_line_print, last_line_print, cursor_position_x, yMax, text);
		     text_history.pop();
                     undo_change(first_line_print, last_line_print, cursor_position_y, cursor_position_x, level, yMax, xMax, text, text_history);
                     break;
	     }
       }

	 else
         {
	     return;
	 }
}

