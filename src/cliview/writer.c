#include "writer.h"

void initWriter(CliWriter *writer, Controller *ctrl) {
	writer->ctrl = ctrl;
	writer->last_command = NULL;
	writer->last_command_result = NULL;
}
