#include <iostream>
#include <string>
#include <ncurses.h>
#include "core/core.h"

using namespace std;

void testNote(){
	Note note;
	cout << endl << "note test started..." << endl;
	cout << "Enter note name(a-g), sygn(-2 - 2) and octave (>=1)" << endl;
	cin >> note.name;
	cin >> note.sygn;
	cin >> note.octave;
	cout << "Note height: " << note.getHeight() << endl;
	
	cout << "Enter direction to enharmony change (1 - up, 0 - down) or any key to continiue\n";
	int flag;
	cin >> flag;
	if (flag == 0 || flag == 1) note.enharmonyChange(flag);
	cout << "name: " << note.name << ", sygn: " << note.sygn<<", octave: "<<note.octave<<endl;
	cout << "enter note name in word system" << endl;
	string name;
	cin >> name;
	note.changeNote(name);
	cout << "name: " << note.name << ", sygn: " << note.sygn<<", octave: "<<note.octave<<endl;
	cout << "full note name: " << note.getName() << endl;
}

void testInterval(){
	cout << endl << "Interval test started..." << endl;
	Interval interval;
	cout << "Enter First and second note,s name, sygn and octave" << endl;
	cin >> interval.low.name;
	cin >> interval.low.sygn;
	cin >> interval.low.octave;
	cin >> interval.high.name;
	cin >> interval.high.sygn;
	cin >> interval.high.octave;
	cout << "Distance: " << interval.getDistance() << endl;
}

void testScale(){
	Note n;
	cout << "scale test started..." << endl;
	cout << "enter note,s size and note names to included to the scale" << endl;
	Scale scale;
	int size;
	cin >> size;
	for (int x=0; x<size; ++x){
		scale.noteScale.push_back(n);
		char in;
		cin >> in;
		if(in > 'a' && in < 'g'){
			scale.noteScale[x].name = in;
		}
	}
	cout << "Scale note names: ";
	for(int x=0; x<scale.noteScale.size(); ++x){
		cout << scale.noteScale[x].name;
	}
	cout << endl;
}

////////////////////////////////////////////////////////////
void interface() {
    // Инициализация ncurses
    initscr();
    noecho();        // Отключаем эхо символов ввода
    cbreak();        // Включаем режим немедленного чтения символов
    keypad(stdscr, TRUE);   // Включение режима чтения функциональных клавиш

    int choice = 0;   // Индекс текущего выбора


//-------  Сюда добавить слово-идентификатор функции -------
    const char* options[] = {"Exit", "Note", "Interval", "Scale"};
//----------------------------------------------------------

    int num_options = sizeof(options) / sizeof(char*);

    while(true) {
        clear();      // Очищаем экран

        for(int i = 0; i < num_options; ++i) {
            if(i == choice)
                attron(A_STANDOUT);  // Подсвечиваем текущий выбор
            mvprintw(i + 1, 1, "%s", options[i]);
            attroff(A_STANDOUT);
        }

        refresh();    // Обновляем экран

        int c = getch();   // Читаем символ с клавиатуры

        switch(c) {
            case KEY_UP:
                choice = (choice > 0) ? choice - 1 : num_options - 1;
                break;
            case KEY_DOWN:
                choice = (choice + 1) % num_options;
                break;
            case '\n':   // Нажатие Enter
                endwin();     // Завершаем работу ncurses
                system("clear");  // Очищаем терминал



				if(choice == 0) return;
//-------  Сюда добавить функции тестирования  --------
				else if(choice == 1) testNote();
				else if(choice == 2) testInterval();
				else if(choice == 3) testScale();
//------------------------------------------------------

                return;
            default:
                continue;
        }
    }
    return;
}
/////////////////////////////////////////////////////////

int main(){
	interface();
}
