#include "stack.h"
#include <assert.h>

void test_stack_pop_empty() {
    assert(stack_pop() == NULL);
}

int main() {
    test_stack_pop_empty();

    return 0;
}

