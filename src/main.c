#include "main.h"

int main(int argc, char *argv[]) {
	Model *model = (Model *) malloc(sizeof(Model));
	Controller *ctrl = (Controller *) malloc(sizeof(Controller));
	initModel(model);
	initController(ctrl, model);

#ifdef USE_CLI
	CliWriter *writer = (CliWriter *) malloc(sizeof(CliWriter));
	initWriter(writer, ctrl);
	StartReadingLoop(writer);
#else
#ifdef OS_Windows
	SetProcessDPIAware(); // This disables scaling on screens (good for high-res screens)
#endif
	sdl_view_init(ctrl);
#endif
	return 0;
}
