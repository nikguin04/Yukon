#include <stdio.h>
#include <model/model.h>
#include <controller/controller.h>
#include <cliview/writer.h>


int main() {
	Model *model = (Model*) malloc(sizeof(Model));
	initModel(model);
	Controller *ctrl = (Controller*) malloc(sizeof(Controller));
	initController(ctrl, model);
	CliWriter *writer = (CliWriter*) malloc(sizeof(CliWriter));
	initWriter(writer, ctrl);
	

	StartReadingLoop(writer);
	return 0;
}
