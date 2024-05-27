#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




typedef struct 
{
    char* buffer;
    ssize_t buffer_length;
    ssize_t input_legth;
} InputBuffer;

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
        if(strcmp(input->buffer, ".exit" ) == 0){
            printf("%zd\n", input->buffer_length);
            close_input_buffer(input);
            exit(EXIT_SUCCESS);
        } else {
            printf("Unrecognized command '%s'.\n", input->buffer);
        }
    }
}
 

