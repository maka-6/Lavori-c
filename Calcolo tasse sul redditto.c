//
// Created by makao on 18/10/2023.
//

#include <stdio.h>
#include <stdlib.h>

int main(){

    float redditto;
    scanf("%f",&redditto);

    if ( redditto >= 10000 ) {

        redditto-= 10000;
        printf("\nTasse: 15% \nRedditto - Tasse: %0.2f", redditto*( 1 - 0.1 ));

        if ( redditto >= 25000 ) {

            redditto-=25000;
            printf("\nTasse: 35% \nRedditto - Tasse: %0.2f", redditto*( 1 - 0.35 ));

            if ( redditto >= 40000 ) {

                redditto -= 40000;
                printf("\nTasse: 40% \nRedditto - Tasse: %0.2f", redditto * (1 - 0.4));
            }
        }

        printf("\nRedditto: %0.2f",redditto);

    } else {

        printf("\nRedditto: %0.2f\nTasse: 0% \nRedditto - Tasse: %0.2f",redditto, redditto );
    }

    exit (0);
}