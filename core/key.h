#ifndef K
#define K

#include <vector>

using namespace std;

struct Key{
	Key();
	Note mainTone; // Тоника
	char lad;      // Мажорный(d), минорный(m), фригийский(f) и прочие.
	char mod;      // Натуральный(n), гармонический (g), мелодический (m), хроматический (h).
	
	int hTones[11] = {1,1,1,1,1,1,1,1,1,1,1};
	int dTones[7] = {2,2,1,2,2,2};
	int mTones[7] = {2,1,2,2,1,2};

	Scale getScale(bool);                  // 0 - нисходящее движение, 1 - восходящее.


	Interval getInterval(int, int, bool);  // номера первой и вотрой ступени и направление движения
	Interval getInterval(int, int);


	int whereIs(Note);

	int whereIs(Interval);
    
	int whereIs(Accord);
};

#endif // K
