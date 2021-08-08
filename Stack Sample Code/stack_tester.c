#include <stdio.h>
#include "stack.h"

// the following function is used to report the success of an operation carried out during testing
// Parameters:
// rVal - the return value returned as a result of calling one of the stack functions.
// funcName - a String containing the name of a stack function that has been called
// optVal - an optional value, doesn't apply to all test cases 
void report(int rVal, char* funcName, int optVal) 
{
	if (rVal == SUCCESS) 
	{ 
		printf("%s successful: %d\n", funcName, optVal); 
	}
	else if (rVal == INVALID_INPUT_PARAMETER) 
	{ 
		printf("%s invalid or NULL input parameter: %d\n", funcName, optVal); 
	}
	else if (rVal == MEMORY_ALLOCATION_ERROR) 
	{ 
		printf("%s out of memory - malloc failed: %d\n", funcName, optVal); 
	}
	else if (rVal == INVALID_STACK_OPERATION) 
	{ 
		printf("%s invalid stack operation, e.g. attempting pop or peek from an empty stack: %d\n", funcName, optVal); 
	}
	else if (rVal == NOT_IMPLEMENTED) 
	{ 
		printf("%s function not implemented yet: %d\n", funcName, optVal); 
	}
}

// main function
int main() {
	double value = 0;
	int rVal = 0;

	// initialize a stack
	Stack *pStack = NULL;
	rVal = stackInit(&pStack);
	report(rVal, "Stack Init", 0);

	// attempt to pop from an empty stack - should report error
	value = 0;
	rVal = pop(pStack, &value);
	report(rVal, "Stack Pop", value);

	// attempt to peek at an empty stack - should report error
	value = 0;
	rVal = peek(pStack, &value);
	report(rVal, "Stack Peek", value);

	// push 71 & report
	value = 71;
	rVal = push(pStack, value);
	report(rVal, "Stack Push", value);

	// push 99
	value = 99;
	rVal = push(pStack, value);
	report(rVal, "Stack Push", value);

	// peek - should get value of '99'
	value = 0;
	rVal = peek(pStack, &value);
	report(rVal, "Stack Peek", value);

	// pop
	value = 0;
	rVal = pop(pStack, &value);
	report(rVal, "Stack Pop", value);

	// pop
	value = 0;
	rVal = pop(pStack, &value);
	report(rVal, "Stack Pop", value);

	// pop (shouldn't do anything) as stack is empty
	value = 0;
	rVal = pop(pStack, &value);
	report(rVal, "Stack Pop", value);

	// release memory
	rVal = freeStack(pStack);
	report(rVal, "Stack Free", 0);

	// other tests
	// attempt to free a 'NULL' stack
	rVal = freeStack(NULL);
	report(rVal, "Stack Free", 0);

	// attempt to initialise an invalid / null pointer to a stack	
	rVal = stackInit(NULL);
	report(rVal, "Stack Init", 0);

	// attempt to push to an invalid / NULL stack
	value = 34;	
	rVal = push(NULL, value);
	report(rVal, "Stack Push", 0);

	// attempt to pop from an invalid / NULL stack	
	rVal = pop(NULL, &value);
	report(rVal, "Stack Pop", 0);

	return 0;
}
