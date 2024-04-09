#ifndef command_reader_h
#define command_reader_h
#include <string.h>
#include <stdbool.h>
#include "writer.h"
#include "command_controller.h"

typedef void (*CommandFunction)(Controller*, char*);
typedef struct commandStruct { // linked list node
    char *input;
    bool takes_input;
    char *friendly_name;
    CommandFunction function;
} Command;

#define COMMAND_COUNT 2
Command commands[COMMAND_COUNT+1] = {
 {'LD', true, 'Load', LoadDeckWithInput},
 {'SW', false, 'Show', ShowDeck}
};


// WORSØE PLEASE FIX WITH BEAUTIFUL MACRO!
typedef struct ll_node_cmd { // linked list node
    Command *command;
    struct ll_node_cmd *next;
    bool skip;
} ll_node_command;

void StartReadingLoop(CliWriter *writer);
Command* MatchCommand(char* cmdinput, size_t len);
void GetInput(char* string, size_t* size, size_t* len);
size_t getline(char **lineptr, size_t *n, FILE *stream);


#endif
