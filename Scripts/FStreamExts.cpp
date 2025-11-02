
#include <string>
#include <FStreamExts.h>
#include <fstream>

using namespace KrostganEngine;
using namespace std;

void FStreamExts::ClearPath(string& path) {
	long long index = -1;
	long long nextIndex = -1;
	long long count = path.size();
	char sym;
	while (nextIndex < count) {
		++nextIndex;
		sym = path[nextIndex];
		if (sym == ' ')
			++index;
		else
			break;
	}
	if (index >= 0) {
		path.erase(0, index + 1);
	}
}
char* FStreamExts::ReadToEnd(const string& path) {

	ifstream st;
	st = ifstream(path,ios::binary|ios::ate);
	if (st.bad() == true ||
		st.fail() == true) {
		throw exception("Cannot open file");
	}
	size_t size = st.tellg();
	char* text = new char[size];
	st.seekg(0);
	st.read(text, size);
	st.close();
	text[size] = '\0';
	return text;
}
bool FStreamExts::ParseBool(const string& servalue) {
	string value = string(servalue);
	ClearPath(value);
	return value == "1";
}