#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND 
} MetaCommandResult;

typedef enum{
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

typedef enum{
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

typedef struct{
    StatementType type;
} Statement;

typedef struct 
{
    char* buffer;
    ssize_t buffer_length;
    ssize_t input_legth;
} InputBuffer;

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement){
    if(strncmp(input_buffer->buffer, "insert", 6) == 0){
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }

    if(strcmp(input_buffer->buffer, "select") == 0){
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}

MetaCommandResult do_meta_command(InputBuffer* input_buffer){
    if(strcmp(input_buffer->buffer, ".exit" ) == 0){
            exit(EXIT_SUCCESS);
        } else {
            return META_COMMAND_UNRECOGNIZED_COMMAND;
        }
}

void execute_statement(Statement * statement){
    switch(statement->type){
        case(STATEMENT_INSERT):
            printf("INsert done here \n");
            break;
        case(STATEMENT_SELECT):
            printf("select done here\n");
            break;
    }
}

InputBuffer* new_input_buffer(){
    InputBuffer* input_buffer = malloc (sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_legth = 0;

    return input_buffer;
}

void print_primpt(){
    printf("db > ");
}

void read_input(InputBuffer* input_buffer){
    ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if(bytes_read <= 0){
        printf("ERROR READING INPUT \n");
        exit(EXIT_FAILURE);
    }
    input_buffer->input_legth = bytes_read - 1;
    input_buffer->buffer[bytes_read -1] = 0;
}

void close_input_buffer(InputBuffer* input_buffer){
    free(input_buffer-> buffer);
    free(input_buffer);
}


int main(int argc, char* argv[]) {

    InputBuffer* input = new_input_buffer();
    while(true){
        print_primpt();
        read_input(input);
        if(input->buffer[0] == "."){
            switch(do_meta_command(input)){
                case (META_COMMAND_SUCCESS):
                    continue;
                case (META_COMMAND_UNRECOGNIZED_COMMAND):
                    printf("Unrecognized command '%s'\n", input->buffer);
            }
        }
        Statement statement;
        switch (prepare_statement(input, &statement))
        {
        case (PREPARE_SUCCESS):
            break;
        
        case (PREPARE_UNRECOGNIZED_STATEMENT):
            printf("Unrecognized keyword at start of '%s'.\n",input->buffer);
            continue;
        }

        execute_statement(&statement);
        printf("executed\n");


    }
}
 

