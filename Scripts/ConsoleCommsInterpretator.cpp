#pragma once

#include <ConsoleCommsInterpretator.h>
#include <string>
#include <iostream>
#include <EngineCore.h>
#include <DBG_DivineCommander.h>
#include <DBG_ImmortalArmy.h>
#include <Extensions.h>


using namespace KrostganEngine;
using namespace KrostganEngine::Debug;
using namespace KrostganEngine::Core;
using namespace std;

void ConsoleCommsInterpretator::ExecuteCommand(const string& input) {
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
	else if (input.find(IMMORTAL_ARMY_COMMAND) != string::npos) {
		if (InterpretateComm_ImmArmy(input))
			return;
	}
	else if (input.find(DISARM_COMMAND) != string::npos) {
		if (InterpretateComm_Disarm(input))
			return;
	}
	else if (input.find(REARM_COMMAND) != string::npos) {
		if (InterpretateComm_Rearm(input))
			return;
	}
	else if (input.find(WARFOG_COMMAND) != string::npos) {
		if (InterpretateComm_WarFog(input))
			return;
	}
	else if (input.find(FRACSET_COMMAND) != string::npos) {
		if (InterpretateComm_FracSet(input))
			return;
	}
	PrintInterpetatorMessage("Unknown command: " + input);
};

bool ConsoleCommsInterpretator::InterpretateComm_Zoom(const string& input) {
	auto& syntax = SplitCommandSyntax(input);
	if (syntax.size() != 2 ||
		syntax.at(0) != ZOOM_COMMAND){

		return false;
	}

	float zoom = stof(syntax[1].c_str()); //¬€¬≈—“» ¬ √ÀŒ¡¿À‹Õ€≈  ŒÕ—“¿Õ“€
	if (zoom <= 0) {
		PrintInterpetatorMessage("Zoom value cannot be less than zero");
		return false;
	}
	Engine::SetZoom(zoom);
	PrintInterpetatorMessage("Zoom was set to " + std::to_string(zoom));
	return true;
}
bool ConsoleCommsInterpretator::InterpretateComm_DivComm(const string& input) {

	auto& syntax = SplitCommandSyntax(input);
	if (syntax.size() != 1 ||
		syntax.at(0)!=DIVIVE_COMMANDER_COMMAND) {
		
		return false;
	}

	if (DBG_DivineCommander::GetActivity()) {
		
		DBG_DivineCommander::TurnOff();
		PrintInterpetatorMessage("Divine commander is offline");
	}
	else {
		
		DBG_DivineCommander::TurnOn();
		PrintInterpetatorMessage("Divine commander is online");
	}
	return true;
}
bool ConsoleCommsInterpretator::InterpretateComm_CamMov(const string& input) {

	auto& syntax = SplitCommandSyntax(input);
	if (syntax.size() != 3 ||
		syntax.at(0) != CAMERA_MOVING_COMMAND) {

		return false;
	}

	Vector2f pos;
	pos.x= stof(syntax[1].c_str());
	pos.y= stof(syntax[2].c_str());

	Engine::SetCameraPos(pos);
	PrintInterpetatorMessage("Set camera to position: " + to_string<float>(pos));
	return true;

}
bool ConsoleCommsInterpretator::InterpretateComm_ImmArmy(const string& input) {
	auto& syntax = SplitCommandSyntax(input);
	if (syntax.size() != 1 ||
		syntax.at(0) != IMMORTAL_ARMY_COMMAND) {

		return false;
	}

	if (DBG_ImmortalArmy::GetActivity()) {

		DBG_ImmortalArmy::TurnOff();
		PrintInterpetatorMessage("Immortal army is offline");
	}
	else {

		DBG_ImmortalArmy::TurnOn();
		PrintInterpetatorMessage("Immortal army is online");
	}
	return true;
}
bool ConsoleCommsInterpretator::InterpretateComm_Disarm(const string& input) {
	auto& syntax = SplitCommandSyntax(input);
	if (syntax.size() != 1 ||
		syntax.at(0) != DISARM_COMMAND) {
		
		return false;
	}

	bool hasChanged = false;
	bool disarm = true;
	Entity* parObj = nullptr;
	auto it = GroupSelectionSystem::GetEntitiesBegIter();
	auto end = GroupSelectionSystem::GetEntitiesEndIter();
	while (it != end) {		///define disarm- or arm-mode
		parObj = dynamic_cast<Entity*>((*it)->GetPtr_t());
		if (parObj != nullptr) {
			if (parObj->GetBattleStats().GetSavedAAStatsCount() != 0) {
				hasChanged = true;
				disarm = parObj->GetBattleStats().GetCurrAAStats() != nullptr;
				break;
			}
		}
		++it;
	}
	while (it != end) {
		parObj = dynamic_cast<Entity*>((*it)->GetPtr_t());
		if (parObj != nullptr) {
			if (parObj->GetBattleStats().GetSavedAAStatsCount() != 0 ||
				parObj->GetBattleStats().GetCurrAAStats()==nullptr != disarm)	//Check that we cannot override the same state of AAStats
			{
				parObj->GetBattleStats().SetAAStats(disarm ? -1 : 0);
			}
		}
		++it;
	}
	if (hasChanged) {
		if (disarm) {
			PrintInterpetatorMessage("Disarm entities");
		}
		else {
			PrintInterpetatorMessage("Arm entities");
		}
	}

	return true;
}

bool ConsoleCommsInterpretator::InterpretateComm_Rearm(const string& input) {
	auto& syntax = SplitCommandSyntax(input);
	if (syntax.size() != 2 ||
		syntax.at(0) != REARM_COMMAND) {

		return false;
	}

	int index = stoi(syntax[1]);
	if (index < -1) {
		PrintInterpetatorMessage("Invalid index of AAStats: " + index);
		return false;
	}
	bool hasChanged = false;
	Entity* parObj = nullptr;
	auto it = GroupSelectionSystem::GetEntitiesBegIter();
	auto end = GroupSelectionSystem::GetEntitiesEndIter();
	while (it != end) {
		parObj = dynamic_cast<Entity*>((*it)->GetPtr_t());
		if (parObj != nullptr &&
			(int)parObj->GetBattleStats().GetSavedAAStatsCount() > index &&
			(int)parObj->GetBattleStats().GetCurrAAStatsIndex() != index) {
			
			hasChanged = true;
			parObj->GetBattleStats().SetAAStats(index);
		}
		++it;
	}
	if (hasChanged) {
		PrintInterpetatorMessage("Rearm entities to AAStats with index: " + std::to_string(index));
	}

	return true;
}

bool ConsoleCommsInterpretator::InterpretateComm_WarFog(const string& input) {
	auto& syntax = SplitCommandSyntax(input);
	if (syntax.size() != 1 ||
		syntax.at(0) != WARFOG_COMMAND) {

		return false;
	}

	WarFogStencilGen::SetActivity(!WarFogStencilGen::GetActivity());

	PrintInterpetatorMessage(WarFogStencilGen::GetActivity() ?
		"Set WarFog active" :
		"Set WarFog inactive");

	return true;
}

bool ConsoleCommsInterpretator::InterpretateComm_FracSet(const string& input) {
	auto& syntax = SplitCommandSyntax(input);
	if (syntax.size() != 2 ||
		syntax.at(0) != FRACSET_COMMAND) {

		return false;
	}

	Fraction frac;

	if (FractionsSystem::FractionNames.find(syntax[1]) != FractionsSystem::FractionNames.end())
		frac = FractionsSystem::FractionNames.at(syntax[1]);
	else {
		PrintInterpetatorMessage("Unknown fraction name");
		return false;
	}
	

	IFractionMember* fracMem = nullptr;
	vector<IFractionMember*> fracMembs = vector<IFractionMember*>(GroupSelectionSystem::GetSelectionCount());
	for (auto mem : fracMembs) {
		mem = nullptr;
	}
	size_t fracMembsCount = 0;
	auto it = GroupSelectionSystem::GetEntitiesBegIter();
	auto end = GroupSelectionSystem::GetEntitiesEndIter();
	while (it != end) {

		fracMem = dynamic_cast<IFractionMember*>((*it)->GetPtr_t());
		if (fracMem != nullptr) {
			fracMembs[fracMembsCount] = fracMem;
			++fracMembsCount;
		}
		++it;
	}
	for (auto mem : fracMembs) {
		if (mem != nullptr)
			mem->SetFraction(frac);
	}
	return true;
}

vector<string>& ConsoleCommsInterpretator::SplitCommandSyntax(const string& input) {
	vector<string>& syntax = *new vector<string>();
	const char* rwInp = input.c_str();
	size_t size = input.size() + 1;
	char* inpCopy = new char[size];
	strcpy_s(inpCopy,size, rwInp);
	char* nextTok = nullptr;
	char* token = strtok_s(inpCopy, &SPLIT_COMM_DELIMS,&nextTok);
	while (token != nullptr) {
		syntax.push_back(token);
		token = strtok_s(nullptr, &SPLIT_COMM_DELIMS,&nextTok);
	}
	return syntax;
};
void ConsoleCommsInterpretator::PrintInterpetatorMessage(const string& message) {
	cout << "DEBUG CONSOLE INTERPRETATOR: " << endl <<"\t\t\t"<< message << endl;
}