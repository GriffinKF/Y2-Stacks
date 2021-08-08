
/* error codes / success codes */
#define SUCCESS                  100   // Value to be returned if a function is completed successfully
#define INVALID_INPUT_PARAMETER  101   // Value to be returned if you detect that one of the input parameters 
                                       // into your function is invalid, e.g. it is NULL or an unexpected value
#define MEMORY_ALLOCATION_ERROR  102   // Value to be returned if a memory allocation error occurs during your function
#define INVALID_STACK_OPERATION  103   // Value to be returned if your function detects an operation that is being
                                       // attempted on your stack data structure that isn't valid or your stack
                                       // isn't in a ready state to receive. For example, an attempt is made to remove
                                       // an item from an empty stack or to peek at an item on an empty stack
#define NOT_IMPLEMENTED          104   // Value to be returned if you haven't implemented this function yet

/* data structures */

// struct for a Node in the Stack
typedef struct node {
	double score;
	struct node *next;
} Node;

// struct for the Stack
typedef struct stack {
	Node *top;
} Stack;

/* prototypes / declarations of Stack functions */

// initialise a new Stack
// Parameters:
// pStack - will receive a pointer to the newly allocated stack
int stackInit(Stack **pStack);

// push a value onto the top of the stack
// Parameters:
// pStack - a pointer to the Stack
// value - the value to be pushed
int push(Stack *pStack, double value);

// pop a value off of the top of the stack
// Parameters:
// pStack - a pointer to the Stack
// value - will receive the value popped
int pop(Stack *pStack, double *value);

// get the value at the top of the stack
// without removing / popping it
// Parameters:
// pStack - a pointer to the Stack
// value - will receive the peeked value
int peek(Stack *pStack, double *value);

// free all memory used in the stack
// Parameters:
// pStack - a pointer to the stack to free
int freeStack(Stack *pStack);
