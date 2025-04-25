#pragma once
#include <string>
#include <vector>

using namespace std;

namespace KrostganEngine::Core {
	class ValuesListDeserializer
	{
	protected:
		struct ValueDefPair {
			ValueDefPair(string Name, string Value) {
				this->Name = Name;
				this->Value = Value;
			}
			ValueDefPair():ValueDefPair("",""){}
			string Name;
			string Value;
		};

		ValuesListDeserializer();
		~ValuesListDeserializer();

		bool TryGetValue(const string& configName, string* Value);
		void DeserializeValues();

		vector<ValueDefPair> StrValuesArr;

		virtual const string GetFilePath() { return ""; }
		virtual const char GetValuesDefEndSym() { return ' '; }
	};
}