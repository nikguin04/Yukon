#include "command_reader.h"

Command commands[COMMAND_COUNT+1] = {
 {"LD", true, "Load", LoadDeckWithInput},
 {"SW", false, "Show", ShowDeck}
};

void StartReadingLoop(CliWriter *writer) {
    while (true) { // Continues until user quits
        char *string = NULL;
        size_t size = 0;
        size_t len = 0;
        GetInput(&string, &size, &len);
        MatchCommand(string, &len);
        free(string);
    }
}

Command* MatchCommand(char* cmdinput, size_t *len) {
    ll_node_command *candidatell = (ll_node_command*) malloc(sizeof(ll_node_command));
    ll_node_command *candidate_tail = candidatell;
    for (int i = 0; i < COMMAND_COUNT; i++) {
        candidate_tail->command = &commands[i];
        candidate_tail->next = (ll_node_command*) malloc(sizeof(ll_node_command));
        candidate_tail->skip = false;
        candidate_tail = candidate_tail->next;
    }
    
    for (int a = 0; a < *len+1; a++) { // plus one here so we hit a null or space
        candidate_tail = candidatell;
        bool allskip = true;
        for (int i = 0; i < COMMAND_COUNT; i++) {
            if (candidate_tail->skip) { candidate_tail = candidate_tail->next; continue; }
            allskip = false;
            char candidate_char = candidate_tail->command->input[a];

            if (candidate_char != cmdinput[a] || candidate_char == NULL) { //  || candidate_char == (candidate_tail->command->takes_input ? '\n' : ' ')
                candidate_tail->skip = true;
                if ((cmdinput[a] == ' ' || cmdinput[a] == NULL) && a == strlen(candidate_tail->command->input)) {
                    printf("TEMP! found cmd!, %s", candidate_tail->command->friendly_name);
                    Command* ret = candidate_tail->command;
                    return ret;
                }
            }
            candidate_tail = candidate_tail->next;
        }
        if (allskip == true) {printf("COMMAND NOT FOUND!"); return NULL;}
    }
}


void GetInput(char** string, size_t* size, size_t* len) {
    
    getline(string, size, stdin);
    if (size < 0) {
        puts("couldn't read the input");
        free(*string);
        return;
    }
    *len = strlen(*string);


    // print the string
    printf("<%s> is length %ld\n", *string, *len);

    // free the memory used by string when returned!
}

size_t getline(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL) {
        return -1;
    }
    if (stream == NULL) {
        return -1;
    }
    if (n == NULL) {
        return -1;
    }
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF) {
        return -1;
    }
    if (bufptr == NULL) {
        bufptr = malloc(128);
        if (bufptr == NULL) {
            return -1;
        }
        size = 128;
    }
    p = bufptr;
    while(c != EOF) {
        if ((p - bufptr) > (size - 1)) {
            size = size + 128;
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1;
            }
        }
        if (c == '\n') {
            break;
        }
        *p++ = c; // put this behind the \n check is we want to include \n
        
        c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}