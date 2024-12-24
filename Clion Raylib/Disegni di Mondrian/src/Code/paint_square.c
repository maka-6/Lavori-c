/*
    * Nome: paint square
    * Autore: Youness Makaoui
    * Luogo: Home
    * Data: 20/03/2024
    * Descrizione:
        - disegna sulla finestra un quadro di Mondrian
*/

// disegna le forme all'interno del quadro
void squarePaint( Mondrian *paint, struct Dot cent, Texture2D texture ){
    DrawTexture( texture, cent.x - (280 / 2) - 25, cent.y - 25, WHITE );
    //DrawRectangle( cent.x  - (lSquare/2), cent.y, lSquare, lSquare, VIOLET );
    //DrawRectangle( cent.x, cent.y, lSquare/2, lSquare, BLUE );
    //DrawRectangle( cent.x - lSquare/2, cent.y + lSquare/2, lSquare, lSquare/2, RED );

    float scaleX = (float)280 / paint->lSquare;
    float scaleY = (float)280 / paint->lSquare;

    int offsetX = cent.x - 280 / 2;
    int offsetY = cent.y;

    for (int i = 0; i < paint->nSeg; i++) {
        int startX = (int)(offsetX + paint->A[i].x * scaleX);
        int startY = (int)(offsetY + paint->A[i].y * scaleY);
        int endX = (int)(offsetX + paint->B[i].x * scaleX);
        int endY = (int)(offsetY + paint->B[i].y * scaleY);

        // Disegna il segmento
        DrawLine(startX , startY, endX, endY, RAYWHITE);
    }
}

// renderizza il quadro
void draw( Mondrian *paint, struct Dot cent, Texture2D texture ){
    ClearBackground(LIGHTGRAY);
    DrawText( "Quadro di Piet Mondrian:",  cent.x / 2, cent.y - 280, ( cent.y * 2 ) / 13, VIOLET);
    squarePaint( paint, cent, texture );
}

//void horizontalDraw(int lSquare, struct Dot cent){}

//void verticalDraw(int lSquare, struct Dot cent){}