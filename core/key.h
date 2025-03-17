#ifndef K
#define K
#include <string>
#include <vector>

using namespace std;

struct Key{
	Key();
	Note mainTone; // Тоника
	string lad;      // Мажорный(d), минорный(m), фригийский(f) и прочие.
	char mod;      // Натуральный(n), гармонический (g), мелодический (m), хроматический (h).
	
	int dTones[7] = {2,2,1,2,2,2}; // Мажорный (ионийский)
	int oTones[7] = {2,1,2,2,2,1}; // Дорийский
	int fTones[7] = {1,2,2,2,1,2}; // Фригийский
	int lTones[7] = {2,2,2,1,2,2}; // Лидийский
	int iTones[7] = {2,2,1,2,2,1}; // Миксолидийский
	int mTones[7] = {2,1,2,2,1,2}; // Минорный (эолийский)
	int kTones[7] = {1,2,2,1,2,2}; // Локрийский

	void change(string);

	Scale getScale(bool);                  // 0 - нисходящее движение, 1 - восходящее.
	Interval getInterval(int, int, bool);  // номера первой и вотрой ступени и направление движения
	int whereIs(Note);
	int whereIs(Interval);
	int whereIs(Accord);
};

#endif // K
