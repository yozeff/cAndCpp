//
//  brainfuck.cpp
//  
//
//  Created by Joseph Harrison on 06/04/2019.
//

#include <iostream>
#include <string>

using namespace std;

//number of memory cells
int CELLS = 8;

//get the position of the next, pairing ']'
int next_closing(int insptr, string line)
{
    //counts the number of '[' we have found
    //these instances must be resolved by
    //decreasing j
    int j = 0;
    while (insptr < line.size())
    {
        if (line[insptr] == ']')
        {
            j--;
            //if we have closed all other pairs
            if (j == 0)
            {
                return insptr;
            }
        }
        //a new instance has been found
        else if (line[insptr] == '[')
        {
            j++;
        }
        insptr++;
    }
    //if a pairing ']' is not found
    cout << "no succeeding ']'\n";
    return insptr;
}

//get the position of the last, pairing '['
int last_starting(int insptr, string line)
{
    int j = 0;
    while (insptr > -1)
    {
        if (line[insptr] == '[')
        {
            j--;
            if (j == 0)
            {
                return insptr;
            }
        }
        else if (line[insptr] == ']')
        {
            j++;
        }
        insptr--;
    }
    cout << "no preceeding '['\n";
    return insptr;
}

int main(void)
{
    //line of commands that are being executed
    string line;
    //data pointer points to a cell
    int dataptr = 0;
    //init and fill memory cells array
    int cells[CELLS];
    for (int i = 0; i < CELLS; i++)
    {
        cells[i] = 0;
    }
    
    //interpreter runtime
    while (line.compare("quit") != 0)
    {
        
        //user prompt
        cout << "$ ";
        cin >> line;
        
        //instruction pointer points to current instruction
        int insptr = 0;
        
        //go through each command in the line
        while (insptr < line.size())
        {
            
            switch (line[insptr])
            {
                //increment data pointer
                case '>': dataptr = (dataptr - 1) % CELLS;
                          break;
                //decrement data pointer
                case '<': dataptr = (dataptr - 1) % CELLS;
                          break;
                //increment value in cell pointed to by data pointer
                case '+': cells[dataptr] = (cells[dataptr] + 1) % 127;
                          break;
                //decrement value in cell pointed to by data pointer
                case '-': cells[dataptr] = (cells[dataptr] - 1) % 127;
                          break;
                //output value in cell pointed to by data pointer as char
                case '.': cout << char(cells[dataptr]) << "\n";
                          break;
                //recieve char input and store ascii value in cell
                case ',': char userin;
                          cout << "$$ ";
                          cin >> userin;
                          cells[dataptr] = int(userin);
                          break;
                //if value in cell pointed to by data pointer is 0 skip to next ]
                case '[': if (cells[dataptr] == 0)
                          {
                              insptr = next_closing(insptr, line);
                          }
                          break;
                //if value pointed to by data pointer is not 0 skip to last [
                case ']': if (cells[dataptr] != 0)
                          {
                              insptr = last_starting(insptr, line);
                          }
                          break;
            }
            //continue to next instruction
            insptr++;
        }
    }
}
