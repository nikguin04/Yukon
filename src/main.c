#include <stdio.h>
#include <controller/controller.h>
#include <cliview/writer.h>
//#include <model/model.h>

int main() {
	Controller ctrl;
	CliWriter writer = initWriter(&ctrl);
	ctrl = initController();
	readToArray(&writer);
	/*Model model = initModel(&writer);
	//ctrl.model = &model;
	for (int i = 0; i < 10; i++) {
		readToArray(&writer);
	}*/
	return 0;
}
