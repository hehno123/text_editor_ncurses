#include "variable.h"
#include <iostream>
#include <vector>
#include <string>

void right_key(int& cursor_position_y, int& cursor_position_x, int& xMax, std::vector<std::string>& text)
{
                        if(cursor_position_x < text[cursor_position_y].size())
			{
			     if(cursor_position_x == xMax && text.size() - 1 != cursor_position_y)
		             {
				     cursor_position_x = 0;
				     cursor_position_y++;
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

void left_key(int& cursor_position_x, int& cursor_position_y, std::vector<std::string>& text)
{
                        if(cursor_position_x == 0 && cursor_position_y > 0)
			{
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

void up_key(int& cursor_position_y, int& first_line_print, int& last_line_print, int& cursor_position_x, std::vector<std::string>& text)
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

void down_key(int& cursor_position_y, int& first_line_print, int& last_line_print, int& cursor_position_x, std::vector<std::string>& text)
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

void backspace_key(int& level, int& c, int& cursor_position_x, int& cursor_position_y, int& xMax, int& yMax, int& first_line_print, int& last_line_print, std::vector<std::string>& text, std::string& add)
{
	                
		    if(cursor_position_x == 0 && cursor_position_y == 0)
		    {
				cursor_position_x = 0; 
			        cursor_position_y = 0;
				return;
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
				    return;
				}

				if(cursor_position_y + 1 < text.size() && text[cursor_position_y].size() == 0)
				{
					 bool check = false;

					 if(first_line_print == 0)
					 {
						 last_line_print--;
						 check = true;
				         }
 
                                         if(cursor_position_y == first_line_print && first_line_print > 0 && check == false)
				         {
					           first_line_print--;
					           last_line_print--;
						   check = true;
					 }

					 if(last_line_print >= yMax && last_line_print - first_line_print <= yMax - 1 && text.size() > yMax && check == false)
				         {
						       last_line_print--;
						       check = true;
				         }

					level--;
					text.erase(text.begin() + cursor_position_y);
					cursor_position_y--;
					cursor_position_x = text[cursor_position_y].size();
					return;
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
					return;
				}
				
			        return;
			}

		        
		        if(cursor_position_x > 0 && cursor_position_y >= 0)
		        {
			        cursor_position_x--;
		                text[cursor_position_y].erase(text[cursor_position_y].begin() + cursor_position_x);
			        return;
		        }

			return;
}

void newline(int& level, int& c, int& cursor_position_x, int& cursor_position_y, int& xMax, int& yMax, int& first_line_print, int& last_line_print,std::vector<std::string>& text, std::string& add)
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
			      return;
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
				return;
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

                           return;
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

					return;
			       } 

		    }

			return;
}

void other_char(int& level, int& c, int& cursor_position_x, int& cursor_position_y, int& xMax, int& yMax, int& first_line_print, int& last_line_print, std::vector<std::string>& text)
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
