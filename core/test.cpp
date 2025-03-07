#include <iostream>
#include "core.h"

using namespace std;

int main(){
    Note note;
    Interval interval;
    Accord accord;
    Scale scale;
    Polyphony pol;
    Key key;
//---- Note test ------
cout << endl << "note test" << endl;
    
	note.name = 'c';
    	cout << note.name << endl;

//---- Interval test --
cout << endl << "Interval test" << endl;
    	
	interval.parts[0].name = 'c';
    	cout << interval.getDistance() << endl;

//--- Key test --------
cout << endl << "key test" << endl;

	note.name = 'c';
	note.sygn = 0;
	key.mainTone = note;
	key.lad = 'd';
	key.mod = 'n';

	scale = key.getScale();
	cout << "scale: ";
	for(int x=0; x<scale.noteScale.size(); ++x){
		cout << scale.noteScale[x].name;
	}	

	cout << "interval from 1 to 3 tones: " << key.getInterval(1,3).getDistance() << endl;
}
