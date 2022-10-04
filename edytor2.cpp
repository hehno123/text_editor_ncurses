#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ncurses.h>
#include "write_mod.h"

void open_file(std::string& name)
{   	
        std::fstream MyFile;
	std::string line2;
	MyFile.open(name);

	if(MyFile.fail())
	{
		MyFile.open(name, std::ios_base::out);
	}

	else
        {
	       
               while (std::getline(MyFile, line2)) 
	       {
                      std::vector<char> row;

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
        
        first_line_print = 0;
        cursor_position_x = 0;
	MyFile.close();
        
        if(text.size() > yMax)
        {
	   last_line_print = yMax - 1;	
	   cursor_position_y = 0;
	}

	else
	{
		last_line_print = text.size() - 1;
		cursor_position_y= 0;
	}
}

void write_file(std::string& name)
{
	       std::fstream MyFile;
               MyFile.open(name);

	       for(int j = 0; j < text.size(); j++)
	       {
	           for(int i = 0; i < text[j].size(); i++)
	           {
			 if(text[j][i] == (char)(0))
	                 {
		         }

			 else
		         {
	                     MyFile << text[j][i];
			 }
	           }

		   MyFile << '\n';
	       } 
 
               MyFile.close();
}



int main(int argc, char** argv)
{	
	initscr();
        raw();
	cbreak();
	noecho();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);

	getmaxyx(stdscr, yMax, xMax);
	std::string name{};

	if(argc > 1)
        {
	    name = argv[1];
        }

	open_file(name);
	
	while(true)
	{
		for(int j = first_line_print; j <= last_line_print; j++)
		{
			if(j > 0)
			{
				move(move_y, move_x);
			}

			for(int i = 0; i < text[j].size(); i++)
			{
				printw("%c", text[j][i]);
				refresh();
			}

			move_y++;
		}

	           refresh();
	           move(cursor_position_y - first_line_print, cursor_position_x);
	
	           move_y = 0;
		   c = getch();
		  
	          if(c == 27)
	          {
	              break;
	          }
                       
		  switch(c)
		  {
		        case KEY_RIGHT:
                             right_key();
			     break;

		        case KEY_LEFT:
                             left_key();
			     break;

		        case KEY_UP:
		             up_key();                       
			     break;
		        case KEY_DOWN:
                             down_key();
			     break;

		        case KEY_BACKSPACE:
			     backspace_key();
			     break;

			case 127:
			     backspace_key();
			     break;
   
		        case '\n':
			     newline();
			     break;

		        default:
			     other_char();
			     break;
                   }
                  
	           refresh();
                   clear();
                   refresh();
               }
                
	        write_file(name);
              	endwin();
	        return 0;
}
