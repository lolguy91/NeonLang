#ifndef LANGFEAT_H
#define LANGFEAT_H

#include <ast.h>

#define FEATTYPE_CHECKER 0
#define FEATTYPE_OPERATOR 1

// Feet haha
struct LangFeat{
    uint8_t type;
    uint16_t parent_id;
    union{
        struct {
            char** error_messages;
            uint8_t (*check)(struct statement* tocheck, struct scope* scope);
        } checker;
        struct {
            statement (*parse)(struct token* tokens, struct scope* scope,uint8_t num_tokens_till_semi);
            //TODO: codegen function
        } operator;
    };
};
#endif 