#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "helpers/vector.h"
#include "helpers/buffer.h"

// enums

enum {
    COMPILER_FILE_COMPILED_OK,
    COMPILER_FAILED_WITH_ERRORS,
};

enum {
    TOKEN_TYPE_IDENTIFIER,
    TOKEN_TYPE_KEYWORD,
    TOKEN_TYPE_OPERATOR,
    TOKEN_TYPE_SYMBOL,
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_COMMENT,
    TOKEN_TYPE_NEWLINE
};


// structs

struct token_position {
    int         line;
    int         column;

    const char *filename;
};

struct token {
    int type;
    int flags;

    union { // it has to be only one value
        char            c_val;
        const char     *s_val;
        unsigned int    i_num;
        unsigned long   l_num;
        unsigned long   ll_num;
        void           *any;
    };

    bool        whitespace;       // followed by whitespace, ignored on lex analysis
    const char *between_brackets; // debugging (1+2+3)
};

struct compile_process {
    int flags;

    struct compile_process_input_file {
        FILE        *fp;
        const char  *abs_path;
    } compile_file;

    FILE *output_file;
};

struct lex_process {
    struct token_position         token_position;
    struct vector                *token_vector;
    struct compile_process       *compile_process;

    int                           current_expression_count;
    struct buffer                *parenthesis_buffer;
    struct lex_process_functions *functions;

    void                         *private;
};

// functions prototypes

int compile_file(const char *filename, const char *output_filename, int flags);
struct compile_process *compile_process_create(const char *filename, const char *filename_out, int flags);