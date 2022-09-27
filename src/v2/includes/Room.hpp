struct wall{
    int start;          //start == -1 -> ancora da inizializzare
    int end;            //start == -2 -> muro assente
    int axis;
    bool horizontal;
};

struct str_room{
    str_room* top;
    str_room* right;
    str_room* bottom;
    str_room* left;
    
    wall wall1;
    wall wall2;
    /*
    * info su muri, nemici, artefatti...
    */
    int difficulty;
};
typedef str_room* p_room;