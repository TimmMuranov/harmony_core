#include "note.h"

using namespace std;

Note::Note() {
    name = 'a';
    octave = 5;
    sygn = 0;
}

void Note::enharmonyChange(bool dir){
    int noteHeight = getHeight();
    if(dir){
        ++name;
        while(getHeight() != noteHeight){
            --sygn;
        }
    } else {
        --name;
        while(getHeight() != noteHeight){
            ++sygn;
        }
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

string Note::getName(char system){
	string answer;
	return answer;
}
