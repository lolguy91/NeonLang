# NeonLang

neolang is a new powerfull coding language that is a coding language that is a coding language that is a coding language that is a coding language.

grammar:
program           ::= declaration_list

declaration_list  ::= declaration
                   | declaration_list declaration

declaration       ::= variable_declaration
                   | function_declaration

variable_declaration ::= type_specifier identifier_list ';'

type_specifier    ::= 'u8' | 'u16' | 'u32' | 'i8' | 'i16' | 'i32' | 'bool' | 'float'

identifier_list   ::= identifier
                   | identifier_list ',' identifier

function_declaration ::= type_specifier function_name '(' parameter_list ')' compound_statement

parameter_list    ::= parameter
                   | parameter_list ',' parameter

parameter         ::= type_specifier identifier

compound_statement ::= '{' statement_list '}'

statement_list    ::= statement
                   | statement_list statement

statement         ::= expression_statement
                   | variable_declaration
                   | compound_statement
                   | selection_statement
                   | iteration_statement
                   | return_statement

expression_statement ::= expression ';'

expression        ::= assignment_expression

assignment_expression ::= conditional_expression
                   | identifier '=' assignment_expression

conditional_expression ::= logical_or_expression
                   | logical_or_expression '?' expression ':' conditional_expression

logical_or_expression ::= logical_and_expression
                   | logical_or_expression '||' logical_and_expression

logical_and_expression ::= equality_expression
                   | logical_and_expression '&&' equality_expression

equality_expression ::= relational_expression
                   | equality_expression '==' relational_expression
                   | equality_expression '!=' relational_expression

relational_expression ::= additive_expression
                   | relational_expression '<' additive_expression
                   | relational_expression '>' additive_expression
                   | relational_expression '<=' additive_expression
                   | relational_expression '>=' additive_expression

additive_expression ::= multiplicative_expression
                   | additive_expression '+' multiplicative_expression
                   | additive_expression '-' multiplicative_expression

multiplicative_expression ::= unary_expression
                   | multiplicative_expression '*' unary_expression
                   | multiplicative_expression '/' unary_expression
                   | multiplicative_expression '%' unary_expression

unary_expression  ::= postfix_expression
                   | '!' unary_expression
                   | '-' unary_expression

postfix_expression ::= primary_expression
                   | postfix_expression '(' argument_expression_list ')'

argument_expression_list ::= assignment_expression
                   | argument_expression_list ',' assignment_expression

primary_expression ::= identifier
                   | constant
                   | '(' expression ')'

constant          ::= integer_constant
                   | float_constant
                   | boolean_constant

integer_constant  ::= [0-9]+
float_constant    ::= [0-9]+ '.' [0-9]+
boolean_constant  ::= 'true' | 'false'

identifier        ::= [a-zA-Z_][a-zA-Z0-9_]*

function_name     ::= identifier