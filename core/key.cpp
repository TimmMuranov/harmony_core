#include "headers.h"

using namespace std;

Key::Key(){
    	hTones = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    	dTones = {2, 2, 1, 2, 2, 2};
    	mTones = {2, 1, 2, 2, 1, 2};

    	Note n;
    	mainTone = n;
}

Scale Key::getScale(){
	Scale answer;
	
	int* lad;
	if(lad == 'd') {
		lad = dTones;
	} else if (lad == 'm'){
	       	lad = mTones;
	} else {
		return answer;
	}

	answer.noteScale.push_back(mainTone);

        for(int x=1; x<7; ++x){
		Note n = mainTone;
		n.name += x;
		if(n.name > 'g'){
			n.name = 'a';
		}
		n.sign = 0;

		if(n.getHeight() - answer.noteScale[x-1].getHeight() < lad[x-1]){
			++answer.noteScale[x].sign;
			if(n.getHeight() - answer.noteScale[x-1].getHeight() < lad[x-1]){
				++answer.noteScale[x].sign;
			}
		}
		if(n.getHeight() - answer.noteScale[x-1].getHeight() > lad[x-1]){
			--answer.noteScale[x].sign;
			if(n.getHeight() - answer.noteScale[x-1].getHeight() > lad[x-1]){
				--answer.noteScale[x].sign;
			}
		}
	}
	

    	if(mod == 'g'){
		Note nextNote = answer.noteScale[0];
		++n.octave;
		if(nextNote.getHeight() - answer.noteScale[6].getHeight() >= 2){
			++answer.noteScale[6].sign;
		if(answer.noteScale[5].getHeight() - answer.noteScale[6].getHeight() < 3){
			--answer.noteScale[5].sign;
		}
    	}

    	if(mod == 'm'){

    	}

    	if(mod == 'h'){
    	}
    	//как же в падло....

    	return answer;
}

Interval Key::getInterval(int n1, int n2, char md){
	Interval::Interval answer;
    if(md != 'n' || md != 'm' || md != 'g' || md != 'n') return answer;
    if(md == 'h'){
	if(n1 > 12 || n1 < 1) return answer;
	if(n2 > 12 || n2 < 1) return answer;
    } else {
	if(n1 > 7 || n2 < 1) return answer;
	if(n2 > 7 || n2 < 1) return answer;
    }

    Scale s = Key::getScale(md);

    interval.parts[0] = s.noteScale[n1];
    interval.parts[1] = s.noteScale[n2];
}

int Key::whereIs(Note n){
    
}

int Key::whereIs(Interval i){
    
}

int Key::whereIs(Accord a){
    
}
