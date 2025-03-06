#ifndef N
#define N

using namespace std;

struct Note{

public:

    Note();

    char name;
    int sygn;
    int octave;

    void enharmonyChange(bool);

    int getHeight();

    int getInterval(Note);

    
};

#endif
