#include "clesson.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

enum LexicalType {
    NUMBER,
    SPACE,
    EXECUTABLE_NAME,
    LITERAL_NAME,
    OPEN_CURLY,
    CLOSE_CURLY,
    END_OF_FILE,
    UNKNOWN
};



struct Token {
    enum LexicalType ltype;
    union {
        int number;
        char onechar;
        char* name;
    } u;
};

#define NAME_SIZE 256

int isdigit(int c) {
    return '0' <= c && c <= '9';
}

int parse_one(int prev_ch, struct Token* out_token) {
    if (prev_ch == EOF) prev_ch = cl_getc();

    if (isdigit(prev_ch)) {
        int val = prev_ch - '0';

        int c;
        while ((c = cl_getc()) != EOF && isdigit(c)) {
            val *= 10;
            val += c - '0';
        }

        out_token->ltype = NUMBER;
        out_token->u.number = val;

        return c;
    }
    else if (prev_ch == ' ') {
        int c;
        while ((c = cl_getc()) != EOF && c == ' ');

        out_token->ltype = SPACE;
        return c;
    }
    else if ('A' <= prev_ch && prev_ch <= 'z') {
        char* name = malloc(NAME_SIZE * sizeof(char));
        name[0] = prev_ch;

        int c, i = 1;
        while ((c = cl_getc()) != EOF && c != ' ') {
            name[i++] = c;
        }
        name[i] = '\0';

        out_token->ltype = EXECUTABLE_NAME;
        out_token->u.name = name;
        return c;
    }
    else if (prev_ch == '/') {
        char* name = malloc(NAME_SIZE * sizeof(char));

        int c, i = 0;
        while ((c = cl_getc()) != EOF && c != ' ') {
            name[i++] = c;
        }
        name[i] = '\0';

        out_token->ltype = LITERAL_NAME;
        out_token->u.name = name;
        return c;
    }
    else if (prev_ch == '{') {
        out_token->ltype = OPEN_CURLY;
        out_token->u.onechar = '{';
        return cl_getc();
    }
    else if (prev_ch == '}') {
        out_token->ltype = CLOSE_CURLY;
        out_token->u.onechar = '}';
        return cl_getc();
    }
    else if (prev_ch == EOF) {
        out_token->ltype = END_OF_FILE;
        return EOF;
    }
    else {
        out_token->ltype = UNKNOWN;
        return EOF;
    }
}


void parser_print_all() {
    int ch = EOF;
    struct Token token = {
        UNKNOWN,
        {0}
    };

    do {
        ch = parse_one(ch, &token);
        if (token.ltype != UNKNOWN) {
            switch (token.ltype) {
            case NUMBER:
                printf("num: %d\n", token.u.number);
                break;
            case SPACE:
                printf("space!\n");
                break;
            case OPEN_CURLY:
                printf("Open curly brace '%c'\n", token.u.onechar);
                break;
            case CLOSE_CURLY:
                printf("Close curly brace '%c'\n", token.u.onechar);
                break;
            case EXECUTABLE_NAME:
                printf("EXECUTABLE_NAME: %s\n", token.u.name);
                break;
            case LITERAL_NAME:
                printf("LITERAL_NAME: %s\n", token.u.name);
                break;
            default:
                printf("Unknown type %d\n", token.ltype);
                break;
            }
        }
    } while (ch != EOF);
}





static void test_parse_one_number() {
    char* input = "123";
    int expect = 123;

    struct Token token = { UNKNOWN, {0} };
    int ch;

    cl_getc_set_src(input);

    ch = parse_one(EOF, &token);

    assert(ch == EOF);
    assert(token.ltype == NUMBER);
    assert(expect == token.u.number);
}

static void test_parse_one_empty_should_return_END_OF_FILE() {
    char* input = "";
    int expect = END_OF_FILE;

    struct Token token = { UNKNOWN, {0} };
    int ch;

    cl_getc_set_src(input);
    ch = parse_one(EOF, &token);

    assert(ch == EOF);
    assert(token.ltype == expect);
}

static void test_parse_one_executable_name() {
    char* input = "add";
    char* expect_name = "add";
    int expect_type = EXECUTABLE_NAME;

    struct Token token = { UNKNOWN, {0} };
    int ch;

    cl_getc_set_src(input);
    ch = parse_one(EOF, &token);

    assert(ch == EOF);
    assert(token.ltype == expect_type);
    assert(strcmp(token.u.name, expect_name) == 0);
}

static void test_parse_one_literal_name() {
    char* input = "/add";
    char* expect_name = "add";
    int expect_type = LITERAL_NAME;

    struct Token token = { UNKNOWN, {0} };
    int ch;

    cl_getc_set_src(input);
    ch = parse_one(EOF, &token);

    assert(ch == EOF);
    assert(token.ltype == expect_type);
    assert(strcmp(token.u.name, expect_name) == 0);
}

static void test_parse_one_open_curly() {
    char* input = "{";
    char expect_char = '{';
    int expect_type = OPEN_CURLY;

    struct Token token = { UNKNOWN, {0} };
    int ch;

    cl_getc_set_src(input);
    ch = parse_one(EOF, &token);

    assert(ch == EOF);
    assert(token.ltype == expect_type);
    assert(token.u.onechar == expect_char);
}

static void test_parse_one_close_curly() {
    char* input = "}";
    char expect_char = '}';
    int expect_type = CLOSE_CURLY;

    struct Token token = { UNKNOWN, {0} };
    int ch;

    cl_getc_set_src(input);
    ch = parse_one(EOF, &token);

    assert(ch == EOF);
    assert(token.ltype == expect_type);
    assert(token.u.onechar == expect_char);
}

static void unit_tests() {
    test_parse_one_empty_should_return_END_OF_FILE();
    test_parse_one_number();
    test_parse_one_executable_name();
    test_parse_one_literal_name();
    test_parse_one_open_curly();
    test_parse_one_close_curly();
}

int main() {
    unit_tests();

    cl_getc_set_src("123 45 add /some { 2 3 add } def");
    parser_print_all();
    return 0;
}