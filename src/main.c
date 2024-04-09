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
	//PrintDeck(model.deck); // does not work after load deck beacuse we load into columns and remove next pointers from linked list
	print_yukon_model(model.yukon);

	/*YukonToDeck(model.deck, model.yukon); // for testing
	PrintDeck(model.deck);*/
	return 0;
}
