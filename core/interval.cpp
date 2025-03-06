#include "note.h"
#include "interval.h"

using namespace std;

Interval::Interval(){
    Note n;
    parts[0] = n;
    parts[1] = n;
}

int Interval::getDistance(){
    if(parts[1].getHeight() - parts[0].getHeight() >= 0){
        return parts[1].getHeight() - parts[0].getHeight();
    }
    return parts[0].getHeight() - parts[1].getHeight();
}
