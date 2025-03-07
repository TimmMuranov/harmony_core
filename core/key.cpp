#include "key.h"

using namespace std;

Key::Key(){
    	Note n;
    	mainTone = n;
	lad = 'd';
	mod = 'n';
}

Scale Key::getScale(){
	Scale answer;
	
	int* l;
	if(lad == 'd') {
		l = dTones;
	} else if (lad == 'm'){
	       	l = mTones;
	} else {
		l = dTones;
	}

	answer.noteScale.push_back(mainTone);
	Note n;
        for(int x=0; x<6; ++x){
		n = mainTone;
		n.name += x;
		if(n.name > 'g'){
			n.name = 'a';
		}
		n.sygn = 0;

		if(n.getHeight() - answer.noteScale[x-1].getHeight() < l[x-1]){
			++answer.noteScale[x].sygn;
			if(n.getHeight() - answer.noteScale[x-1].getHeight() < l[x-1]){
				++answer.noteScale[x].sygn;
			}
		}
		if(n.getHeight() - answer.noteScale[x-1].getHeight() > l[x-1]){
			--answer.noteScale[x].sygn;
			if(n.getHeight() - answer.noteScale[x-1].getHeight() > l[x-1]){
				--answer.noteScale[x].sygn;
			}
		}
	}
	

    	if(mod == 'g'){
		Note nextNote = answer.noteScale[0];
		++n.octave;
		if(nextNote.getHeight() - answer.noteScale[6].getHeight() >= 2){
			++answer.noteScale[6].sygn;
		}
		if(answer.noteScale[5].getHeight() - answer.noteScale[6].getHeight() < 3){
			--answer.noteScale[5].sygn;
		}
    	}

    	if(mod == 'm'){
		Note nextNote = answer.noteScale[0];
		++n.octave;
		if(nextNote.getHeight() - answer.noteScale[6].getHeight() >= 2){
			++answer.noteScale[6].sygn;
		}
		if(answer.noteScale[6].getHeight() - answer.noteScale[5].getHeight() > 2){
			++answer.noteScale[5].sygn;
		} else if(answer.noteScale[6].getHeight() - answer.noteScale[5].getHeight() < 2){
			--answer.noteScale[5].sygn;
		}
    	}

    	if(mod == 'h'){
		answer.noteScale.clear();
		answer.noteScale.push_back(mainTone);
	}
    	//как же в падло....

    	return answer;
}


Interval Key::getInterval(int n1, int n2){
	Interval answer;
    if(mod != 'n' || mod != 'm' || mod != 'g' || mod != 'h') return answer;
    if(mod == 'h'){
	if(n1 > 12 || n1 < 1) return answer;
	if(n2 > 12 || n2 < 1) return answer;
    } else {
	if(n1 > 7 || n2 < 1) return answer;
	if(n2 > 7 || n2 < 1) return answer;
    }

    Scale s = getScale();

    answer.parts[0] = s.noteScale[n1];
    answer.parts[1] = s.noteScale[n2];

    return answer;
}

int Key::whereIs(Note n){
	int answer;

	return answer;
}

int Key::whereIs(Interval i){
	int answer;

	return answer;
}

int Key::whereIs(Accord a){
	int answer;

	return answer;
}
