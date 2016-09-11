#pragma once

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#include "../util/collections/fifo.h"

/* Reserve the top 100 for root ast constructs */
typedef enum {
	TOK_EOF = 100,
	TOK_IDENT,
	TOK_INTEGER_LITERAL,
	TOK_TYPE_S8,
	TOK_TYPE_S16,
	TOK_TYPE_S32,
	TOK_TYPE_S64,
	TOK_TYPE_U8,
	TOK_TYPE_U16,
	TOK_TYPE_U32,
	TOK_TYPE_U64
} TokenType;

struct Token;

typedef union {
	char* string;
	int64_t* integer;
} TokenValue;

typedef struct {
	size_t line;
	size_t column;
} TokenPos;

typedef struct Token {
	TokenType type;
	TokenValue* val;
	TokenPos pos;
	size_t len;
} Token;

typedef struct {
	char* fname;
	FILE* fp;
	char lookahead;
	char previous;
	TokenPos current_pos;
	TokenPos start;
} LexerContext;

LexerContext init_lexer(char* fname);
void destroy_lexer();
void destroy_token(void* tok);

FIFO* lex(LexerContext lexer);
void dump_tokens();

