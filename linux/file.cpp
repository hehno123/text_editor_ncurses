#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "variable.h"

void open_file(std::string& file_name, std::vector<std::string>& text, int& yMax, int& last_line_print, int& cursor_position_y, int& cursor_position_x, int& first_line_print)
{   	
        std::fstream MyFile;
	std::string line2;
	MyFile.open(file_name);
        
	text.clear();
	text.resize(1);

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
         cursor_position_x = 0;
	 first_line_print = 0;

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
	                 MyFile << text[j];
		         MyFile << '\n';
	       } 
 
               MyFile.close();
}
