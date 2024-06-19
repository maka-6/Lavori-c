/*
    * Nome: check mondrian
    * Autore: Youness Makaoui
    * Luogo: Home
    * Data: 20/03/2024
    * Descrizione:
        - controlla i segmenti del quadro
*/

//
typedef struct Payload{
    int num;
    Mondrian *value;
    struct Payload *left;
    struct Payload *right;
}Tree;

void checkSeg( Mondrian *segments ){
    Tree *mov;
    //
}