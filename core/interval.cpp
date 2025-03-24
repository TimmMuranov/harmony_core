#include "headers.h"

using namespace std;

Interval::Interval(){
    Note n;
    low = n;
    high = n;
}

int Interval::getDistance(){
	return high.getHeight() - low.getHeight();
}
