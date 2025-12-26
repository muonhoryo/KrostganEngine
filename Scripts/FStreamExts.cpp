
#include <string>
#include <FStreamExts.h>
#include <fstream>

using namespace KrostganEngine;
using namespace std;
using namespace sf;

void FStreamExts::ClearPath(string& path) {

	if (path.size() <= 1)
		return;

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
	nextIndex = count;
	while (nextIndex > index) {
		--nextIndex;
		sym = path[nextIndex];
		if (sym == ' ')
			--count;
		else 
			break;
	}
	if (index >= 0) {
		path = path.substr(index + 1, count - index - 1);
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
char FStreamExts::SFKeyToChar(Keyboard::Key key) {
	if (key >= Keyboard::Key::A && key <= Keyboard::Key::Z)
		return (char)key + 97;
	else if (key >= Keyboard::Key::Num0 && key <= Keyboard::Key::Num9)
		return (char)key + 22;
	else if (key == Keyboard::Key::Space)
		return ' ';
	else if (key == Keyboard::Key::Add || key == Keyboard::Key::Equal)
		return '+';
	else if (key == Keyboard::Key::Subtract || key == Keyboard::Key::Hyphen)
		return '-';
	else if (key == Keyboard::Key::Period)
		return '.';
	else
		return (char)key;
}
void FStreamExts::ToLowerStr(string& str) {
	for (auto it = str.begin();it < str.end();++it) {
		(*it)=tolower(*it);
	}
}