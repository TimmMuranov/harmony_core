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

	void enharmonyChange(bool); // 0 - нисходящая замена, 1 - восходящая.
	int getHeight(); // Высота относительно ля суб контр октавы.
	string getName(); // Возвращает имя в буквенной форме.
	void change(string); // Изменяет ноту по буквенному обозначению.
	int resolution(string, bool); // Разрешает ноту в указанной тональности вниз или вверх.
};

#endif
