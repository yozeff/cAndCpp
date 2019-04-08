//
//  brainfuck.c
//  
//
//  Created by Joseph Harrison on 08/04/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int CELLS = 8;
const int MAXLINESIZE = 15;

typedef struct Cell
{
    int data;
    struct Cell * nextptr;
    struct Cell * lastptr;
} cell_t;

//get the next pairing bracket in the line
char * next_bracket(char * insptr)
{
    int j = 0;
    while (*insptr != '\0')
    {
        if (*insptr == ']')
        {
            j--;
            if (j == 0)
            {
                return insptr;
            }
        }
        else if (*insptr == '[')
        {
            j++;
        }
        insptr++;
    }
    printf("no closing bracket\n");
    return insptr;
}

//get the last pairing bracket in line
char * last_bracket(char * insptr, char line[MAXLINESIZE])
{
    int j = 0;
    char * head = line;
    while (insptr >= head)
    {
        if (*insptr == '[')
        {
            j--;
            if (j == 0)
            {
                return insptr;
            }
        }
        else if (*insptr == ']')
        {
            j++;
        }
        insptr--;
    }
    printf("no starting bracket\n");
    return insptr;
}

int main(void)
{
    //allocate our first cell
    cell_t * first = malloc(sizeof(cell_t));
    first -> data = 0;
    cell_t * last = first;
    //allocate next cells
    for (int i = 0; i < CELLS; i++)
    {
        cell_t * cell = malloc(sizeof(cell_t));
        cell -> data = 0;
        //link cell to last cell
        cell -> lastptr = last;
        //link last cell to cell
        last -> nextptr = cell;
        last = cell;
    }
    //link the last cell back to the first
    last -> nextptr = first;
    first -> lastptr = last;
    
    //data pointer starts pointing to the first cell
    cell_t * dataptr = first;
    
    //stores the line that the user has entered
    char line[MAXLINESIZE];
    
    while (strcmp(line, "quit") != 0)
    {
        
        //user prompt
        printf("$ ");
        scanf("%s", line);
        
        //instruction pointer
        char * insptr = line;
        
        //evaluate the line
        while (*insptr != '\0')
        {
            switch (*insptr)
            {
                //changing the data pointer
                case '>': dataptr = dataptr -> nextptr;
                          break;
                case '<': dataptr = dataptr -> lastptr;
                          break;
                //changing the value in the current cell
                case '+': dataptr -> data = (dataptr -> data + 1) % 127;
                          break;
                case '-': dataptr -> data = (dataptr -> data - 1) % 127;
                          break;
                //user io
                case '.': printf("%c\n", dataptr -> data);
                          break;
                case ',': printf("$$ ");
                          char userin[1];
                          scanf("%s", userin);
                          dataptr -> data = (int)userin[0];
                          break;
                //bracket routines
                case '[': if (dataptr -> data == 0)
                          {
                              insptr = next_bracket(insptr);
                          }
                          break;
                case ']': if (dataptr -> data != 0)
                          {
                              insptr = last_bracket(insptr, line);
                          }
                          break;
            }
            insptr++;
        }
    }
}
