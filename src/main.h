#ifndef MAIN_H
#define MAIN_H

#ifdef __unix__ /* __unix__ is usually defined by compilers targeting Unix systems */
	#define OS_Unix
#elifdef _WIN32 /* _WIN32 is usually defined by compilers targeting 32-bit or 64-bit Windows */
	#define OS_Windows
	#include <windows.h>
	#include <WinUser.h>
#endif

#include "model/model.h"
#include "controller/controller.h"

#ifdef USE_CLI
	#include "cliview/command_reader.h"
#else
	#include "sdlview/sdlinit.h"
#endif

#endif
