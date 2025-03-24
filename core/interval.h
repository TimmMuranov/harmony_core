#ifndef I
#define I

#include <map>
using namespace std;

struct Interval{
	Interval();

	Note high; // высокая нота интервала
	Note low; // низкая нота интервала
	
	int getDistance(); // получить расстояние между нотами
};

#endif //I
