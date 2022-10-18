#include <iostream>
#include <vector>
#include <string>
#include "variable.h"
#include "copy_variable.h"

void right_key_visual(int& cursor_position_y, int& cursor_position_x, int& xMax, int& yMax, int& first_line_print, int& last_line_print, std::vector<std::string>& text, Visual_struct& visual_structure)
{
                      right_key_write(cursor_position_y, cursor_position_x, xMax, yMax, first_line_print, last_line_print, text);
		      visual_structure.change_line_non_static(cursor_position_y);
		      visual_structure.change_x_position_non_static(cursor_position_x);
}

void left_key_visual(int& cursor_position_x, int& cursor_position_y, int& yMax, int& first_line_print, int& last_line_print, std::vector<std::string>& text,
Visual_struct& visual_structure)
{
	              left_key_write(cursor_position_x, cursor_position_y, yMax, first_line_print, last_line_print, text);

		      if(visual_structure.get_line_non_static() > cursor_position_y)
		      {
                               visual_structure.change_first_line_print(first_line_print);
		      }

		      visual_structure.change_line_non_static(cursor_position_y);
		      visual_structure.change_x_position_non_static(cursor_position_x);
}

void up_key_visual(int& cursor_position_y, int& first_line_print, int& last_line_print, int& cursor_position_x, int& yMax, std::vector<std::string>& text, Visual_struct& visual_structure)
{
	              up_key_write(cursor_position_y, first_line_print, last_line_print, cursor_position_x, yMax, text);

                      if(visual_structure.get_line_non_static() > cursor_position_y)
		      {
                               visual_structure.change_first_line_print(first_line_print);
		      }

		      visual_structure.change_line_non_static(cursor_position_y);
		      visual_structure.change_x_position_non_static(cursor_position_x);
}

void down_key_visual(int& cursor_position_y, int& first_line_print, int& last_line_print, int& cursor_position_x, std::vector<std::string>& text, Visual_struct& visual_structure)
{
	              down_key_write(cursor_position_y, first_line_print, last_line_print, cursor_position_x, text);
		      visual_structure.change_line_non_static(cursor_position_y);
		      visual_structure.change_x_position_non_static(cursor_position_x);
                      visual_structure.change_first_line_print(first_line_print);
}

void copy_to_buffer_visual(std::vector<std::string>& text, Visual_struct& visual_structure)
{
                      int max_value_line;
		      int min_value_line;            
		      int min_value_x;
		      int max_value_x;
                      
		      visual_structure.max_value_visual(max_value_line, min_value_line, max_value_x, min_value_x);

		      int what_index_in_copied_vector = 0;

		      for(int j = min_value_line; j <= max_value_line; j++)
		      {
			                    std::string copied_buffer;

				            if(j == max_value_line || j == min_value_line)
				            {
						       int min_value_x_copy;
						       int max_value_x_copy;

						       if(max_value_line == j && min_value_line == j)
						       {
							       min_value_x_copy = min_value_x;
							       max_value_x_copy = max_value_x;
                                                       }

						       if(max_value_line == j && min_value_line != j)
						       {
							       max_value_x_copy = max_value_x;
							       min_value_x_copy = 0;
						       }

						       if(max_value_line != j && min_value_line == j)
						       {
							       min_value_x_copy = min_value_x_copy;
							       max_value_x_copy = text[j].size();
						       }
                                                       
						       for(int i = min_value_x_copy; i < text[j].size(); i++)
						       {
                                                               copied_buffer.push_back(text[j][i]);
						       }
				             }

					     else
				             {
                                                       copied_buffer = text[j];
					     }

					     visual_structure.copied_text.push_back(copied_buffer);
				     
		      }

}

void paste_visual(int& cursor_position_y, int& cursor_position_x, int& xMax, int& yMax, int& last_line_print, std::vector<std::string>& text, Visual_struct& visual_structure)
{
	          int max_value_line = std::max(visual_structure.get_line_static(), visual_structure.get_line_non_static());
		  int min_value_line = std::min(visual_structure.get_line_static(), visual_structure.get_line_non_static());

		  int what_index_in_text = text[cursor_position_y].size();
                  int what_index_on_copied_vector = 0;
		  int where_is_cursor_x = cursor_position_x;
		  int where_is_cursor_y = cursor_position_y;
		  std::string buffer;

	          for(int i = 0; i < visual_structure.copied_text[0].size(); i++)
		  {
			  text[cursor_position_y].insert(text[cursor_position_y].begin() + where_is_cursor_x, visual_structure.copied_text[0][i]);
			  where_is_cursor_x++;
                  }

		  if(text[cursor_position_y].size() >= xMax - 1)
	          {
			  for(int i = text[cursor_position_y].size() - 1; i >= xMax - 1; i--)
		          {
				  buffer.insert(buffer.begin() + 0, text[cursor_position_y][i]);
				  text[cursor_position_y].pop_back();
		          }

		  }

                   if(min_value_line != max_value_line)
	           {
	                 for(int i = 1; i < visual_structure.copied_text.size(); i++)
	                 {
	                         where_is_cursor_y++;
	                         text.insert(text.begin() + where_is_cursor_y, visual_structure.copied_text[i]);

				 if(last_line_print < yMax - 1)
			         {
					 last_line_print++;
			         }
                         } 
                   }

                   if(text[where_is_cursor_y].size() + buffer.size() >= xMax - 1)
		   {
			   text.insert(text.begin() + where_is_cursor_y + 1, buffer);
                           
                           if(last_line_print < yMax - 1)
			   {
				last_line_print++;
			   }
	           }

		   else if(text[where_is_cursor_y].size() + buffer.size() < xMax - 1)
	           {
			   for(int i = 0; i < buffer.size(); i++)
		           {
				   text[where_is_cursor_y].push_back(buffer[i]);
			   }

                           if(last_line_print < yMax - 1)
			   {
					 last_line_print++;
			   }

		   }
}

void delete_visual(int& first_line_print, int& last_line_print, int& yMax, int& cursor_position_y, int& cursor_position_x, std::vector<std::string>& text, Visual_struct& visual_structure)
{
	          int max_value_line = std::max(visual_structure.get_line_static(), visual_structure.get_line_non_static());
		  int min_value_line = std::min(visual_structure.get_line_static(), visual_structure.get_line_non_static());

		  for(int i = min_value_line; i <= max_value_line; i++)
	          {
			  text.erase(text.begin() + min_value_line);
	          }


	          first_line_print = visual_structure.get_first_line();
	          
		  if(first_line_print + yMax >= text.size())
	          {
			  last_line_print = text.size() - 1;
	          }

		  if(first_line_print + yMax < text.size())
		  {
			  last_line_print = first_line_print + yMax - 1;
	          }

	          if(min_value_line != 0)
		  {
		         cursor_position_y = min_value_line - 1;
		  }

		  else
	          {
			 cursor_position_y = 0;
	          }

	          cursor_position_x = 0;
}

void pre_search(std::string& search_value, std::vector<int>& lps) 
{
        int length = 0;
        lps[0] = 0;   
        int i = 1;

        while (i < search_value.size()) 
	{
            if (search_value[i] == search_value[length]) 
	    {
                length++;
                lps[i] = length;
                i++;
            }
                
	    else if (length != 0) 
            {
                    length = lps[length - 1];
            }

            else             
            {
                    lps[i] = 0;
                    i++;
            }
        }
}

void search_in_text(int& first_line_print, int& last_line_print, int& yMax, int& xMax, int& cursor_position_y, int& cursor_position_x, std::string& search_value, std::vector<std::string>& text)
{
	int size_of_search_text = search_value.size();
    
	if(size_of_search_text == 0)
        {
		return;
	}

	for(int i = 0; i < text.size(); i++)
	{
		int size_of_text = text[i].size();
		std::vector<int> lps(size_of_search_text);

		if(size_of_search_text > text[i].size())
		{
			continue;
		}

                pre_search(search_value, lps);

		int k = 0;
                int j = 0;

                while (j < size_of_text) 
		{
                       if(search_value[k] == text[i][j]) 
		       {
                                k++;
                                j++;
                       }
  
                       if (j == size_of_search_text) 
		       { 
                              cursor_position_y = i;  
	                      cursor_position_x = j - k;

	                      if(cursor_position_y - (yMax - 1) / 2 >= 0)
	                      {
		                       first_line_print = cursor_position_y - (yMax - 1) / 2;
		              }

                              else
	                      {
	                               first_line_print = 0;
	                      }
                              
                              if(first_line_print + yMax <= text.size())
	                      {
	                               last_line_print = first_line_print + yMax - 1;
	                      }
                              
                              else
	                      {
	                               last_line_print = text.size() - 1;
	                      }			       
		       }

		       if (k != 0 && j < size_of_text && search_value[k] != text[i][j])
		       {
                             k = lps[k - 1];
		       }

                       else if(k == 0 && j < size_of_text && search_value[k] != text[i][j])
		       {
                               k++;     
		       }
                 }
	}
}
		            	    

