#include <iostream>
#include "core/core.h"

using namespace std;

int main(){
    Note note;
    Interval interval;
    Accord accord;
    Scale scale;
    Polyphony pol;

    note.name = 'c';
    cout << note.name << endl;

    interval.parts[0].name = 'c';

    cout << interval.getDistance() << endl;
}
