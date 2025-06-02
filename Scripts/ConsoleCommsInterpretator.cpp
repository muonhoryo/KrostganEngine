#pragma once

#include <ConsoleCommsInterpretator.h>
#include <string>
#include <iostream>
#include <EngineCore.h>
#include <DivineCommander.h>
#include <Extensions.h>


using namespace KrostganEngine;
using namespace KrostganEngine::Debug;
using namespace KrostganEngine::Core;
using namespace std;

void ConsoleCommsInterpretator::ExecuteCommand(string input) {
	if (input.find(ZOOM_COMMAND) != string::npos)
	{
		if (InterpretateComm_Zoom(input)) {
			return;
		}
	}
	else if (input.find(DIVIVE_COMMANDER_COMMAND) != string::npos) {

		if (InterpretateComm_DivComm(input)) {
			return;
		}
	}
	else if (input.find(CAMERA_MOVING_COMMAND) != string::npos) {
		if (InterpretateComm_CamMov(input)) {
			return;
		}
	}
	cout << "Unknown command: " << input << endl;
};

bool ConsoleCommsInterpretator::InterpretateComm_Zoom(string& input) {
	auto syntax = SplitCommandSyntax(input);
	if (syntax->size() != 2 ||
		syntax->at(0) != ZOOM_COMMAND){

		return false;
	}

	float zoom = stof((*syntax)[1].c_str()); //¬€¬≈—“» ¬ √ÀŒ¡¿À‹Õ€≈  ŒÕ—“¿Õ“€
	if (zoom <= 0) {
		cout << "Zoom value cannot be less than zero" << endl;
		return false;
	}
	Engine::SetZoom(zoom);
	cout << "Zoom was set to " << zoom << endl;
	return true;
}
bool ConsoleCommsInterpretator::InterpretateComm_DivComm(string& input) {

	auto syntax = SplitCommandSyntax(input);
	if (syntax->size() != 1 ||
		syntax->at(0)!=DIVIVE_COMMANDER_COMMAND) {
		
		return false;
	}

	if (DivineCommander::GetActivity()) {
		
		DivineCommander::TurnOff();
		cout << "Divine commander is off-line" << endl;
	}
	else {
		
		DivineCommander::TurnOn();
		cout << "Divine commander is on-line" << endl;
	}
	return true;
}
bool ConsoleCommsInterpretator::InterpretateComm_CamMov(string& input) {

	auto syntax = SplitCommandSyntax(input);
	if (syntax->size() != 3 ||
		syntax->at(0) != CAMERA_MOVING_COMMAND) {

		return false;
	}

	Vector2f pos;
	pos.x= stof((*syntax)[1].c_str());
	pos.y= stof((*syntax)[2].c_str());

	cout << "Set camera to position: " << ToString<float>(pos) << endl;
	Engine::SetCameraPos(pos);
	return true;

}

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