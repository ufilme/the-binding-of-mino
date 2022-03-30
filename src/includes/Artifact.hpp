/*
    TYPE
        - ALL       0
        - HEALTH    1
        - POWER     2
        - SPEED     3
    BIO
        - story
        - owner
    increment
        -1          max
        k           quel che l'è
*/
#include <string>
using namespace std;

class Artifact{
    protected:
        int type;
        int increment;
        int duration;
        string story;
        string owner;
    public:
        int _getType();
        int _getIncrement();
        int _getDuration();
        string _getStory();
        string _getOwner();
};

//storia del caffe, memino di claudio
class Kaffe: public Artifact{
    public:
        Kaffe();
};

//Sacra la pausa
class Pause: public Artifact{
    public:
        Pause();
};

//storia Amir
//aumenta il danno. all'inizio sei una pippa
class NAND: public Artifact{
    public:
        NAND();
};

class CFU: public Artifact{
    public:
        CFU();
};

class Kebab: public Artifact{
    public:
        Kebab();
};