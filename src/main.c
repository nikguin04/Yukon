#include <stdio.h>
#include <model/model.h>
#include <controller/controller.h>
#include <cliview/writer.h>


int main() {
	Model model;
	initModel(&model);
	Controller ctrl = initController(&model);
	CliWriter writer = initWriter(&ctrl);

	readToArray(&writer);
	/*
	//ctrl.model = &model;
	for (int i = 0; i < 10; i++) {
		readToArray(&writer);
	}*/
	return 0;
}
