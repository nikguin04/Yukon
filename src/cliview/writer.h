#ifndef writer_h
#define writer_h
#include <stdio.h>
#include "../controller/controller.h"


typedef struct CliWriterStucture { // linked list node
    Controller *ctrl;
} CliWriter;

int readToArray(CliWriter *writer);

CliWriter initWriter(Controller *ctrl);

#endif