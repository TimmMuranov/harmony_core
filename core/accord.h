#ifndef A
#define A

#include <vector>
#include "scale.h"
using namespace std;

struct Accord{
	Accord();

	vector<Note> notes;

	void addTone(Note);
	void rmTone(int);
	void buildKeyAccord(Note, char, int);
	Scale getArpeggio();
};

#endif // A
