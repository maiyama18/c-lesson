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

void test_parse_one_123();
void test_parse_one_123_456();

int main() {
    int answer1 = 0;
    int answer2 = 0;

    test_parse_one_123();
    test_parse_one_123_456();

    cl_getc_set_src("123 456");

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

void test_parse_one_123() {
    cl_getc_set_src("123");
    int val;
    TokenType token_type;

    int current_ch = 0;
    current_ch = parse_one(current_ch, &val, &token_type);

    assert(token_type == NUMBER);
    assert(val == 123);

    assert(current_ch == EOF);
}

void test_parse_one_123_456() {
    cl_getc_set_src("123 456");
    int val1, val2, val3;
    TokenType type1, type2, type3;

    int current_ch = 0;
    current_ch = parse_one(current_ch, &val1, &type1);
    current_ch = parse_one(current_ch, &val2, &type2);
    current_ch = parse_one(current_ch, &val3, &type3);

    assert(type1 == NUMBER);
    assert(val1 == 123);

    assert(type2 == SPACE);
    assert(val2 == 0);

    assert(type3 == NUMBER);
    assert(val3 == 456);

    assert(current_ch == EOF);
}