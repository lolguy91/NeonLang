#ifndef __PARSER_H__
#define __PARSER_H__

#include <Tokenizer.h>
#include <stdbool.h>
#include <ast.h>

struct program* parse(struct Token* tokens);

#endif // __PARSER_H__