#include "stack.h"

#define STACK_SIZE 1024

static Literal stack[STACK_SIZE];
static int top = -1;

static int is_stack_empty() {
    return top < 0;
}

void stack_push(Literal literal) {
    stack[++top] = literal;
}

Literal* stack_pop() {
    if (is_stack_empty()) return NULL;
    return &stack[top--];
}

