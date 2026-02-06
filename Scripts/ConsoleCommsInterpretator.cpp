#pragma once

#include <ConsoleCommsInterpretator.h>
#include <string>
#include <iostream>
#include <_EngineCore.h>
#include <DBG_DivineCommander.h>
#include <DBG_ImmortalArmy.h>
#include <_Extensions.h>

#include <GameEffectsCatalog.h>
#include <_GeneralGameEffects.h>
#include <Ability_Aura.h>
#include <Ability_NonTar_SetAA.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Debug;
using namespace KrostganEngine::Core;
using namespace std;

void ConsoleCommsInterpretator::ExecuteCommand(const string& input) {

	string cpyInput = input;
	FStreamExts::ClearPath(cpyInput);
	auto& syntax = SplitCommandSyntax(cpyInput);
	auto& comDef = syntax[0];

	if (comDef == ZOOM_COMMAND)
	{
		if (InterpretateComm_Zoom(syntax)) {
			return;
		}
	}
	else if (comDef ==DIVIVE_COMMANDER_COMMAND) {

		if (InterpretateComm_DivComm(syntax)) {
			return;
		}
	}
	else if (comDef ==CAMERA_MOVING_COMMAND) {
		if (InterpretateComm_CamMov(syntax)) {
			return;
		}
	}
	else if (comDef ==IMMORTAL_ARMY_COMMAND) {
		if (InterpretateComm_ImmArmy(syntax))
			return;
	}
	else if (comDef == DISARM_COMMAND) {
		if (InterpretateComm_Disarm(syntax))
			return;
	}
	else if (comDef == REARM_COMMAND) {
		if (InterpretateComm_Rearm(syntax))
			return;
	}
	else if (comDef == WARFOG_COMMAND) {
		if (InterpretateComm_WarFog(syntax))
			return;
	}
	else if (comDef == FRACSET_COMMAND) {
		if (InterpretateComm_FracSet(syntax))
			return;
	}
	else if (comDef == PRINT_COMMAND) {
		if (InterpretateComm_Print(syntax))
			return;
	}

	/*else if (input == "testab") {

		auto it = GroupSelectionSystem::GetChoosenEntities_Begin();
		auto end = GroupSelectionSystem::GetChoosenEntities_End();
		Entity* parObj = nullptr;
		while (it != end) {
			parObj = dynamic_cast<Entity*>((*it)->GetPtr_t());
			if (parObj != nullptr) {

				Ability_NonTar_TempEff& ability = *new Ability_NonTar_TempEff(
					*dynamic_cast<ComposeGameEff_Temporal*>(&GameEffectsCatalog::GetObjectInfo(1).InstantiateGameEff()),
					(float)3,
					(size_t)0,
					(std::byte)0);

				parObj->AddAbility(ability);
			}
			++it;
		}
		return;
	}*/
	/*else if (input == "testaura") {

		auto it = GroupSelectionSystem::GetChoosenEntities_Begin();
		auto end = GroupSelectionSystem::GetChoosenEntities_End();
		WorldTransfObj* parObj = nullptr;
		while (it != end) {
			parObj = dynamic_cast<WorldTransfObj*>((*it)->GetPtr_t());
			if (parObj != nullptr) {

				ComposeGameEff_Permanent& deserGameEff = *new ComposeGameEff_Permanent(1);
				auto deserGameEff_gen = new GameEff_Dur_Deserter(Fraction::Neutral);
				deserGameEff_gen->SetOwnedEffect(deserGameEff);
				deserGameEff.AddGameEffect_Durable(*deserGameEff_gen);


				ComposeGameEff_Instant& tickGameEff = *new ComposeGameEff_Instant(2);
				tickGameEff.AddGameEffect(*new GameEff_Inst_AddDurEff(deserGameEff));

				ComposeGameEff_Periodical& gameEff = *new ComposeGameEff_Periodical(tickGameEff, 1, 10000000, 3);

				Aura& aura = *new Aura(15000, Fraction::Neutral, Relation::All, gameEff,*parObj);
			}

			++it;
		}
	}*/
	//else if (input == "testab2") {

	//	auto it = GroupSelectionSystem::GetChoosenEntities_Begin();
	//	auto end = GroupSelectionSystem::GetChoosenEntities_End();
	//	Entity* parObj = nullptr;
	//	while (it != end) {
	//		parObj = dynamic_cast<Entity*>((*it)->GetPtr_t());
	//		if (parObj != nullptr) {

	//			ComposeGameEff_Temporal& gameEff = *new ComposeGameEff_Temporal(10);
	//			gameEff.AddGameEffect_Durable(*new GameEff_Dur_EntBatStatMult(EntityBattleStatType::MaxHP, 10));
	//			auto abil = new Ability_NonTar_TempEff(gameEff, 10);
	//			parObj->AddAbility(*abil);
	//		}
	//		++it;
	//	}
	//	return;
	//}
	PrintInterpetatorMessage("Unknown command: " + input);
};

bool ConsoleCommsInterpretator::InterpretateComm_Zoom(const vector<string>& syntax) {
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
bool ConsoleCommsInterpretator::InterpretateComm_DivComm(const vector<string>& syntax) {

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
bool ConsoleCommsInterpretator::InterpretateComm_CamMov(const vector<string>& syntax) {

	if (syntax.size() != 3 ||
		syntax.at(0) != CAMERA_MOVING_COMMAND) {

		return false;
	}

	Vector2f pos;
	pos.x= stof(syntax[1].c_str());
	pos.y= stof(syntax[2].c_str());

	Engine::SetCameraPos(pos);
	auto& posStr = to_string<float>(pos);
	PrintInterpetatorMessage("Set camera to position: " + posStr);
	delete& posStr;
	return true;

}
bool ConsoleCommsInterpretator::InterpretateComm_ImmArmy(const vector<string>& syntax) {

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
bool ConsoleCommsInterpretator::InterpretateComm_Disarm(const vector<string>& syntax) {
	
	if (syntax.size() != 1 ||
		syntax.at(0) != DISARM_COMMAND) {
		
		return false;
	}

	bool hasChanged = false;
	bool disarm = true;
	Entity* parObj = nullptr;
	auto it = GroupSelectionSystem::GetSelectedEnts_Begin();
	auto end = GroupSelectionSystem::GetSelectedEnts_End();
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

bool ConsoleCommsInterpretator::InterpretateComm_Rearm(const vector<string>& syntax) {
	
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
	auto it = GroupSelectionSystem::GetSelectedEnts_Begin();
	auto end = GroupSelectionSystem::GetSelectedEnts_End();
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

bool ConsoleCommsInterpretator::InterpretateComm_WarFog(const vector<string>& syntax) {
	
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

bool ConsoleCommsInterpretator::InterpretateComm_FracSet(const vector<string>& syntax) {
	
	if (syntax.size() != 2 ||
		syntax.at(0) != FRACSET_COMMAND) {

		return false;
	}

	const Fraction* frac = FractionsSystem::GetFractionByName(syntax[1]);
	if (frac == nullptr) {
		PrintInterpetatorMessage("Unknown fraction name");
		return false;
	}

	IFractionMember* fracMem = nullptr;
	vector<IFractionMember*> fracMembs = vector<IFractionMember*>(GroupSelectionSystem::GetSelectionCount());
	for (auto mem : fracMembs) {
		mem = nullptr;
	}
	size_t fracMembsCount = 0;
	auto it = GroupSelectionSystem::GetSelectedEnts_Begin();
	auto end = GroupSelectionSystem::GetSelectedEnts_End();
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
			mem->SetFraction(*frac);
	}
	return true;
}

bool ConsoleCommsInterpretator::InterpretateComm_Print(const vector<string>& syntax) {
	
	if (syntax.size() < 2 ||
		syntax.at(0) != PRINT_COMMAND) {
		
		return false;
	}
	
	auto interParam = PrintComm_TryInterpetateParameter(syntax);
	PrintInterpetatorMessage("Print-command: " + (interParam == nullptr ? syntax[1] : *interParam));
	return true;
}
string* ConsoleCommsInterpretator::PrintComm_TryInterpetateParameter(const vector<string>& splitInput) {

	auto& param = splitInput[1];
	if (param == PRINT_PARAM_CAMERAPOS) {
		return &to_string(Engine::GetCameraPos());
	}
	
	return nullptr;
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