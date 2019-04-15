//Joseph Harrison 2019
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LEFT '1'
#define RIGHT '0'

//definition of node
typedef struct Node
{
	char data;
	int freq;
	struct Node * left;
	struct Node * right;
} node_t;

//returns ptr to struct with null or zeroed members
node_t * null_node(void)
{
	node_t * nullnode = malloc(sizeof(node_t));
	nullnode -> data = '\0';
	nullnode -> freq = 0;
	nullnode -> left = NULL;
	nullnode -> right = NULL;
	return nullnode;
}

//decodes bitstrings
void decode_bitstr(node_t * root, char * bitptr, char * dataptr)
{
	//current position in datastring
	int i = 0;
	//current position in huffman code
	node_t * current = root;
	//read from bitstring
	for (int j = 0; *(bitptr + j) != '\0'; j++)
	{
		if (*(bitptr + j) == LEFT)
		{
			//go left
			current = current -> left;
		}
		else if (*(bitptr + j) == RIGHT)
		{
			//go right
			current = current -> right;
		}
		else
		{
			printf("bitstr error at %d\n", j);
		}
		//check if current is terminating
		//assume left and right will both have null ptrs	
		if (current -> left == NULL)
		{
			//write to datastring
			*(dataptr + i) = current -> data;
			//next position in datastring
			i++;
			//reset current ptr
			current = root;
		}
	}
}

//get node with a given freq
node_t * match_node_freq(node_t * node, int freq)
{
	//check if we have terminated
	if (node -> left == NULL)
	{
		//if we have found our node
		if (node -> freq == freq)
		{
			return node;
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		//explore left
		node_t * sol = match_node_freq(node -> left, freq);
		//if freq in left branch
		if (sol != NULL)
		{
			return sol;
		}
		else
		{
			//explore right
			sol = match_node_freq(node -> right, freq);
			//if freq in right branch
			if (sol != NULL)
			{
				return sol;
			}
			else
			{
				//freq is not in this tree
				return NULL;
			}
		}
	}
}

//create a huffman code
void make_code(node_t * root, int freqlist[], int length)
{
	//basis step
	if (length == 2)
	{
		printf("making basis tree\n");
		printf("frequencies:\nf1 = %d f2 = %d\n", freqlist[0], freqlist[1]);
		//left branch
		root -> left = null_node();
		root -> left -> freq = freqlist[0];
		//right branch
		root -> right = null_node();
		root -> right -> freq = freqlist[1];
	}
	else
	{
		//get the indices of two minimum freqs
		int i = 0;
		int j = 1;
		for (int k = 0; k < length; k++)
		{
			if (freqlist[k] < freqlist[i])
			{
				j = i;
				i = k;
			}
			else if (freqlist[k] < freqlist[j] && k != i)
			{
				j = k;
			}
		}
		printf("minimums:\nf1 = %d f2 = %d\n", freqlist[i], freqlist[j]);
		//new freqlist replaces freqs at i and j with their sum
		int newfreqlist[length - 1];
		int l = 0;
		for (int k = 0; k < length; k++)
		{
			if (k != i && k != j)
			{
				newfreqlist[l] = freqlist[k];
				l++;
			}
		}
		newfreqlist[l] = freqlist[i] + freqlist[j];
		printf("sum: %d\nsum: %d\n", freqlist[i] + freqlist[j], newfreqlist[l]);
		printf("new freqlist:\n");
		for (int k = 0; k < l + 1; k++)
		{
			printf("%d: %d\n", k, newfreqlist[k]);
		}
		//recursively generate tree
		make_code(root, newfreqlist, length - 1);
		//get node with freq sum
		node_t * subroot = match_node_freq(root, freqlist[i] + freqlist[j]);
		printf("replacing %d with %d and %d\n", subroot -> freq, freqlist[i], freqlist[j]);
		//create simple tree rooted on subroot
		//left branch
		subroot -> left = null_node();
		subroot -> left -> freq = freqlist[i];
		//right branch
		subroot -> right = null_node();
		subroot -> right -> freq = freqlist[j];
	}
}

//set a terminating node's data member to data argument
//if frequencies match
bool set_data(node_t * node, int freq, char data)
{
	//if the node is terminating
	if (node -> left == NULL)
	{
		//if we have matched the frequency and the data hasn't been set
		if (node -> freq == freq && node -> data == '\0')
		{
			node -> data = data;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		//explore left
		bool sol = set_data(node -> left, freq, data);
		//if we have set data
		if (sol == true)
		{
			return true;
		}
		else
		{
			//explore right
			sol = set_data(node -> right, freq, data);
			//if we have set data
			if (sol == true)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}

void print_tree(node_t * node, int depth)
{
	for (int i = 0; i < depth; i++)
	{
		printf("	");
	}
	printf("data: %c freq: %d\n", node -> data, node -> freq);
	//if not terminating
	if (node -> left != NULL)
	{
		print_tree(node -> left, depth + 1);
		print_tree(node -> right, depth + 1);
	}
}

int main()
{
	//create structs
	node_t * root = null_node();
	root -> left = null_node();
	root -> right = null_node();
	root -> left -> left = null_node();
	root -> left -> right = null_node();
	//setting data
	root -> right -> data = 'a';
	root -> right -> freq = 5;
	root -> left -> left -> data = 'b';
	root -> left -> left -> freq = 3;
	root -> left -> right -> data = 'c';
	root -> left -> right -> freq = 2;
	char bitstr[] = "1010110";
	char datastr[10];
	char * bitptr = bitstr;
	char * dataptr = datastr;
	decode_bitstr(root, bitptr, dataptr);
	printf("decoding bitstrings:\n");
	printf("bitstr: %s\n", bitstr);
	printf("datastr: %s\n", datastr);
	printf("node matching:\n");
	node_t * match = match_node_freq(root, 2);
	printf("ptr: %p data: %c freq: %d\n", match, match -> data, match -> freq);
	printf("creating huffman codes:\n");
	root = null_node();
	int freqlist[] = {2, 4, 5, 5, 7};
	make_code(root, freqlist, 5);
	printf("setting data:\n");
	char datalist[] = {'a', 'b', 'c', 'd', 'e'};
	for (int i = 0; i < 5; i++)
	{
		set_data(root, freqlist[i], datalist[i]);
	}	
	print_tree(root, 0);
	printf("decoding bitstrings with new huffman code:");
	char newbitstr[] = "001000111001";
	char newdatastr[10];
	char * newbitptr = newbitstr;
	char * newdataptr = newdatastr;
	decode_bitstr(root, newbitptr, newdataptr);
	printf("bitstr: %s\n", newbitstr);
	printf("datastr: %s\n", newdatastr);
	return 0;
}
