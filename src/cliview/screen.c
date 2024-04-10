#include "screen.h"

void UpdateScreen(CliWriter *writer) {
    // Check here if game is paused, etc...
    printf("LAST Command: %s\n", writer->last_command);
    printf("Message: %s\n", writer->last_command_result);
}