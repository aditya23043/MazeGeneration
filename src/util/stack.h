#pragma once

#include <stdio.h>

#define MAX_SIZE 256

typedef struct {
	int arr[MAX_SIZE];
 	int head; // head index
} STACK;

void stack_init(STACK *stack);
/* return 1 for failure or 0 for success */
int stack_push(STACK *stack, int num);
void stack_print(STACK stack);
void stack_clear(STACK *stack);
/* return 1 for failure or 0 for success */
int stack_pop(STACK *stack);
int* stack_head(STACK* stack);
