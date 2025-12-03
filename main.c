#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
   // for PlaySound
#include <mmsystem.h>   

/* remove flicker */
void clear_screen_fast() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0, 0};
    SetConsoleCursorPosition(h, pos);
}

int main() {
	system("color 1F");
    PlaySound(TEXT("bg.wav"), NULL, SND_ASYNC | SND_LOOP);
    srand(time(0));
    int play = 1;

    while (play) {
        int playerLane = 1;             // 0,1,2
        int coinLane = rand() % 3;      // 0,1,2
        int coinStep = 0;               // vertical movement
        int score = 0;
        int lives = 3;
        int i;

        while (1) {
            // ---- INPUT ----
            if (_kbhit()) {
                char key = getch();
                if (key == 75 && playerLane > 0) playerLane--; // LEFT
                if (key == 77 && playerLane < 2) playerLane++; // RIGHT
            }

            // ---- DRAW ----
            clear_screen_fast();
            printf(" SCORE: %d   LIVES: %d\n", score, lives);
            printf("|--- --- ---|\n");

            for (i = 0; i < 10; i++) {
                if (i == coinStep) {
                    if (coinLane == 0){
                    	printf("| $         |\n");
					}
                    else if (coinLane == 1){
                    	printf("|     $     |\n");
					}
			       else{
                    	printf("|         $ |\n");
					} 
                } 
				else {
                    printf("|           |\n");
                }
            }

            // ---- PLAYER ----
            if (playerLane == 0) printf("| ^         |\n");
            else if (playerLane == 1) printf("|     ^     |\n");
            else printf("|         ^ |\n");

            // ---- CHECK COLLECTION ----
            if (coinStep == 9) {
                if (playerLane == coinLane) {
                    score += 10; // collected coin
                    //PlaySound(TEXT("coin.wav"), NULL, SND_ASYNC);
                } else {
                    lives--;     // missed coin
                    if (lives == 0) {
                    	PlaySound(TEXT("game.wav"), NULL, SND_ASYNC);
                        printf("\nGAME OVER!\nFINAL SCORE: %d\n", score);
                        break;
                    }
                }
                coinStep = 0;
                coinLane = rand() % 3;
            } else {
                coinStep++;
            }

            int speed = 150;       
            if (score >= 100){
            	speed = 80;
			}
            Sleep(speed);
        }

        // ---- REPLAY ----
        printf("\nDo you want to play again? (Y/N): ");
        char choice = getch();
        if (choice == 'Y' || choice == 'y'){
        	play = 1;
		}
        else { 
		   play = 0; 
		   printf("\nThanks for playing!\n"); }
    }

    return 0;
}

