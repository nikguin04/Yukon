#include <stdio.h>
#include "model/model.h"
#include "controller/controller.h"
#include "cliview/command_reader.h"

#include "sdlview/sdlinit.h"

int main(int argc, char *argv[]) {
	/*Model *model = (Model *) malloc(sizeof(Model));
	Controller *ctrl = (Controller *) malloc(sizeof(Controller));
	CliWriter *writer = (CliWriter *) malloc(sizeof(CliWriter));
	initModel(model);
	initController(ctrl, model);
	initWriter(writer, ctrl);

	StartReadingLoop(writer);*/
	sdl_view_init();
	return 0;
}
