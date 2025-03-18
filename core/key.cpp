#include "headers.h"

using namespace std;

Key::Key(){
    	Note n;
    	mainTone = n;
	lad = "dur";
	mod = 'n';
}

void Key::change(string n){
	if(n[0] <= 'G' && n[0] >= 'A'){
		lad = "dur";
		n[0] += 32;
	} else if (n[0] <= 'g' && n[0] >= 'a'){
		lad = "mol";
	} else return;

    mainTone.name = n[0];
    if(n[0] == 'a' || n[0] == 'e'){
	    if(n.length() > 2){
		    n.erase(1);
	    }
	    --mainTone.sygn;
    }
    if(n.length() == 1){
        mainTone.sygn = 0;
        return;
    }
    for(int x=1; x< n.length(); x+=2){
        if(n.substr(x, 2) == "is") ++mainTone.sygn;
        if(n.substr(x, 2) == "es") --mainTone.sygn;
    }
}

Scale Key::getScale(bool direction){
	Scale answer;
	Note n;
	vector<int> l;

	bool chronScale = 0;
//----------------------------------------------------	
	if(lad == "dur"){
		for(int x=0; x<7; ++x){
			l.push_back(dTones[x]);
		}
	}
	if(lad == "mol"){
		for(int x=0; x<7; ++x){
			l.push_back(mTones[x]);
		}
	}
	if(lad == "dor"){
		for(int x=0; x<7; ++x){
			l.push_back(oTones[x]);
		}
	}
	if(lad == "frg"){
		for(int x=0; x<7; ++x){
			l.push_back(fTones[x]);
		}
	}
	if(lad == "lid"){
		for(int x=0; x<7; ++x){
			l.push_back(lTones[x]);
		}
	}
	if(lad == "mks"){
		for(int x=0; x<7; ++x){
			l.push_back(mTones[x]);
		}
	}
	if(lad == "lks"){
		for(int x=0; x<7; ++x){
			l.push_back(kTones[x]);
		}
	}

	if(mod == 'g'){
		l[4] = 1;
		l[5] = 3;
	}
	if(mod == 'm'){
		l[4] = 2;
		l[5] = 2;
	}

//-----------------------------------------------------
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
		int t = answer.noteScale.size() - 1;
		for(int x=0; x<t; ++x){
			if(answer.noteScale[x+1].getHeight() - answer.noteScale[x].getHeight() == 2){
				n = answer.noteScale[x];
				++n.sygn;
				auto iter = answer.noteScale.cbegin();
				answer.noteScale.emplace(iter + (x+1), n);
				++t;
				++x;
			}
		}
		if(lad == "dur"){
			answer.noteScale[10].enharmonyChange(1);
		} else if(lad == "mol"){
			answer.noteScale[1].enharmonyChange(1);
		}
	}

	if(!direction){
		if(mod == 'n' || mod == 'g' || mod == 'm'){
			for(int x=0; x<3; ++x){
				n = answer.noteScale[x];
				++n.octave;
				answer.noteScale[x] = answer.noteScale[6-x];
				answer.noteScale[6-x] = n;
			}
			answer.noteScale.insert(answer.noteScale.begin(), answer.noteScale[6]);
			answer.noteScale.pop_back();

			if(mod == 'm'){
				--answer.noteScale[1].sygn;
				--answer.noteScale[2].sygn;
			}
		}
		if(mod == 'h'){
		}
	}
    return answer;
	//Исправить нисходящее движение хроматической гаммы
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
