#include "stack.h"

void stack_init(STACK *stack)
{
	stack->head = -1;
}

int stack_push(STACK *stack, int num)
{
	if(stack->head >= MAX_SIZE-1)
	{
		return 1;
	}

	stack->head++;
	stack->arr[stack->head] = num;

	return 0;
}

void stack_print(STACK stack)
{
	printf("[ ");
	for( int i = 0; i <= stack.head; i++ )
	{
		printf("%d ", stack.arr[i]);
	}
	printf("]\n");
}

void stack_clear(STACK *stack)
{
	for( int i = 0; i < MAX_SIZE; i++ )
	{
		stack->arr[i] = 0;
	}
	stack->head = -1;
}

int stack_pop(STACK *stack)
{
	if(stack->head < 0)
	{
		return 1;
	}
	stack->head--;

	return 0;
}

int* stack_head(STACK* stack)
{
	if(stack->head == -1)
	{
		return NULL;
	}

	return &stack->arr[stack->head];
}
