#ifndef N
#define N

#include <string>

using namespace std;

struct Note{

public:
	Note();
/*
Значения ноты по умолчанию:
name - 'a'
sygn - 0
octave - 5
*/
//-----------------------------------------
	char name;
	int sygn;
	int octave;
// атрибуты ноты
//-----------------------------------------
	void enharmonyChange(bool); 
/* 0 - нисходящая замена, 1 - восходящая. 
Пример: 
Note n = {'a', 0, 1};
n.enharmonyChange(1);
cout << n.name; // beses
*/
//-----------------------------------------
	int getHeight(); 
/* Высота относительно ля суб контр октавы.
Пример:
Note n = {'a', 0, 1};
Note t = {a, 0, 2};
cout << n.getHeight(); // 0
cout << t.getHeight() // 14
*/
//-----------------------------------------
        string getName(); 
/* Возвращает имя в буквенной форме.
Пример:
Note n = {'a', -1, 5}
cout << n.getName(); // as
*/
        void change(string); 
/* Изменяет ноту по буквенному обозначению.
Пример: 
Note n;
n.change("fis"); // n == {'f', 1, 5}
*/
	int resolution(string, bool); 
/* Разрешает ноту в ближайшую устойчивую ноту указанной тональности вниз или вверх.
Пример:
Note n; // n == {'a', 0, 5};
n.resolution('C', 0); // n == {'g', 0, 4}
n.resolution('As', 1); // n == {'a', -1, 5}
*/
};

#endif
