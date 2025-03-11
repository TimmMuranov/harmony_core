#include "key.h"

using namespace std;

Key::Key(){
    	Note n;
    	mainTone = n;
	lad = 'd';
	mod = 'n';
}

Scale Key::getScale(bool direction){
	Scale answer;
	Note n;
	vector<int> l;

	bool chronScale = 0;
	
	if(lad == 'd'){
		for(int x=0; x<7; ++x){
			l.push_back(dTones[x]);
		}

		if(mod == 'g'){
			l[4] = 1;
			l[5] = 3;
		}
	}

	if(lad == 'm'){
		for(int x=0; x<7; ++x){
			l.push_back(mTones[x]);
		}
	
		if(mod == 'g'){
			l[4] = 1;
			l[5] = 3;
		}
		if(mod == 'm'){
			l[4] = 2;
			l[5] = 2;
		}
	}

	answer.noteScale.push_back(mainTone);
       	for(int x=1; x<l.size(); ++x){
		n = mainTone;
		n.name += x;
		if(n.name > 'g'){
			n.name -= 7;
			++n.octave;
		}
		n.sygn = 0;
		n.sygn = l[x-1] - (n.getHeight() - answer.noteScale[x-1].getHeight());
		answer.noteScale.push_back(n);
	}

	if(mod == 'h'){
		//Пройтись по всей гамме и включить между каждой большой секундой повышенный первый тон
		//В нужных местах энгармонически заменить	
	} 

	if(!direction){
		if(mod == 'n' || mod == 'g'){
			for(int x=0; x<3; ++x){
				n = answer.noteScale[x];
				++n.octave;
				answer.noteScale[x] = answer.noteScale[6-x];
				answer.noteScale[6-x] = n;
			}
			answer.noteScale.insert(answer.noteScale.begin(), answer.noteScale[6]);
			answer.noteScale.pop_back();
		}
		if(mod == 'm'){
		}
		if(mod == 'h'){
		}
	}

    	return answer;
}


Interval Key::getInterval(int n1, int n2, bool direction){
	Interval answer;
	Scale s = getScale(1);

	answer.low = s.noteScale[n1-1];
	answer.high = s.noteScale[n2-1];
	return answer;
}

int Key::whereIs(Note n){
	int answer;
	Scale s = getScale(1);

	for(int x=0; x<7; ++x){
		if(s.noteScale[x].name == n.name){
		       if(s.noteScale[x].sygn == n.sygn){
				return x + 1;
		       }
		}
	}
	return -1;
}

int Key::whereIs(Interval i){
	int answer;

	return answer;
}

int Key::whereIs(Accord a){
	int answer;

	return answer;
}
