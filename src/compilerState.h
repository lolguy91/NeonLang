#ifndef CS_H
#define CS_H

#include <langFeat.h>
#include <scope.h>
#include <Tokenizer.h>
#include <ast.h>

struct CompilerState{
    struct Token* tokens;
    uint16_t num_tokens;
    struct LangFeat* features;
    uint16_t num_features;
    struct identifier* identifiers;
    uint16_t num_identifiers;
    struct program *ast_root;
};
#endif