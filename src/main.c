#include "model/model.h"
#include "controller/controller.h"
#include "cliview/command_reader.h"

#include "sdlview/sdlinit.h"

#ifdef __unix__ /* __unix__ is usually defined by compilers targeting Unix systems */
	#define OS_Unix
#elifdef _WIN32 /* _WIN32 is usually defined by compilers targeting 32-bit or 64-bit Windows */
	#define OS_Windows
	#include <windows.h>
	#include <WinUser.h>
#endif

int main(int argc, char *argv[]) {
	Model *model = (Model *) malloc(sizeof(Model));
	Controller *ctrl = (Controller *) malloc(sizeof(Controller));
	CliWriter *writer = (CliWriter *) malloc(sizeof(CliWriter));
	initModel(model);
	initController(ctrl, model);
	initWriter(writer, ctrl);

//	StartReadingLoop(writer);
//	printf("hello");

#ifdef OS_Windows
	SetProcessDPIAware(); // This disables scaling on screens (good for high res screens)
#endif
	sdl_view_init(ctrl);
	return 0;
}
