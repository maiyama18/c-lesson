#include <stdlib.h>

typedef enum {
    NUMBER,
    NAME,
} LiteralType;

typedef struct {
    LiteralType type;
    union {
        int number;
        char* name;
    } u;
} Literal;

void stack_push(Literal);
Literal* stack_pop();