#ifndef writer_h
#define writer_h
#include <stdio.h>
//#include "../controller/controller.h"

typedef struct ControlStucture Controller;



struct CliWriterStucture { // linked list node
    Controller *ctrl;
};
typedef struct CliWriterStucture CliWriter;

int readToArray(CliWriter *writer);

CliWriter initWriter(Controller *ctrl);
#endif

