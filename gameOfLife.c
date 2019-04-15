#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//print an array
void print_array(int *arr, int sizex, int sizey)
{
	for (int i = 0; i < sizey; i++)
	{
		for (int j = 0; j < sizex; j++)
		{
			printf("%d ", *((arr + i * sizex) + j));
		}
		printf("\n");
	}
	//print a partition
	for (int i = 0; i < sizex; i++)
	{
		printf("--");
	}
	printf("\n");
}

//check if an array is empty
bool is_empty(int *arr, int sizex, int sizey)
{
	for (int i = 0; i < sizey; i++)
	{
		for (int j = 0; j < sizex; j++)
		{
			if (*((arr + i * sizex) + j) == 1)
			{
				return false;
			}
		}
	}
	return true;
}

//initialise an array with 0s
void init_array(int *arr, int sizex, int sizey)
{
	for (int i = 0; i < sizey; i++)
	{
		for (int j = 0; j < sizex; j++)
		{
			*((arr + i * sizex) + j) = 0;
		}
	}
}

//populate an array with 1s based on probability, prob
void populate(int *arr, int sizex, int sizey, int prob)
{
	int rnum;
	for (int i = 0; i < sizey; i++)
	{
		for (int j = 0; j < sizex; j++)
		{
			rnum = rand() % 99;
			if (rnum <= prob)
			{
				*((arr + i * sizex) + j) = 1;
			}
		}
	}
}

//apply rules to array copying to next array
void apply_rules(int *arr, int *nextarr, int sizex, int sizey)
{
	for (int i = 0; i < sizey; i++)
	{
		for (int j = 0; j < sizex; j++)
		{
			//get number of live neighbours
			int alive = 0;
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					if (*((arr + (i + k) * sizex) + (j + l)) == 1 && k != 0 && l != 0)
					{
						alive++;
					}
				}
			}
			
			//if alive
			if (*((arr + i * sizex) + j) == 1)
			{
				//apply rules
				if (alive < 2)
				{
					//the cell is dead from isolation
					*((nextarr + i * sizex) + j) = 0;
				}
				else if (alive > 3)
				{
					//the cell is dead from overpopulation
					*((nextarr + i * sizex) + j) = 0;
				}
				else
				{
					//the cell survives
					*((nextarr + i * sizex) + j) = 1;
				}
			}
			//if dead
			else
			{
				if (alive == 3)
				{
					//the cell comes to life
					*((nextarr + i * sizex) + j) = 1;
				}
			}
		}
	}
}

//copy one array's contents into another array
void copy_array(int *arr, int *nextarr, int sizex, int sizey)
{
	for (int i = 0; i < sizey; i++)
	{
		for (int j = 0; j < sizex; j++)
		{
			//copy elements
			*((arr + i * sizex) + j) = *((nextarr + i * sizex) + j);
		}
	}
}

int main(int argc, char ** argv)
{
	//size for game array
	int sizex = atoi(argv[1]);
	int sizey = atoi(argv[2]);
	//probability for a cell to be made alive
	//0 to 100
	int prob = atoi(argv[3]);
	
	//create our array
	int arr[sizey][sizex];
	init_array((int *)arr, sizex, sizey);
	
	//randomly populate
	populate((int *)arr, sizex, sizey, prob);

	//while there are still alive cells
	int nextarr[sizey][sizex];
	char userin;
	while (is_empty((int *)arr, sizex, sizey) == false && userin != 'q')
	{
		//clear screen
		system("clear");
		
		//initialise array for next state
		init_array((int *)nextarr, sizex, sizey);

		//apply rules to array copying results to next array
		apply_rules((int *)arr, (int *)nextarr, sizex, sizey);

		//print array
		print_array((int *)arr, sizex, sizey);

		//copy next array into array
		copy_array((int *)arr, (int *)nextarr, sizex, sizey);
		
		printf("'q' to quit: ");
		scanf("%c", &userin);
	}
}
