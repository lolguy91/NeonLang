#ifndef OPERATOR_H
#define OPERATOR_H
struct operator{
    struct statement (*parse)(struct token* tokens, struct scope* scope,uint8_t num_tokens_till_semi);
    //TODO: codegen function
};

#endif