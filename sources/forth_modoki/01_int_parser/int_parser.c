#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

static const char* const input = "123 456  1203";

const char* parse_int(const char* c, int* parsed) {
    while (*c && !isdigit(*c)) c++;
    if (*c == '\0') {
        fprintf(stderr, "unexpected end of string\n");
        exit(1);
    }

    int v = 0;
    while (*c && isdigit(*c)) {
        v *= 10;
        v += *c - '0';
        c++;
    }

    *parsed = v;

    return c;
}

int main() {
    int answer1 = 0;
    int answer2 = 0;
    int answer3 = 0;

    const char* c = input;
    c = parse_int(c, &answer1);
    c = parse_int(c, &answer2);
    parse_int(c, &answer3);

    // verity result.
    assert(answer1 == 123);
    assert(answer2 == 456);
    assert(answer3 == 1203);

    return 0;
}