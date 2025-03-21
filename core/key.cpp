#include "headers.h"
#include <iostream>

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
	Scale natAnswer = answer;
	Scale natAnswerRev = answer;
	if(mod == 'h'){
		int t = answer.noteScale.size();
		n = answer.noteScale[0];
		++n.octave;
		answer.noteScale.push_back(n);
		for(int x=0; x<t; ++x){
			if(answer.noteScale[x+1].getHeight() - answer.noteScale[x].getHeight() == 2){
				n = answer.noteScale[x];
				++n.sygn;
				if(!direction) n.enharmonyChange(1);
				auto iter = answer.noteScale.cbegin();
				answer.noteScale.emplace(iter + (x+1), n);
				++t;
				++x;
			}
		}
		answer.noteScale.pop_back();

		t = natAnswer.noteScale.size() + 7;
		for(int x=0; x<t; ++x){
			natAnswer.noteScale.push_back(natAnswer.noteScale[x]);
			++natAnswer.noteScale[7+x].octave;
		} //Прибавляем октаву, чтобы при поиске интервала не выходить за край вектора
		
		if(direction){
			for(int x=1; x<t; ++x){
				if((natAnswer.noteScale[x+4].getHeight() - natAnswer.noteScale[x].getHeight()) == 6){
					if((natAnswer.noteScale[x].getHeight() - natAnswer.noteScale[x-1].getHeight()) == 2){
						int n_num = answer.whereIs(natAnswer.noteScale[x]);
						answer.noteScale[n_num-1].enharmonyChange(1);
					}
				}
			}
		}
	}

	for(int x=0; x<3; ++x){
		n = natAnswerRev.noteScale[x];
		++n.octave;
		natAnswerRev.noteScale[x] = natAnswerRev.noteScale[6-x];
		natAnswerRev.noteScale[6-x] = n;
	}
	natAnswerRev.noteScale.insert(natAnswerRev.noteScale.begin(), natAnswerRev.noteScale[6]);
	natAnswerRev.noteScale.pop_back();
	//Инвертитуем натуральную гамму для поиска тритона в случае реверсивного движения гаммы

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
			++answer.noteScale[0].octave;
			for(int x=1; x<=5; ++x){
				n = answer.noteScale[x];
				answer.noteScale[x] = answer.noteScale[12-x];
				answer.noteScale[12-x] = n;
			}

			int t = natAnswerRev.noteScale.size() + 7;
			cout << endl;
			for(int x=1; x<t; ++x){
				cout << natAnswerRev.noteScale[x].getHeight() << ' ';
				if((natAnswerRev.noteScale[x+3].getHeight() - natAnswerRev.noteScale[x].getHeight()) == 6){
					if((natAnswerRev.noteScale[x].getHeight() - natAnswerRev.noteScale[x-1].getHeight()) == 2){
						int n_num = answer.whereIs(natAnswerRev.noteScale[x]);
						answer.noteScale[n_num-1].enharmonyChange(0);
					}
				}
			}//Некорректно работает реверс гаммы
			cout << endl;
		}
	}
//------------------ обработка хроматической гаммы ----------
//Добавить исключения в построение хроматической гаммы:
//При восходящей если на след. ноте нат. гаммы тритон вверх, текущая не повышается.
//При нисходящей если на след. ноте тритон вниз - текущая не понижается.
	return answer;
}

int Key::whereIs(Note n, int direction){
	int answer;
	Scale s = getScale(direction);
	int t = s.noteScale.size();
	for(int x=0; x<t; ++x){
		if(s.noteScale[x].name == n.name){
		       if(s.noteScale[x].sygn == n.sygn){
			       if(s.noteScale[x].octave == n.octave){
					return x + 1;
			       }
		       }
		}
	}
	return -1;
}

int Key::whereIs(Interval i, int direction){
	int answer;

	return answer;
}

int Key::whereIs(Accord a, int direction){
	int answer;

	return answer;
}
