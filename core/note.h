#ifndef N
#define N

#include <string>

using namespace std;

struct Note{

public:
	Note();

	char name;
	int sygn;
	int octave;

	void enharmonyChange(bool);   // 0 - нисходящая замена, 1 - восходящая.
	int getHeight();              // Высота относительно ля 1 октавы
	string getName(char);  // Возвращает имя в слоговой русской системе (w) или в буквенной английской (l)
};

#endif
