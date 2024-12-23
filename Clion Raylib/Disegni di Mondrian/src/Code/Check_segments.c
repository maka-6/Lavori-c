/*
    * Nome: check mondrian
    * Autore: Youness Makaoui
    * Luogo: Home
    * Data: 20/03/2024
    * Descrizione:
        - verifica i segmenti del quadro
*/

#include "Geometry.h"

//void freeTree(Tree *root);

MondrianSegments separateSegments(Mondrian *segments){
    MondrianSegments separate = {0}; // Inizializza tutti i puntatori a NULL
    separate.vertical.count = 0;
    separate.horizontal.count = 0;
    separate.horizontal.start = (struct Dot*) malloc((segments->nSeg / 2 + 1) * sizeof(struct Dot));
    separate.horizontal.end = (struct Dot*) malloc((segments->nSeg / 2 + 1) * sizeof(struct Dot));
    separate.vertical.start = (struct Dot*) malloc((segments->nSeg / 2 + 1) * sizeof(struct Dot));
    separate.vertical.end = (struct Dot*) malloc((segments->nSeg / 2 + 1) * sizeof(struct Dot));

    // Controlla allocazioni
    if (!separate.horizontal.start || !separate.horizontal.end ||
        !separate.vertical.start || !separate.vertical.end) {
        printf("Errore: memoria insufficiente per separare i segmenti.\n");

        // Libera la memoria già allocata
        free(separate.horizontal.start);
        free(separate.horizontal.end);
        free(separate.vertical.start);
        free(separate.vertical.end);
        exit(1); // Termina con errore
    }
    int i;
    for (i = 0; i < segments->nSeg; ++i) {
        if ( segments->A[i].x == segments->B[i].x ){
            separate.horizontal.start[separate.horizontal.count] = segments->A[i];
            separate.horizontal.end[separate.horizontal.count] = segments->B[i];
            separate.horizontal.count++;

        } else if ( segments->A[i].y == segments->B[i].y ){
            separate.vertical.start[separate.vertical.count] = segments->A[i];
            separate.vertical.end[separate.vertical.count] = segments->B[i];
            separate.vertical.count++;
        }
    }
    return separate;
}

// Prototipo della funzione per trovare o costruire un segmento principale
Segment MainSegmentBuild(SegmentList segmentList, int squareSide, int isHorizontal ){
    Segment mainSegment = {0};
    int i, j;
    // Array per tracciare i segmenti usati
    bool *used = malloc(segmentList.count * sizeof(bool));

    for (i = 0; i < segmentList.count; ++i) {
        used[i] = false;
    }

    // Cerca il segmento principale se gia presente intero
    for (i = 0; i < segmentList.count; ++i) {
        if (distance(segmentList.start[i], segmentList.end[i]) == squareSide) {
            mainSegment.A = segmentList.start[i];
            mainSegment.B = segmentList.end[i];
            used[i] = true;
            free(used);
            return mainSegment; // Segmento trovato
        }
    }

    struct Dot start;
    struct Dot end;
    // Altrimenti costruisci il segmento principale con i segmenti piccoli
    for (i = 0; i < segmentList.count; ++i) {
        start = segmentList.start[i];
        end = segmentList.end[i];

        // Confronta con gli altri segmenti
        for (j = 0; j < segmentList.count; ++j) {
            if (i != j) {
                // Controlla contiguità (orizzontale o verticale)
                if (isHorizontal && end.x == segmentList.start[j].x && end.y == segmentList.start[j].y) {
                    end = segmentList.end[j];
                    j = -1; // Ricomincia il ciclo per verificare nuove estensioni
                } else if (end.y == segmentList.start[j].y && end.x == segmentList.start[j].x) {
                    end = segmentList.end[j];
                    j = -1; // Ricomincia il ciclo per verificare nuove estensioni
                }
            }
        }

        // Verifica se il segmento costruito è valido
        if (distance(start, end) == squareSide) {
            mainSegment.A = start;
            mainSegment.B = end;
            //debug
            printf("\n x%d y%d",mainSegment.A.x, mainSegment.A.y);
            printf("\n x%d y%d",mainSegment.B.x, mainSegment.B.y);
            free(used);
            return mainSegment;
        }
    }
    free(used);
    printf("\nQuadro fasullo");
    exit(1); // Termina con errore
}

int checkSeg( Mondrian *segments ){

    MondrianSegments separate = separateSegments(segments);
    Segment mainHorizontal;
    Segment mainVertical;
    //Tree *root;

    // Trova o costruisci il segmento orizzontale principale
    mainHorizontal = MainSegmentBuild(separate.horizontal, segments->lSquare, 1);
    // Trova o costruisci il segmento verticale principale
    mainVertical = MainSegmentBuild(separate.vertical, segments->lSquare, 0);

    // costruisco l'albero
    //root = (Tree*) malloc(sizeof(Tree));

    // Libera la memoria allocata
    //freeTree(root);
    free(separate.vertical.start);
    free(separate.vertical.end);
    free(separate.horizontal.start);
    free(separate.horizontal.end);
    return 1;
}