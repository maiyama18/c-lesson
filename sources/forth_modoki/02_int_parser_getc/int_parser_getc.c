#include "clesson.h"
#include <assert.h>
#include <ctype.h>

/*
cc cl_getc.c int_parser_getc.c
*/

typedef enum {
    NUMBER,
    SPACE,
} TokenType;

int parse_one(int current_ch, int* out_val, TokenType* out_type);

int main() {
    int answer1 = 0;
    int answer2 = 0;

    TokenType type1, type2, types;

    int current_ch = 0;
    current_ch = parse_one(current_ch, &answer1, &type1);
    current_ch = parse_one(current_ch, NULL, &types); // space
    parse_one(current_ch, &answer2, &type2);

    // verity result.
    assert(answer1 == 123);
    assert(answer2 == 456);

    assert(type1 == NUMBER);
    assert(type2 == NUMBER);
    assert(types == SPACE);

    return 0;


}

int parse_one(int current_ch, int* out_val, TokenType* out_type) {
    if (!current_ch) current_ch = cl_getc();

    if (isdigit(current_ch)) {
        int val = current_ch - '0';

        int c;
        while ((c = cl_getc()) != EOF && isdigit(c)) {
            val *= 10;
            val += c - '0';
        }

        *out_type = NUMBER;
        *out_val = val;
        return c;
    }
    else if (isspace(current_ch)) {
        int c;
        while ((c = cl_getc()) != EOF && isspace(c));

        *out_type = SPACE;
        return c;
    }
    else {
        return 0;
    }
}
