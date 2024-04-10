#include "screen.h"

void UpdateScreen(CliWriter *writer) {
	// Clear screen for clean printing and home
	printf("\x1B[2J\x1B[H");
	// Check here if game is paused, etc...
	print_yukon_model(writer->ctrl->model->yukon, writer->ctrl->model->OPTION_IGNORE_HIDDEN);

	// Set to hidden again if needed
	if (writer->ctrl->model->OPTION_IGNORE_HIDDEN) { writer->ctrl->model->OPTION_IGNORE_HIDDEN = false; }
	printf("LAST Command: %s\n", writer->last_command);
	printf("Message: %s\n", writer->last_command_result);
}
