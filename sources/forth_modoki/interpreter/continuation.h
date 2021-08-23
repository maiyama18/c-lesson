#include "stack.h"

typedef struct {
    StackElementArray* exec_array;
    int pc;
} Continuation;

void co_stack_push(Continuation* continuation);

// return 1 if continuation found, otherwise return 0
int co_stack_pop(Continuation* out_continuation);