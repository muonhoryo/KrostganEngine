
#include <string>
#include <FStreamExts.h>

using namespace KrostganEngine;
using namespace std;

void FStreamExts::ClearPath(string* path) {
	long long index = -1;
	long long nextIndex = -1;
	long long count = path->size();
	char sym;
	while (nextIndex < count) {
		++nextIndex;
		sym = (*path)[nextIndex];
		if (sym == ' ')
			++index;
		else
			break;
	}
	if (index >= 0) {
		path->erase(0, index + 1);
	}
}