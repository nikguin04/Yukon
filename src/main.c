#include <stdio.h>
#include "model/model.h"
#include "controller/controller.h"
#include "cliview/command_reader.h"

int main() {
	Model *model = (Model *) malloc(sizeof(Model));
	Controller *ctrl = (Controller *) malloc(sizeof(Controller));
	CliWriter *writer = (CliWriter *) malloc(sizeof(CliWriter));
	initModel(model);
	initController(ctrl, model);
	initWriter(writer, ctrl);

    PrintWelcome(writer);
	StartReadingLoop(writer);
	return 0;
}
