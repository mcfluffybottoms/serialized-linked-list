#include "App.hpp"
#include <cstring>

int main(int argc, char* argv[]) {
	AppFunction func= ParseAndSerialize;
	if (argc > 1)
	{
		func= strcmp(argv[0], "deserialize") ? Deserialize : ParseAndSerialize;
	}
	App app;
	app.run(func);
}