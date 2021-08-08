#include "stack.h"
#include <stdlib.h>

// initialise a new Stack
// Parameters:
// pStack - will receive a pointer to the newly allocated stack
int stackInit(Stack **pStack)
{
	// we expect to be provided with the memory address
	// of a Stack pointer variable. Make sure this memory 
	// address is valid, e.g. isn't NULL
	if (pStack == NULL)
		return  INVALID_INPUT_PARAMETER;

	// make sure that a Stack hasn't been initialised already, 
	// e.g. is there already something (non-NULL) present at
	// the memory address we will be writing to?
	if (*pStack != NULL)
		return INVALID_INPUT_PARAMETER;

	// allocate memory for a new Stack and store in the pointer provided
	(*pStack) = (Stack*)malloc(sizeof(Stack));

	// check for memory failure
	if ((*pStack) == NULL)
	{
			return MEMORY_ALLOCATION_ERROR;
	}

	// initialise fields in the Stack
	(*pStack)->top = NULL;

	return SUCCESS;
}

// push a value onto the top of the stack
// Parameters:
// pStack - a pointer to the Stack
// value - the value to be pushed
int push(Stack *pStack, double value)
{
	// check that we have a pointer to a valid Stack
	if (pStack == NULL)
		return INVALID_INPUT_PARAMETER;

	// create a new node to go onto the stack
	Node *newNode = (Node*)malloc(sizeof(Node));

	// if failed to allocate memory for new node
	if (newNode == NULL)
		return MEMORY_ALLOCATION_ERROR;

	// initialise fields in new node
	newNode->score = value;

	// set the new node's 'next' pointer to point to
	// whatever is currently at the top of the stack
	// (because the new node will become the new top
	// of the stack and the existing top will shift
	// down below it)
	newNode->next = pStack->top;

	// make the new node the new top of the stack
	pStack->top = newNode;

	return SUCCESS;
}

// pop a value off of the top of the stack
// Parameters:
// pStack - a pointer to the Stack
// value - will receive the value popped
int pop(Stack *pStack, double *value)
{
	// check that we have a pointer to a valid Stack
	if (pStack == NULL)
		return INVALID_INPUT_PARAMETER;

	// check that the pointer we have received
	// to store the popped value into isn't null
	// (it should be pointing to a valid memory address)
	if (value == NULL)
		return INVALID_INPUT_PARAMETER;

	// proceed with popping a node from the top of the stack

	// first, check: is the stack currently empty?
	// Are we attempting to pop an item from an empty stack?
	if (pStack->top == NULL)
		return INVALID_STACK_OPERATION;

	// otherwise, store the value that's in the node 
	// at the top of the stack
	*value = pStack->top->score;

	// create a temporary pointer to the node currently
	// at the top of the stack (we are going to remove it)
	Node *nodeToRemove = pStack->top;

	// change the top of the stack to now be the
	// next node down
	pStack->top = pStack->top->next;

	// remove / free the existing top (which has now been popped)
	nodeToRemove->next = NULL;
	nodeToRemove->score = 0;
	free(nodeToRemove);

	return SUCCESS;

}

// get the value at the top of the stack
// without removing / popping it
// Parameters:
// pStack - a pointer to the Stack
// value - will receive the peeked value
int peek(Stack *pStack, double *value)
{
	// check that we have a pointer to a valid Stack
	if (pStack == NULL)
		return INVALID_INPUT_PARAMETER;

	// check that the pointer we have received
	// to store the peeked-at value into isn't null
	// (it should be pointing to a valid memory address)
	if (value == NULL)
		return INVALID_INPUT_PARAMETER;

	// proceed with peeking at the node on the top of the stack

	// first, check: is the stack currently empty?
	// Are we attempting to peek at an empty stack?
	if (pStack->top == NULL)
		return INVALID_STACK_OPERATION;

	// otherwise, store the value that's in the node 
	// at the top of the stack
	*value = pStack->top->score;

	return SUCCESS;

}

// free all memory used in the stack
// Parameters:
// pStack - a pointer to the stack to free
int freeStack(Stack *pStack)
{	
	// check that we have a pointer to a valid Stack
	if (pStack == NULL)
		return INVALID_INPUT_PARAMETER;

	// while there is still an item at the top of 
	// the stack to free
	while (pStack->top != NULL)
	{
		// get pointer to current top of the stack
		Node *currentTop = pStack->top;

		// shift top to the next node down
		pStack->top = pStack->top->next;

		// free the current top
		free(currentTop);
	}

	// all nodes in the stack have been freed.
	// now free the stack itself
	free(pStack);

	return SUCCESS;
}
