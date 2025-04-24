
#include <ConsoleCommsInterpretator.h>
#include <string>
#include <iostream>
#include <EngineCore.h>


using namespace KrostganEngine::Debug;
using namespace KrostganEngine::Core;
using namespace std;

void ConsoleCommsInterpretator::ExecuteCommand(string input) {
	if (input.find(ZOOM_COMMAND) != string::npos)
	{
		auto syntax = SplitCommandSyntax(input);
		if (syntax->size() != 2)
		{
			cout << "Incorrect arguments for {zoom}-command: "<<syntax->size()<<" / 2" << endl;
			return;
		}
		float zoom = stof((*syntax)[1].c_str()); //ÂÛÂÅÑÒÈ Â ÃËÎÁÀËÜÍÛÅ ÊÎÍÑÒÀÍÒÛ
		if (zoom <= 0) {
			cout << "Zoom value cannot be less than zero" << endl;
			return;
		}
		Engine::SetZoom(zoom);
		cout << "Zoom was set to "<<zoom<<endl;
	}
	else {
		cout << "Unknown command: " << input << endl;
	}
};
vector<string>* ConsoleCommsInterpretator::SplitCommandSyntax(string input) {
	vector<string>* syntax = new vector<string>();
	const char* rwInp = input.c_str();
	size_t size = input.size() + 1;
	char* inpCopy = new char[size];
	strcpy_s(inpCopy,size, rwInp);
	char* nextTok = nullptr;
	char* token = strtok_s(inpCopy, &SPLIT_COMM_DELIMS,&nextTok);
	while (token != nullptr) {
		syntax->push_back(token);
		token = strtok_s(nullptr, &SPLIT_COMM_DELIMS,&nextTok);
	}
	return syntax;
};