#include <stdio.h>
#include <model/model.h>
#include <controller/controller.h>
#include <cliview/writer.h>


int main() {
	Model model;
	initModel(&model);
	Controller ctrl;
	initController(&ctrl, &model);
	CliWriter writer;
	initWriter(&writer, &ctrl);
	
	//ctrl.model = &model;
	/*for (int i = 0; i < 10; i++) {
		readToArray(&writer);
	}*/
	PromptLoadDeck(&ctrl);
	PrintDeck(model.deck);
	return 0;
}
