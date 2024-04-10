#include "writer.h"

int readToArray(CliWriter *writer) {
	printf("Hello World! from writer");
	printf("Please input int into array: ");
	int input_value;
	scanf("%d", &input_value);

	addIntToModelArray(writer->ctrl, &input_value);

	printList(writer->ctrl->model->intlist);
	return 0;
}

void printList(ll_node_int *list) {
	printf("Elements in list: ");
	ll_node_int *elem = list;
	while (elem != NULL) {
		printf("%d, ", elem->val);
		elem = elem->next;
	}
	printf("\n");
}

void initWriter(CliWriter *writer, Controller *ctrl) {
	writer->ctrl = ctrl;
	writer->last_command = NULL;
	writer->last_command_result = NULL;
}

void PromptLoadDeck(Controller *ctrl) {
	printf("Please input path to load deck from:");
	char input_value[255];
	scanf("%s", &input_value);
	LoadDeckFromFile(ctrl, input_value);
}
