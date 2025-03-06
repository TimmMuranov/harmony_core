#ifndef K
#define K

#include "headers.h"
#include <vector>

using namespace std;

struct Key{
	Key();
	Note mainTone; // Тоника
	char lad;      // Мажорный(d), минорный(m), фригийский(f) и прочие.
	char mod;      // Натуральный(n), гармонический (g), мелодический (m), хроматический (h).
	
	int hTones[11];
	int dTones[7];
	int mTones[7];

	Scale getScale();

	Interval getInterval(int, int, char);

	int whereIs(Note);

	int whereIs(Interval);
    
	int whereIs(Accord);
};

#endif // K
