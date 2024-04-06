#include "writer.h"


int readToArray(CliWriter *writer) {
	printf("Hello World! from writer");
    printf("Please input int into array: ");
    int input_value;
    scanf("%d", &input_value);

    addIntToModelArray(writer->ctrl, &input_value);

    printf("Current int: %d", writer->ctrl->val);

	return 0;
}

CliWriter initWriter(Controller *ctrlptr) {
    CliWriter writer;
    writer.ctrl = ctrlptr;
    return writer;
}
