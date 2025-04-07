#ifndef N
#define N

#include <string>

using namespace std;

struct Note{

public:
	Note();
//-----------------------------------------
	char name;
	int sygn;
	int octave;
// атрибуты ноты
//-----------------------------------------
	void enharmonyChange(bool); 
/* 
0 - нисходящая замена, 1 - восходящая. 
Пример: 
Note n = {'a', 0, 1};
n.enharmonyChange(1);
cout << n.name; // beses
*/
//-----------------------------------------
	int getHeight(); 
/* 
Высота относительно ля суб контр октавы.
Пример:
Note n = {'a', 0, 1};
Note t = {a, 0, 2};
cout << n.getHeight(); // 0
cout << t.getHeight() // 14
*/
//-----------------------------------------
        string getName(); // Возвращает имя в буквенной форме.
	void change(string); // Изменяет ноту по буквенному обозначению.
	int resolution(string, bool); // Разрешает ноту в указанной тональности вниз или вверх.
};

#endif
