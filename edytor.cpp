#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <ncurses.h>
#include "variable.h"

void open_file(std::string& file_name, std::vector<std::string>& text, int& yMax, int& last_line_print, int& cursor_position_y)
{   	
        std::fstream MyFile;
	std::string line2;
	MyFile.open(file_name);

	if(MyFile.fail())
	{
		MyFile.open(file_name, std::ios_base::out);
	}

	else
        {
	       
               while (std::getline(MyFile, line2)) 
	       {
                     std::string row;

                     for (char &c : line2) 
		     {   
                         if(c != '\n') 
			 {
                             row.push_back(c);
                         }
                      }

                     text.push_back(row);
	       }        
	}

	 if(text.size() > 1 && MyFile.fail())
	 {
       	    text.erase(text.begin() + 0);
	 }
        
	 MyFile.close();
        
         if(text.size() > yMax)
         {
	       last_line_print = yMax - 1;	
	       cursor_position_y = 0;
	 }

	 else
	 {
		last_line_print = text.size() - 1;
		cursor_position_y = 0;
	 }
}

void write_file(std::string& file_name, std::vector<std::string>& text)
{
	       std::fstream MyFile;
               MyFile.open(file_name);

	       for(int j = 0; j < text.size(); j++)
	       {
	           for(int i = 0; i < text[j].size(); i++)
	           {
	                 MyFile << text[j][i];
	           }

		       MyFile << '\n';
	       } 
 
               MyFile.close();
}

void print_text(std::string& file_name, int& first_line_print, int& last_line_print, int& cursor_position_y, int& cursor_position_x, std::vector<std::string>& text,bool& what_mode, int& yMax, int& xMax)
{
	  start_color();
	  
          for(int j = first_line_print; j <= first_line_print + yMax - 1; j++)
          {
		        if(j <= text.size() - 1)
		        {
		           attrset(COLOR_PAIR(0));
                           printw(text[j].c_str());
			   printw("%c", '\n');
			}

			else
		        {
                            init_pair(1, COLOR_BLUE, COLOR_BLACK);
		            attrset(COLOR_PAIR(1)); 
		            printw("~");
		            printw("%c", '\n');
		            refresh();
			}	            	
	  }
	  
	   refresh(); 
	   refresh();
           attrset(COLOR_PAIR(0));
	   move(yMax , 0);
	   
	   if(what_mode == true)
           {
		  printw("WRITE_MODE     ");
           }

	   else
           {
		  printw("EDIT_MODE      ");
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

           move(cursor_position_y - first_line_print, cursor_position_x);
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
        bool what_mode = true;
        int level = 1;
	std::vector<std::string> text(1);
	std::string add{};
	int cursor_position_x = 0, cursor_position_y = 0;
	int xMax = 0;
	int yMax = 0;
	int first_line_print = 0, last_line_print = 0;
        
	getmaxyx(stdscr, yMax, xMax);
	yMax--;

	if(argc > 1)
        {
	    file_name = argv[1];
        }

	open_file(file_name, text, yMax, last_line_print, cursor_position_y);
	
	while(true)
	{
		   print_text(file_name, first_line_print, last_line_print, cursor_position_y, cursor_position_x, text, what_mode, yMax, xMax);
		   int input_key = getch();
		  
	           if(input_key == 27)
	           {
	              break;
	           }
          
		  switch(input_key)
		  {
		        case KEY_RIGHT:
                                right_key(cursor_position_y, cursor_position_x, xMax, text);
			        break;

		        case KEY_LEFT:
                                  left_key(cursor_position_x, cursor_position_y, text);
			          break;

		        case KEY_UP:
		                 up_key(cursor_position_y, first_line_print, last_line_print, cursor_position_x, text);                       
			         break;
			         
		        case KEY_DOWN:
                                 down_key(cursor_position_y, first_line_print, last_line_print, cursor_position_x, text);
			         break;

		        case KEY_BACKSPACE:
			         backspace_key(level, input_key, cursor_position_x, cursor_position_y, xMax, yMax, first_line_print, last_line_print, text, add);
			         break;

			    case 127:
			         backspace_key(level, input_key, cursor_position_x, cursor_position_y, xMax, yMax, first_line_print, last_line_print, text, add);
			         break;
   
		        case '\n':
			        newline(level, input_key, cursor_position_x, cursor_position_y, xMax, yMax, first_line_print, last_line_print, text, add);
			        break;

		        default:
			        other_char(level, input_key, cursor_position_x, cursor_position_y, xMax, yMax, first_line_print, last_line_print, text);
			        break;
          }
                   add = {};
	           refresh();
                   clear();
                   refresh();
    }
                
	        write_file(file_name, text);
                endwin();
	        return 0;
}
