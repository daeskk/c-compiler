#include <stdio.h>

#include "compiler.h"

int main() {
    int res = compile_file("./test.c", "./test", 0);

    switch (res)
    {
    case COMPILER_FILE_COMPILED_OK:
        printf("everything compiled fine\n");
        break;
    
    case COMPILER_FAILED_WITH_ERRORS:
        printf("compile error\n");
        break;
    
    default:
        printf("unknown status\n");
        break;
    }


    return 0;
}