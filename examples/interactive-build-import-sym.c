// Build me with:
// ->  gcc interactive-build-import-sym.c libinteractive-build.a

#include <stdio.h>

extern char *_ZJ0l16DEVELOPERS__NAME1s0;

int main()
{
    printf("Hello, %s!\n", _ZJ0l16DEVELOPERS__NAME1s0);
}