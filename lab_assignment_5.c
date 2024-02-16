#include <stdio.h>
#include <stdlib.h>
typedef struct node {
	char letter;
	struct node* next;
} node;
// Returns number of nodes in the linkedList.
int length(node* head)
{
	if (head == NULL) return 0;
	struct node* temp = head;
	int n = 1;

	while (temp->next != NULL) {
		n++;
		temp = temp->next;
	}
	return n;
}
// parses the string in the linkedList
// if the linked list is head -> |a|->|b|->|c|
// then toCString function wil return "abc"
char* toCString(node* head)
{
	if (head == NULL) return NULL;

	int linkSize = length(head); // keep track of the size of the string
	struct node* temp = head;    // traversal pointer

	char* cstring = (char*)malloc(linkSize * sizeof(char) + sizeof(char)); // array to be returned at the end
	if (cstring == NULL) return NULL;

	for (int i = 0; i < linkSize; i++) {
		cstring[i] = temp->letter;
		temp = temp->next;
	}
	cstring[linkSize] = '\0';
	return cstring;
}
// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	if (newNode == NULL) return;
	newNode->next = NULL;
	newNode->letter = c;
	// ^ creation of new node with parameters

	struct node* temp = *pHead;
	if (temp == NULL) {
		*pHead = newNode;
		return; // special case when head points to NULL, create new node there.
	}
	while (temp->next != NULL) { // otherwise, traverse to end of linked list,
		temp = temp->next;
	}

	// then insert the node
	temp->next = newNode;
}
// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
	struct node* temp = *pHead;
	while (temp != NULL) {
		*pHead = temp->next;
		free(temp);
		temp = *pHead;
	}
	*pHead = NULL;
}
int main(void)
{
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt", "r");
	fscanf(inFile, " %d\n", &numInputs);
	while (numInputs-- > 0)
	{	
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile, " %c", &c);
			insertChar(&head, c);
		}
		str = toCString(head);
		printf("String is : %s\n", str);
		free(str);
		deleteList(&head);
		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}
	fclose(inFile);
}