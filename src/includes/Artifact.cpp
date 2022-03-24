/*
    TYPE
        - ALL       0
        - HEALTH    1
        - POWER     2
        - SPEED     3
    BIO
        - story
        - owner
    
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
        int _getType(){
            return this->type;
        };
        int _getIncrement(){
            return this->increment;
        };
        int _getDuration(){
            return this->duration;
        }
        string _getStory(){
            return this->story;
        };
        string _getOwner(){
            return this->owner;
        };
};

//storia del caffe, memino di claudio
class Kaffe: public Artifact{
    public:
        Kaffe(){
            this->owner = "Tutor";
            this->story = "";
            this->type = 3;
            this->increment = 1;
            this->duration = 30;
        };
};

//Sacra la pausa
class Pause: public Artifact{
    public:
        Pause(){
            this->owner = "Prof";
            this->story = "";
            this->type = 1;
            this->increment = 1;
            this->duration = -1;
        };
};

//storia Amir
//aumenta il danno. all'inizio sei una pippa
class NAND: public Artifact{
    public:
        NAND(){
            this->owner = "Tutor";
            this->story = "";
            this->type = 2;
            this->increment = 1;
            this->duration = 30;
        };
};

class CFU: public Artifact{
    public:
        CFU(){
            this->owner = "Unibo";
            this->story = "";
            this->type = 0;
            this->increment = -1;
            this->duration = 120;
        };
};