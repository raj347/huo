#include <stdlib.h>
#include <string.h>
#include "structures.h"

void build_array(struct Value_array * array, struct Tokens * tokens){
    while(tokens->tokens[tokens->counter].type != 'e'){
        tokens->counter++;
        if(tokens->tokens[tokens->counter].type == 's'){
            struct Value * val = malloc(sizeof(struct Value));
            val->type = 's';
            val->data.str.length = tokens->tokens[tokens->counter].data.length;
            strcpy(val->data.str.body, tokens->tokens[tokens->counter].data.body);
            array->values[array->size] = val;
            array->size++;
        }
        else if(tokens->tokens[tokens->counter].type == 'n'){
            struct Value * val = malloc(sizeof(struct Value));
            val->data.ln = atol(tokens->tokens[tokens->counter].data.body);
            val->type = 'l';
            array->values[array->size] = val;
            array->size++;
        }
        else if(tokens->tokens[tokens->counter].type == 'b'){
            struct Value * val = malloc(sizeof(struct Value));
            val->type = 'a';
            val->data.array = malloc(sizeof(struct Value_array));
            val->data.array->size = 0;
            build_array(val->data.array, tokens);
            array->values[array->size] = val;
            array->size++;
            // to advance beyond the inner closing bracket, otherwise it
            // will cause the outer array to stop building
            tokens->counter++;
        }
    }
}