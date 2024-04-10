#include "screen.h"

void UpdateScreen(CliWriter *writer) {
    // Check here if game is paused, etc...
    print_yukon_model(writer->ctrl->model->yukon, writer->ctrl->model->OPTION_IGNORE_HIDDEN);
    if (writer->ctrl->model->OPTION_IGNORE_HIDDEN) {writer->ctrl->model->OPTION_IGNORE_HIDDEN = false;} // set hidden again
    printf("LAST Command: %s\n", writer->last_command);
    printf("Message: %s\n", writer->last_command_result);
}
