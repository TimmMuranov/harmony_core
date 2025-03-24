#include "headers.h"

using namespace std;

Note::Note() {
    name = 'a';
    octave = 5;
    sygn = 0;
}

void Note::enharmonyChange(bool dir){
    int noteHeight = getHeight();
    Note n;
    n.name = name;
    n.octave = octave;
    n.sygn = sygn;
    if(dir){
        ++name;
        if(name > 'g'){
            name = 'a';
            ++octave;
        }
        while(getHeight() != noteHeight){
            --sygn;
        }
    } else {
        --name;
        if(name < 'a'){
            name = 'g';
            --octave;
            if(octave < 0){
                name = 'a';
                octave = 1;
                sygn = 0;
                return;
            }
        }
        while(getHeight() != noteHeight){
            ++sygn;
        }
    }
    if(sygn > 2 || sygn < -2){
	    name = n.name;
	    octave = n.octave;
	    sygn = n.sygn;
    }
}

int Note::getHeight(){
    int answer = (octave - 1) * 12;
    char test = 'a';
    for(int x=0; x<7; ++x){
        if(test == name) {
            break;
        }
        if(test == 'b' || test == 'e'){
            ++answer;
        } else {
            answer += 2;
        }
        ++test;
    }
    return answer + sygn;
}

void Note::change(string n){
	if(n[0] > 'g' || n[0] < 'a') return;
	name = n[0];
	if(n.length() == 1){
        	sygn = 0;
        	return;
	}
	if(n[0] == 'a' || n[0] == 'e'){
		if(n.length() > 2){
			n = n[0] + n.substr(2);
		}
		--sygn;
	}
	for(int x=1; x< n.length(); x+=2){
        	if(n.substr(x, 2) == "is") ++sygn;
        	if(n.substr(x, 2) == "es") --sygn;
	}
}

string Note::getName(){
	string answer;
	answer += name;
	int s = sygn;
	while(s != 0){
        if(s > 0){
            --s;
            answer += "is";
        }
        if(s < 0){
            ++s;
            answer += "es";
        }
	}
	if((name == 'a' || name == 'e') && answer[1] == 'e'){
	    answer = answer[0] + answer.substr(2);
	}
	return answer;
}
