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
#include "Artifact.hpp"

int Artifact::_getType(){
    return this->type;
};
int Artifact::_getIncrement(){
    return this->increment;
};
int Artifact::_getDuration(){
    return this->duration;
};
string Artifact::_getStory(){
    return this->story;
};
string Artifact::_getOwner(){
    return this->owner;
};

//storia del caffe, memino di claudio
Kaffe::Kaffe(){
    this->owner = "Tutor";
    this->story = "";
    this->type = 3;
    this->increment = 1;
    this->duration = 30;
};

//Sacra la pausa
Pause::Pause(){
    this->owner = "Prof";
    this->story = "";
    this->type = 1;
    this->increment = 1;
    this->duration = -1;
};

//storia Amir
//aumenta il danno. all'inizio sei una pippa
NAND::NAND(){
    this->owner = "Tutor";
    this->story = "";
    this->type = 2;
    this->increment = 1;
    this->duration = 30;
};

CFU::CFU(){
    this->owner = "Unibo";
    this->story = "";
    this->type = 0;
    this->increment = -1;
    this->duration = 120;
};

Kebab::Kebab(){
    this->owner = "Franco";
    this->story = "";
    this->type = 1;
    this->increment = 3;
    this->duration = -1;
};