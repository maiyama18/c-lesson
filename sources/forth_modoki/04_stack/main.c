#include "stack.h"
#include <assert.h>

void assert_popped_literals_eq(Literal* expects[], int nexpects) {
    for (int i = 0; i < nexpects; i++) {
        Literal* expect = expects[i];
        Literal* actual = stack_pop();

        if (expect == NULL) {
            assert(actual == NULL);
        }
        else {
            assert(expect->type == actual->type);

            switch (expect->type) {
            case NUMBER:
                assert(expect->u.number == actual->u.number);
                break;
            case NAME:
                assert(strcmp(expect->u.name, actual->u.name) == 0);
                break;
            }
        }
    }
}

void verify_stack_pop(Literal inputs[], int ninputs, Literal* expects[], int nexpects) {
    for (int i = 0; i < ninputs; i++) stack_push(inputs[i]);
    assert_popped_literals_eq(expects, nexpects);
}

void test_stack_pop_empty() {
    Literal inputs[] = {};
    Literal* expects[] = { NULL };

    verify_stack_pop(inputs, 0, expects, 1);
}

void test_stack_pop_one_literal_number() {
    Literal inputs[] = { { NUMBER, {.number = 42} } };
    Literal* expects[] = { &inputs[0], NULL };

    verify_stack_pop(inputs, 1, expects, 2);
}

void test_stack_pop_one_literal_name() {
    Literal inputs[] = { { NAME, {.name = "foo"} } };
    Literal* expects[] = { &inputs[0], NULL };

    verify_stack_pop(inputs, 1, expects, 2);
}

int main() {
    test_stack_pop_empty();
    test_stack_pop_one_literal_number();
    test_stack_pop_one_literal_name();

    return 0;
}

