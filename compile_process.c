#include <stdio.h>
#include <stdlib.h>

#include "compiler.h"

struct compile_process *compile_process_create(const char *filename, const char *output_filename, int flags) {
    FILE *compile_file = fopen(filename, "r");
    
    if (!compile_file) {
        return NULL;
    }

    FILE *output_file = NULL;
    
    if (output_filename) {
        output_file = fopen(output_filename, "w");

        if (!output_file) {
            return NULL;
        }
    }
    
    struct compile_process *process = malloc(sizeof(struct compile_process));

    process->flags = flags;
    process->compile_file.fp = compile_file;
    process->output_file = output_file;

    return process;
}