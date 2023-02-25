#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <ncurses.h>
#include <stdlib.h>
#include "variable.h"
#include "copy_variable.h"
#include "syntax_highlighter.h"

void printString(std::string name, int minRange, int xMax, int array_color[])
{
	  int index = minRange;
          int i = minRange + xMax - 1;
          int array_index = 0;

	  while(minRange < name.size() && minRange <= i)
	  {
		   attrset(COLOR_PAIR(array_color[array_index]));
		   printw("%c", name[minRange]);
		   minRange++;
		   array_index++;
          }

          if(i >= name.size() - 1 || name.size() == 0)
	  { 
	       printw("%c", '\n');
	  }
}

void printVisualString(std::string name, int minRange, int xMax, int minLine, int maxLine)
{
	  int index = minRange;
          int i = minRange + xMax - 1;

	  while(minRange < name.size() && minRange <= i)
	  {
                   if(minRange >= minLine && minRange <= maxLine)
		   {
                           init_pair(2, COLOR_WHITE, COLOR_RED); 
			   attrset(COLOR_PAIR(2));
		   }

		   else
	           {
                           attrset(COLOR_PAIR(0));
	           }

		   printw("%c", name[minRange]);
		   minRange++;
          }

          if(i >= name.size() - 1)
	  { 
	       printw("%c", '\n');
	  }
}

void print_text(std::string& file_name, int& first_line_print, int& last_line_print, int& cursor_position_y, int& cursor_position_x, std::vector<std::string>& text, int& what_mode, int& yMax, int& xMax, int& copy_cursor_position_x, std::string& search_value, Visual_struct& visual_structure, int& minRangeX, int& maxRangeX)
{
	  start_color();

	  short foreground_terminal_color;
	  short background_terminal_color;

	  pair_content(0, &foreground_terminal_color, &background_terminal_color);
          init_pair(2, COLOR_WHITE, COLOR_RED);
          init_pair(1, COLOR_BLUE, background_terminal_color);
	  init_pair(3, COLOR_YELLOW, background_terminal_color);
          init_pair(4, COLOR_GREEN, background_terminal_color);
          init_pair(5, COLOR_MAGENTA, background_terminal_color);

          int array_color[yMax + 1][xMax + 1];
          int index_in_color_array = 0;
	  int index_in_color_array_x = 0;
	  bool is_char_in_string = false;
          
	/*
          for(int i = first_line_print; i <= first_line_print + yMax - 1; i++)
          {
		  if(i < text.size())
	          {
		      std::string name = "";
                             
		      for(int j = minRangeX; j <= maxRangeX && j < text[i].size(); j++)
		      {
		
			      if(text[i][j] == 34)
			      {
				       if(is_char_in_string)
				       {
					       is_char_in_string = false;
				       }

				       else
				       {
					       is_char_in_string = true;
				       }

				       array_color[index_in_color_array][index_in_color_array_x] = 5;
	                      }
                              
			      if(is_char_in_string)
		              {
				       array_color[index_in_color_array][index_in_color_array_x] = 5;
			      }
                              
			      if(text[i][j] == ' ' && !is_char_in_string)
		              {
				       name.clear();
				       array_color[index_in_color_array][index_in_color_array_x] = 0;
			      }
                              
			      if(text[i][j] != ' ' && text[i][j] != 34 && !is_char_in_string)
		              {
				      name.push_back(text[i][j]);
				      array_color[index_in_color_array][index_in_color_array_x] = 0;
			      }

			      for(int k = 0; k < variable_types_cpp.size(); k++)
			      {
				      if(name == variable_types_cpp[k])
				      {
					      for(int m = j - name.size() + 1; m <= j; m++)
				              {
						      array_color[index_in_color_array][m] = 4;
					      }
				      }
			      }

                              for(int k = 0; k < word_reserved_cpp.size(); k++)
			      {
				      if(name == word_reserved_cpp[k])
				      {
					      for(int m = j - name.size() + 1; m <= j; m++)
				              {
						      array_color[index_in_color_array][m] = 3;
					      }
				      }
			      }

                              for(int k = 0; k < macro_cpp.size(); k++)
			      {
				      if(name == macro_cpp[k])
				      {
					      for(int m = j - name.size() + 1; m <= j; m++)
				              {
						      array_color[index_in_color_array][m] = 1;
					      }

				      }
			      }

                              index_in_color_array_x++;
 		      }
		}

		else
                {
			array_color[index_in_color_array][0] = 1;
	        }


		index_in_color_array++;
	  } */

	  if(cursor_position_x < minRangeX)
	  {
		  minRangeX = cursor_position_x;
                  maxRangeX = minRangeX + xMax - 1;
          }

	  else if(cursor_position_x > maxRangeX)
          {
		  maxRangeX = cursor_position_x;
		  minRangeX = maxRangeX - xMax + 1;
	  }
          
	  index_in_color_array = 0;

	  for(int j = first_line_print; j <= first_line_print + yMax - 1; j++)
          {
	                if(j <= text.size() - 1)
		        {
			     attrset(COLOR_PAIR(0));

		             if(what_mode != visual_mode)
	                     {			     
			         printw(text[j].c_str());
			         printw("%c", '\n');
				 //printString(text[j], minRangeX, xMax, array_color[index_in_color_array]);
		             }

			     if(what_mode == visual_mode)
		             {
				     int max_value_line;
				     int min_value_line;
				     int min_value_x;
				     int max_value_x;

				     visual_structure.max_value_visual(max_value_line, min_value_line, max_value_x, min_value_x);
                              
				     if(j == max_value_line || j == min_value_line)
				     {
					              if(text[j].size() == 0)
					              { 
                                                          init_pair(2, COLOR_WHITE, COLOR_RED);
							  attrset(COLOR_PAIR(2));
							  printw(" ", minRangeX, xMax);
					              } 

                                                       int min_value_x_copy;
						       int max_value_x_copy;

						       if(max_value_line == j && min_value_line == j)
						       {
							       min_value_x_copy = min_value_x;
							       max_value_x_copy = max_value_x;
                                                       }

						       if(max_value_line == j && min_value_line < j)
						       {
							       max_value_x_copy = max_value_x;
							       min_value_x_copy = 0;
						       }

						       if(max_value_line > j && min_value_line == j)
						       {
							       min_value_x_copy = min_value_x;
							       max_value_x_copy = text[j].size() - 1;
						       }

                                                  /*for(int i = minRangeX; i < text[j].size() || i <= maxRangeX; i++)
					          {
						       if(i >= min_value_x_copy && i <= max_value_x_copy)
						       {
                                                             init_pair(2, COLOR_WHITE, COLOR_RED);
							     attrset(COLOR_PAIR(2));
							     printw("%c", text[j][i]);
						       }

						       else
						       {
							     attrset(COLOR_PAIR(0));
							     printw("%c", text[j][i]);
						       } 
				                 }

					         if(maxRangeX >= text[j].size() - 1)
				                 {
							 printw("%c", '\n');
						 }*/
						 
					         printVisualString(text[j], minRangeX, xMax, min_value_x_copy, max_value_x_copy);
				     }


				     else if(j > min_value_line && j < max_value_line)
			             {
                                             init_pair(2, COLOR_WHITE, COLOR_RED);
					     attrset(COLOR_PAIR(2));
					     
					     if(text[j].size() == 0)
					     {
						     printString(" ", minRangeX, xMax, array_color[index_in_color_array]);
					     }

					     else
				             {
						     printString(text[j], minRangeX, xMax, array_color[index_in_color_array]);
					     }
				     }

				     else
		                     {
					     printString(text[j], minRangeX, xMax, array_color[index_in_color_array]);
				     }
			  }

		   } 

                        else
		        {
                            //
			    //init_pair(1, COLOR_BLUE, 0);
		            attrset(COLOR_PAIR(1)); 			   
			    printw("~");
		            printw("%c", '\n');
			    //printString("~", minRangeX, xMax, array_color[index_in_color_array]);
		            refresh();
			}

                        index_in_color_array++;			
	  }
	  
	   refresh();
	   attrset(COLOR_PAIR(0)); 
	   move(yMax , 0);

	   if(what_mode == search_mode)
           {
	          printw("/");
                  printw(search_value.c_str());
                  move(yMax, copy_cursor_position_x); 
		  return;
	   }
           
           else	
	   {   
	            if(what_mode == write_mode)
                    {
		           printw("WRITE_MODE     ");
                    }

	            else if(what_mode == edit_mode)
                    { 
		           printw("EDIT_MODE      ");
                    }

	            else if(what_mode == visual_mode)
	            {
		           printw("VISUAL_MODE   ");
                    }

	            printw("FILE_NAME: ");

	            if(file_name.size() == 0)
                    {
		         printw("no name");
                    }
 
	            else
	            {
	                printw(file_name.c_str());
	            } 
 
	            move(yMax, xMax - xMax / 6);
	            printw("%d" "%c" "%d", cursor_position_y, ',', cursor_position_x);
           }

           move(cursor_position_y - first_line_print, cursor_position_x - minRangeX);
           //printw("%d" "%c" "%d" "%c" "%d" "%c" "%d" "%c" "%d" "%c" "%d" "%c" "%d", cursor_position_y, ' ', cursor_position_x, ' ', first_line_print, ' ', last_line_print, ' ', text.size(), ' ', minRangeX, ' ', maxRangeX);
}

int main(int argc, char** argv)
{	
	initscr();
        raw();
	cbreak();
	noecho();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);

	std::string file_name;
	bool editor_work = true;
        int what_mode = write_mode;
        int level = 1;
	std::vector<std::string> text(1);
	std::string add{};
	int cursor_position_x = 0, cursor_position_y = 0;
	int xMax = 0;
	int yMax = 0;
	int first_line_print = 0, last_line_print = 0; 
	std::stack<Undo_struct> text_history;
	Visual_struct visual_structure;
	std::string search_value;
	int copy_cursor_position_x;
        
	getmaxyx(stdscr, yMax, xMax);
	yMax--;
        
	int minRangeX = 0;
	int maxRangeX = xMax - 1;
	
	//int color_array[yMax + 1][xMax + 1];

	if(argc > 1)
        {
	    file_name = argv[1];
        }

	open_file(file_name, text, yMax, last_line_print, cursor_position_y, cursor_position_x, first_line_print);
	
	while(editor_work)
	{
		   print_text(file_name, first_line_print, last_line_print, cursor_position_y, cursor_position_x, text, what_mode, yMax, xMax, copy_cursor_position_x, search_value,  visual_structure, minRangeX, maxRangeX);
		   int input_key = getch();
		  
		  if(what_mode == write_mode)
	          {
                      Undo_struct undo_struct_copy;

		      switch(input_key)
		      {

		        case KEY_RIGHT:
                                 right_key_write(cursor_position_y, cursor_position_x, xMax, yMax, first_line_print, last_line_print, text);
				 undo_struct_copy.what_operation = right_key_undo;
				 text_history.push(undo_struct_copy);
			         break;

		        case KEY_LEFT:
                                  left_key_write(cursor_position_x, cursor_position_y, yMax, first_line_print, last_line_print, text);
                                  undo_struct_copy.what_operation = left_key_undo;
				  text_history.push(undo_struct_copy);
			          break;

		        case KEY_UP:
		                 up_key_write(cursor_position_y, first_line_print, last_line_print, cursor_position_x, yMax, text);
	                         undo_struct_copy.what_operation = up_key_undo;
				 text_history.push(undo_struct_copy);
			         break;
			         
		        case KEY_DOWN:
                                 down_key_write(cursor_position_y, first_line_print, last_line_print, cursor_position_x, text);
				 undo_struct_copy.what_operation = down_key_undo;
				 text_history.push(undo_struct_copy);
			         break;

		        case KEY_BACKSPACE:
			         backspace_key_write(level, input_key, cursor_position_x, cursor_position_y, xMax, yMax, first_line_print, last_line_print, text, add, text_history);
			         break;

			case 127:
			         backspace_key_write(level, input_key, cursor_position_x, cursor_position_y, xMax, yMax, first_line_print, last_line_print, text, add, text_history);
			         break;
   
		        case '\n':
			        newline_write(level, input_key, cursor_position_x, cursor_position_y, xMax, yMax, first_line_print, last_line_print, text, add,text_history);
			        break;
 
			case KEY_IC:
                               what_mode = edit_mode;
			       break;

		        default:
			        other_char_write(level, input_key, what_mode, cursor_position_x, cursor_position_y, xMax, yMax, first_line_print, last_line_print, text, text_history);
			        break;
                       }
		 }

                 else if(what_mode == edit_mode)
	         {
                         Undo_struct undo_struct_copy;

			 switch(input_key)
		         {
			       case KEY_IC:
			            what_mode = write_mode;
			            break;
			       
			       case 's':
                                    write_file(file_name, text);
				    break;

			       case 27:
			            editor_work = false;
			            break;
			      
			       case KEY_RIGHT:
                                    right_key_write(cursor_position_y, cursor_position_x, xMax, yMax, first_line_print, last_line_print, text); 
				    undo_struct_copy.what_operation = right_key_undo;
				    text_history.push(undo_struct_copy);
			            break;

		               case KEY_LEFT:
                                    left_key_write(cursor_position_x, cursor_position_y, yMax, first_line_print, last_line_print, text);
				    undo_struct_copy.what_operation = left_key_undo;
				    text_history.push(undo_struct_copy);
			            break;

		               case KEY_UP:
		                    up_key_write(cursor_position_y, first_line_print, last_line_print, cursor_position_x, yMax, text); 
                                    undo_struct_copy.what_operation = up_key_undo;
				    text_history.push(undo_struct_copy);
			            break;
			         
		               case KEY_DOWN:
                                    down_key_write(cursor_position_y, first_line_print, last_line_print, cursor_position_x, text);
                                    undo_struct_copy.what_operation = down_key_undo;
				    text_history.push(undo_struct_copy);
			            break;
			       
			       case 'w':
				    what_mode = visual_mode;
				    visual_structure.change_line_non_static(cursor_position_y);
				    visual_structure.change_line_static(cursor_position_y);
				    visual_structure.change_x_position_non_static(cursor_position_x);
				    visual_structure.change_x_position_static(cursor_position_x);
				    visual_structure.change_first_line_print(first_line_print);
				    visual_structure.copied_text.clear();
				    break;

			       case 'p':
				    paste_visual(cursor_position_y, cursor_position_x, xMax, yMax, last_line_print, text, visual_structure);
				    break;
			       
			       case '/':
				    what_mode = search_mode;
				    copy_cursor_position_x = 1;
				    break;

			       case 'u':
				    undo_change(first_line_print, last_line_print, cursor_position_y, cursor_position_x, level, yMax, xMax, text, text_history);
			            break;
		         }
	         }
                 
		 else if(what_mode == visual_mode)
	         {
			 switch(input_key)
		         {
				 case KEY_IC:
				 what_mode = edit_mode;
				 break;

				 case 'd':
				 right_key_visual(cursor_position_y, cursor_position_x, xMax, yMax, first_line_print, last_line_print, text, visual_structure);
				 break;

				 case KEY_RIGHT:
                                 right_key_visual(cursor_position_y, cursor_position_x, xMax, yMax, first_line_print, last_line_print, text, visual_structure);
                                 break;

				 case 'a':
			         left_key_visual(cursor_position_x, cursor_position_y, yMax, first_line_print, last_line_print, text, visual_structure);
				 break;

				 case KEY_LEFT:
                                 left_key_visual(cursor_position_x, cursor_position_y, yMax, first_line_print, last_line_print, text, visual_structure);
				 break;

				 case 'w':
				 up_key_visual(cursor_position_y, first_line_print, last_line_print, cursor_position_x, yMax, text, visual_structure);
				 break;

				 case KEY_UP:
				 up_key_visual(cursor_position_y, first_line_print, last_line_print, cursor_position_x, yMax, text, visual_structure);
				 break;

				 case 's':
				 down_key_visual(cursor_position_y, first_line_print, last_line_print, cursor_position_x, text, visual_structure);
				 break;

				 case KEY_DOWN:
                                 down_key_visual(cursor_position_y, first_line_print, last_line_print, cursor_position_x, text, visual_structure);
				 break;

				 case 'c':
				 copy_to_buffer_visual(text, visual_structure);
                                 what_mode = write_mode;
			         break;

				 case KEY_BACKSPACE:
				 delete_visual(first_line_print, last_line_print, yMax, cursor_position_y, cursor_position_x, text, visual_structure);
				 what_mode = write_mode;
				 break; 

                                 case 127:
				 delete_visual(first_line_print, last_line_print, yMax, cursor_position_y, cursor_position_x, text, visual_structure);
				 what_mode = write_mode;
				 break; 

		         }
				      
 	         }

		 else if(what_mode == search_mode)
		 {
			 switch(input_key)
			 {
			        case '\n':
				search_in_text(first_line_print, last_line_print, yMax, xMax, cursor_position_y, cursor_position_x, search_value, text);
				search_value.clear();
				what_mode = write_mode;
				break;

				case 27:
				search_value.clear();
				what_mode = write_mode;
				break;
			        
				case KEY_IC:
				what_mode = edit_mode;
				search_value.clear();
				break;

				case KEY_BACKSPACE:

				if(copy_cursor_position_x > 1)
				{
			           search_value.pop_back();
                                   copy_cursor_position_x--;
				}

				break;
                                
				case KEY_LEFT:

                                if(copy_cursor_position_x > 1)
				{
					copy_cursor_position_x--;
				}

				break;

				case KEY_RIGHT:

				if(copy_cursor_position_x < search_value.size())
			        {
					copy_cursor_position_x++;
				}

				break;

		                default:
			        search_value.push_back(input_key);
				copy_cursor_position_x++;
			        break;
			 }
	          }

                   add = {};
		   
                   for(int i = first_line_print; i <= last_line_print; i++)
                   {
		      std::string name = "";

		      for(int j = 0; j < text[i].size(); j++)
		      {
			      if(text[i][j] == ' ')
		              {
				       name.clear();
			      }
                              
			      else
		              {
				      name.push_back(text[i][j]);
			      }

			      if(name == "for")
			      {
				      mvchgat(i, j - 2, name.size(), A_BLINK, 1, NULL);
				      printw("nigger");
				      refresh();
			      }
		      }
	           }

	           refresh();
                   clear();
                   refresh();
    }
                
	        endwin();
	        return 0;
}
