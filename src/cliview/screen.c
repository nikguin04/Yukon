#include "screen.h"

void UpdateScreen(CliWriter *writer) {
	// Clear screen for clean printing and home
	printf("\x1B[2J\x1B[H");
	// Check here if game is paused, etc...
	printYukonModel(writer->ctrl->model->yukon, writer->ctrl->model->optionIgnoreHidden);

	// Set to hidden again if needed
	if (writer->ctrl->model->optionIgnoreHidden) { writer->ctrl->model->optionIgnoreHidden = false; }
	printf("LAST Command: %s\n", writer->last_command);
	printf("Message: %s\n", writer->last_command_result);
	printf("INPUT > ");
}
