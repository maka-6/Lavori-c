/*
    * Nome: paint square
    * Autore: Youness Makaoui
    * Luogo: Home
    * Data: 20/03/2024
    * Descrizione:
        - disegna sulla finestra un quadro di Mondrian
*/

void squarePaint( int lSquare, struct Dot cent, Texture2D texture ){

    DrawTexture( texture, cent.x - (lSquare / 2) - 25, cent.y - 25, WHITE );
    DrawRectangle( cent.x  - (lSquare/2), cent.y, lSquare, lSquare, VIOLET );
    DrawRectangle( cent.x, cent.y, lSquare/2, lSquare, BLUE );
    DrawRectangle( cent.x - lSquare/2, cent.y + lSquare/2, lSquare, lSquare/2, RED );

}

// renderizza il quadro
void paint( int lSquare, struct Dot cent, Texture2D texture ){

    ClearBackground(LIGHTGRAY);
    DrawText( "Quadro di Piet Mondrian:",  cent.x / 2, cent.y - lSquare, 80, VIOLET);
    squarePaint( lSquare, cent, texture );

}