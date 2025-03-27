#include <iostream>
#include <string>
#include <ncurses.h>
#include "core/core.h"

using namespace std;

/////////////////////////////////////////////////////////////
Note note;
void testNote(){
	char command;
	cin >> command;
	if(command == 'r'){
		system("clear");
		testNote();
	} else if (command == 'q'){
		return;
	} else if(command == 'h'){
		cout << "'r' - restart console\n'c' - change note\n";
		cout << "'e' - enharmony change\n't' - tell notes parametres\n";
		cout << "'p' - prepared notes parameters\n'q' - quit\n";
		testNote();
	} else if(command == 'c'){
		cout << "enter new note name\n";
		string n;
		cin >> n;
		note.change(n);
		cout << "note changet to " << n << endl;
		testNote();
	} else if(command == 'e'){
		cout << "enter enharmony change direction\n";
		bool dir;
		cin >> dir;
		note.enharmonyChange(dir);
		cout << "enharmony change completed\n";
		testNote();
	} else if(command == 't'){
		cout << "note name: " << note.getName() << endl;
		cout << "---------------------" << endl;
		cout << "note height: " << note.getHeight() << endl;
		cout << "note name (obj): " << note.name << endl;
		cout << "note sygn: " << note.sygn << endl;
		cout << "note octave: " << note.octave << endl;
		testNote();
	} else if(command == 'p'){
		cout << "enter notes name, sygn and octave\n";
		char n;
		cin >> n;
		note.name = n;
		int t;
		cin >> t;
		note.sygn = t;
		cin >> t;
		note.octave = t;
		cout << "notes parametres changed\n";
		testNote();
	}
	else {
		cout << "unknown command...\n";
		testNote();
	}
}
//--------------------------------------------------------
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
//--------------------------------------------------------
void testScale(){
	Note n;
	cout << "scale test started..." << endl;
	cout << "enter note,s size and note names to included to the scale" << endl;
	Scale scale;
	int size;
	cin >> size;
	for (int x=0; x<size; ++x){
		scale.noteScale.push_back(n);
		string in;
		cin >> in;
		scale.noteScale[x].change(in);
	}
	cout << "Scale note names: ";
	for(int x=0; x<scale.noteScale.size(); ++x){
		cout << scale.noteScale[x].getName();
		if(x != scale.noteScale.size() - 1){
			cout << ", ";
		}
	}
	cout << endl;
}
//--------------------------------------------------------
void testKey(){
	Key key;
	cout << "key test started..." << endl;
	cout << "enter key name" << endl;
	string name;
	cin >> name;
	key.change(name);

	cout << "enter key lad (dor, frg, lid, mks, lks) or '-' to continiue" << endl;
	cin >> name;
	if((name != "-") && (name == "dor" || name == "frg" || name == "lid" || name == "mks" || name == "lks")){
		key.lad = name;
	}

	cout << "enter key specification: natural(n), garmony(g), melody(m) or chromatic (h)" << endl;
	char m;
	cin >> m;
	key.mod = m;

	cout << "key setting finished. Enter scale direction (0 - down, 1 - up)" << endl;
	bool dir;
	cin >> dir;
	Scale s = key.getScale(dir);
	int t = s.noteScale.size();

	cout << "key scale: ";
	for(int x=0; x<t; ++x){
		cout << s.noteScale[x].getName() << ' ';
	}
	cout << endl;
}
/////////////////////////////////////////////////////////////
void interface() {
    // Инициализация ncurses
    initscr();
    noecho();        // Отключаем эхо символов ввода
    cbreak();        // Включаем режим немедленного чтения символов
    keypad(stdscr, TRUE);   // Включение режима чтения функциональных клавиш

    int choice = 0;   // Индекс текущего выбора


//-------  Сюда добавить слово-идентификатор функции -------
    const char* options[] = {"Exit", "Note", "Interval", "Scale", "Key"};
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
				else if(choice == 4) testKey();
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
