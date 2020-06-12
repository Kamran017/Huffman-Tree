/*
	KAMRAN BALAYEV 17011904

	SOURCES:
		https://www.geeksforgeeks.org/
		https://www.programiz.com/
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COUNT 10 //variable for printing huffman tree
typedef struct Node {
	int data;//frequency of character
	char ch;//character
	struct Node *left, *right, *next;//left, right and next element of list
}node;

void printList(node *node);
void findFrequency(node *, char *, int);
void sortedInsert(node **, node*);
void insertionSort(node **);
void hufman(node *freq);
void insert(node *, node*);
node * createNode(node*, node*, int);
void printHufman(node *, int);


int main()
{

	char textArr[1000];//store the string value
	int inputLength, a = 0;
	node *freq = (node*)malloc(sizeof(node));//allocate node
	
	freq->right = NULL;
	freq->left = NULL;


	printf("Please enter the text: ");
	gets(&textArr);//scan the string from user
	//assign the length of string to the proper variable
	inputLength = strlen(textArr);
	//call the function for calculating frequency
	findFrequency(freq, textArr, inputLength);
	//insert the frequencies
	insertionSort(&freq);
	freq = freq->next;//point to the right location
	//print the listed frequencies
	printList(freq);
	//call the huffman function in order to create the tree
	hufman(freq);	
	return 0;
}
/*
	Purpose of this function is listing the frequencies.	
	It has one parameter called node which will be used 
	as	reference to the head of linked list.
*/
void printList(node *node)
{
	while (node != NULL)
	{
		printf("%d ", node->data);
		node = node->next;
	}
}

/*
	This function is finding the frequencies of characters in linked list.
	It has 3 parameters one of them is freq which is referance to the head 
	of linked list, second one is input string and the last one is the length
	of this string.
*/
void findFrequency(node *freq, char *textArr, int inputLength) {
	int i = 0, j, count;
	node * head = freq;//this variable will be used for setting head of list operation.
	//find the frequency of character
	for (i = 0; i < inputLength; i++) {
		count = 1;//reset count
		if (textArr[i]) {
			for (j = i + 1; j < inputLength; j++) {
				//if the character matches with another
				if (textArr[i] == textArr[j])
				{
					count++;//increment of the frequency of proper character
					textArr[j] = '\0';//purpose of this operation is not repeating frequency during calculation
				};
			}
			freq->ch = textArr[i];//add the character to the list
			freq->data = count;//add the counter of character to the list
			freq->next = (node*)malloc(sizeof(node));//allocate node
			freq = freq->next;//freq will show the next node of list
			freq->left = NULL;
			freq->right= NULL;
		}
	}
	freq->next = NULL;//make the end of linked list equal to the NULL
	freq = head;//assign the header of linked list
}

// function to sort a linked list using insertion sort
void insertionSort(node **head)
{
	// Initialize sorted linked list
	node *sorted = NULL;

	// Traverse the given linked list and insert every
	// node to sorted
	node *current = *head;
	while (current != NULL)
	{
		// Store next for next iteration
		node  *next = current->next;

		// insert current in sorted linked list
		sortedInsert(&sorted, current);

		// Update current
		current = next;
	}

	// Update head_ref to point to sorted linked list
	*head = sorted;
}

//function to insert a new node in a list
void sortedInsert(node ** head, node* newNode)
{
	node* current;
	/* Special case for the head end */
	if (*head == NULL || (*head)->data >= newNode->data)
	{
		newNode->next = *head;
		*head = newNode;
	}
	else
	{
		/* Locate the node before the point of insertion */
		current = *head;
		while (current->next != NULL && current->next->data < newNode->data)
		{
			current = current->next;
		}
		newNode->next = current->next;
		current->next = newNode;
	}
}

/*
	This function will be used to insert new node to the sorted list.
	First parameter is the head of list and the second parameter is 
	new node. 
*/
void insert(node *freq, node * newNode) {

	while (newNode->data > freq->data  && freq->next != NULL)
	{
		freq = freq->next;
	}

	newNode->next = freq->next;
	freq->next = newNode;
}
/*
	This function will be used for creating huffman tree nodes.
	Function has 3 parametres one of them is the left part of tree, another one is right 
	part of tree and the final parameter is value of root which is the sum of left and right
*/
node *createNode(node* left, node*right, int sum) {
	node * newNode = (node*)malloc(sizeof(node));//allocate node
	newNode->right = (node*)malloc(sizeof(node));//allocate node
	newNode->left = (node*)malloc(sizeof(node));//allocate node

	newNode->left = left;//assign left value of tree
	newNode->right = right;//assign right value of tree
		
	newNode->data = sum;//assign the value of root which is sum of left and right
	newNode->ch = NULL;//root value has no character

	return newNode;//return the node
}


/*
	This function will print the huffman tree.
*/
void printHufman(node *freq, int space)
{
	// Base case 
	if (freq == NULL)
		return;

	// Increase distance between levels 
	space += COUNT;

	// Process right child first 
	printHufman(freq->right, space);

	// Print current node after space 
	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	if (freq->ch == '\0')
		printf("%d\n", freq->data);
	else
		printf("%d %c\n", freq->data, freq->ch);

	// Process left child 
	printHufman(freq->left, space);
}

/*
	This function is creating the huffman tree.
	It has one parameter which is the head of 
	linked list

*/
void hufman(node *freq) {
	node * newNode;//this variable will used when we call the createNode function
	int sum = 0;//this variable will store the sum of left and right child in tree
	while (freq->next != NULL) {
		sum = freq->data + freq->next->data;//add left and right child of tree
		newNode = createNode(freq,freq->next,sum);//create new node and assign it to the proper variable
		insert(freq, newNode);//insert node to the linked list 
		freq = freq->next->next;//show the proper value in linked list for next operations
	}
	printf("\n");
	printf("\n");
	printHufman(freq, 0);//print the huffman tree
}


