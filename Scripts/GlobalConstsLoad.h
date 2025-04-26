#pragma once

#include <vector>
#include <string>
#include <GlobalConsts.h>
#include <ValuesListDeserializer.h>

using namespace std;

namespace KrostganEngine::Core {
	class GlobalConstsLoad:public ValuesListDeserializer{
	public:
		GlobalConstsLoad();
		~GlobalConstsLoad(){}

		const GlobalConsts& LoadGlobalConsts();
		const GlobalConsts& GetLoadedConsts();
		
	private:
		GlobalConsts& LoadedGlobalConsts;

		const string GetFilePath() override;
		const char GetValuesDefEndSym() override;
		float DeserializeValueByDefinition(const string& definition, string* buffer);

		static const string CONSTS_PATH;
		static const char CONFIG_DEF_END_SYM;
	};
}