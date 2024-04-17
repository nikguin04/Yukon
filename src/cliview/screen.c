#include "screen.h"

void UpdateScreen(CliWriter *writer) {
	// Go to top left and clear screen
	printf("\x1B[H\x1B[J");
	// Check here if game is paused, etc...
	printYukonModel(writer->ctrl->model->yukon, writer->ctrl->model->optionIgnoreHidden);

	// Set to hidden again if needed
	if (writer->ctrl->model->optionIgnoreHidden) { writer->ctrl->model->optionIgnoreHidden = false; }
	printf("LAST Command: %s\n", writer->last_command);
	printf("Message: %s\n", writer->last_command_result);
	printf("INPUT > ");
}
