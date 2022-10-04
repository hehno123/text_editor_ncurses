#ifndef WRITE_MOD_H
#define WRITE_MOD_H
#include "variable.h"

int right_key()
{
                        if(cursor_position_x < text[cursor_position_y].size())
			{
			     if(cursor_position_x == xMax)
		             {
				     cursor_position_x = 0;
		             }
			     
			     else
		             {
                                cursor_position_x++;
			     }
			}

			return hellping;
}

int left_key()
{
                        if(cursor_position_x > 0)
			{
				cursor_position_x--;
			}

			return hellping;
}

int up_key()
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
					return hellping;
				}

				cursor_position_y--;	
			}

			return hellping;
}

int down_key()
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
					return hellping;
		         	}

			        cursor_position_y++;
			}

			return hellping;
}

int backspace_key()
{
	                
			if(cursor_position_x == 0 && cursor_position_y == 0)
			{
				cursor_position_x = 0; 
			        cursor_position_y = 0;
				return hellping;
			}

		        if(cursor_position_x == 0 && cursor_position_y > 0)
			{ 
				if(cursor_position_y + 1 == text.size() && text[cursor_position_y].size() == 0)
				{
                                    if(last_line_print >= yMax)
				    { 
					first_line_print--;
					last_line_print--;
				    }

			            cursor_position_y--;
				    cursor_position_x = text[cursor_position_y].size();
				    level--;
				    text.pop_back();
				    return hellping;
				}

				if(cursor_position_y + 1 <= text.size() && text[cursor_position_y].size() == 0)
				{
                                        if(cursor_position_y == first_line_print && first_line_print > 0)
				        {
					    first_line_print--;
					    last_line_print--;
					}

					if(last_line_print <= yMax - 1 && cursor_position_y < yMax && text.size() <= yMax)
				        {
						last_line_print--;
				        }

					level--;
					text.erase(text.begin() + cursor_position_y);
					cursor_position_y--;
					cursor_position_x = text[cursor_position_y].size();
					return hellping;
				}

				if(cursor_position_y + 1 <= text.size() && text[cursor_position_y].size() != 0)
				{
					for(int i = 0; i < text[cursor_position_y].size(); i++)
					{
						text[cursor_position_y - 1].push_back(text[cursor_position_y][i]);
					}

					level--;
					text.erase(text.begin() + cursor_position_y);

                                        if(last_line_print >= yMax)
				        {
					   first_line_print--;
					   last_line_print--;
				        }

					else
				        {
					   last_line_print--;
					}

					cursor_position_x = text[cursor_position_y - 1].size() - text[cursor_position_y].size();
					cursor_position_y--;
					return hellping;
				}
				
			        return hellping;
			}

		        
		        if(cursor_position_x > 0 && cursor_position_y >= 0)
		        {
			    cursor_position_x--;
		            text[cursor_position_y].erase(text[cursor_position_y].begin() + cursor_position_x);
			    return hellping;
		        }

			return hellping;
}

int newline()
{
                      if(cursor_position_y + 1 == text.size() && cursor_position_x == text[cursor_position_y].size())
		      {
		      	 cursor_position_y++;
			 cursor_position_x = 0;
			 level++;
			 text.push_back(add);
                         last_line_print++;

                         if(last_line_print - yMax == first_line_print)
			 {
			      first_line_print++;
			 }
			       
			 add.clear();
			 add.resize(1);
			 return hellping;
		      }

			if(cursor_position_y + 1 < text.size() && cursor_position_x == text[cursor_position_y].size())
			{
				cursor_position_y++;
				cursor_position_x = 0;
				level++;

                               if(text.size() < yMax)
		               {
			          last_line_print++;
		               }

                               if(last_line_print - yMax == first_line_print)
			       {
			          first_line_print++;
			       }
                               
			     
				text.insert(text.begin() + cursor_position_y, add);
				add.clear();
				add.resize(1);
				return hellping;
			}

	    		if(cursor_position_y + 1 <= text.size() && text[cursor_position_y].size() > cursor_position_x)
			{
				for(int i = cursor_position_x; i <= text[cursor_position_y].size(); i++)
				{
				    add.push_back(text[cursor_position_y][i]);
			        }

				add.pop_back();
				add.erase(add.begin());

				for(int i = 1; i <= add.size(); i++)
				{
				        	text[cursor_position_y].pop_back();	
				}
	
                              	if(cursor_position_y + 1 == text.size())
				{
			          cursor_position_x = 0;
				  cursor_position_y++;
			 	  text.push_back(add);
				  add.clear();
				  add.resize(1);

                                if(text.size() < yMax)
		                {
			           last_line_print++;
		                }

				if(text.size() >= yMax)
				{
				   last_line_print++;
				   first_line_print++;
				}

                                if(last_line_print - yMax == first_line_print)
			        {
			           first_line_print++;
			        } 

                                  return hellping;
				} 

				if(cursor_position_y + 1 < text.size())
				{
					cursor_position_x = 0;
					cursor_position_y++;
					text.insert(text.begin() + cursor_position_y,add);
					add.clear();
					add.resize(1);

                                        if(text.size() < yMax)
		                        {
			                   last_line_print++;
		                        }

				        if(text.size() >= yMax)
				        {
				           last_line_print++;
				           first_line_print++;
				        } 

                                        if(last_line_print - yMax == first_line_print)
			                {
			                   first_line_print++;
			                } 

					return hellping;
				} 

		       }

			return hellping;
}

int other_char()
{
                        if(cursor_position_y == xMax)
		        {
			    if(cursor_position_y + 1 == text.size())
		            {
				    level++;
				    text.push_back(add);
				    text[cursor_position_y + 1][0] = c;
                                    last_line_print++;
				    cursor_position_x = 0;
				    cursor_position_y;

				    if(last_line_print - yMax + 1 > first_line_print)
				    {
					    first_line_print++;
				    }

				    return hellping;
			    }

			    else
		            {
			     cursor_position_y++;
			     text.insert(text.begin() + cursor_position_y, add);
			     text[cursor_position_y].push_back(c);
			     cursor_position_x++;
			    }
			}

			else
		       {
		         text[cursor_position_y].insert(text[cursor_position_y].begin() + cursor_position_x, c);
			 cursor_position_x++;
		       }
		       
			return hellping;
}

#endif
