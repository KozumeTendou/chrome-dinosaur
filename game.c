/**ncurses = è una libreria di funzioni software che gestisce il display di un'applicazione su un
terminale a caratteri.*/
#include <ncurses.h>
/**unist = è una libreria che consente l'accesso alle API dello standard POSIX*/
#include <unistd.h>
/**time = è l’header file ‘standard’ di C che fornisce un accesso standardizzato alle funzioni di
acquisizione e manipolazione del tempo.*/
#include <time.h>
/**stdlib = è l'header file che, all'interno della libreria standard del C, dichiara funzioni e costanti di utilità generale: allocazione della memoria, controllo dei processi, e altre funzioni
generali comprendenti anche i tipi di dato.*/
#include <stdlib.h>

/**Vengono richiamate le librerie urilizzate, dove vengono spegificate la procedure per il funzionamento del gioco*/
#include "menu.h"
#include "game.h"
#include "appearance.h"
#include "minunit.h"

///Funzione che controlla se il gioco sta per finire in questo giro di loop
int checkGame(int y, int x, int diY, int diX) {
	if (diY == y) {
		if (abs((diX+14)-x) <= 4) {
			return 0;
		}
	}
	return 1;
}

///Funzione che aumenta la velocità del gioco
int computeTime(int delayTime) {
	if (delayTime >= 250000) {
		delayTime -= 1000;
	}
	else if (delayTime >= 200000) {
		delayTime -= 600;
	}
	else {
		delayTime -= 200;
	}
	return delayTime;
}

///Procedura dichiarata nel file game.h che sceglie quale dinosauro deve essere stampato
void showdinosaur(int diY, int diX) {
	static int counter = 0;
	if (counter == 0) {
		dinosaur1(diY, diX);
		counter++;
	}
	else {
		dinosaur2(diY, diX);
		counter--;
	}
}

///Funzione che "dona" all'utente un premio
int computePrize(int score, int usedPrize) {
///Se il punteggio è maggiore uguale a 20 e minore uguale a 40 e il premio è stato usato restituisce 1
	if (score >= 20 && score <= 40 && usedPrize == 0) {
		return 1;
	}
///Se il punteggio è maggiore uguale a 60 e minore uguale a 80 e il premio è già presente ma non utilizzato restituisce 1
	else if (score >= 60 && score <= 80 && usedPrize <= 1) {
		return 1;
	}
///Se il punteggio è maggiore uguale a 100 e minore uguale a 120 e il premio è già presente ma non utilizzato restituisce 1
	else if (score >= 100 && score <= 120 && usedPrize <= 2) {
		return 1;
	}	
	return 0;
}

///Corpo del gioco dichiarato nella file game.h
void startEngine(int highScore, struct user firstUser) {
    srand(time(NULL));
	int x, y, diX=5, prize=0, usedPrize=0, score=0, delayTime = 300000
    , gameStatus=1, cactusNum=0;
	int maxX=getmaxx(stdscr);
	x = maxX-20;
	y = getmaxy(stdscr)-6;
	int diY = y;
	int arrowX=(diX+15), arrowY=(diY-3);
	char userInput;
	int jumping=-1;
    bool fire=FALSE;
    clear();
	nodelay(stdscr, TRUE);
  	init_pair(1,COLOR_WHITE,COLOR_BLACK);
	init_pair(4,COLOR_BLUE,COLOR_BLACK);
	init_pair(5,COLOR_GREEN,COLOR_BLACK);
	init_pair(6,COLOR_YELLOW,COLOR_BLACK);
	while (gameStatus == 1) {
		userInput = getch();
		///Mostra il cambiamento giorno a notte
		if((score/50)%2 != 0) {
			moon(10, (maxX/2)-10);
		}
		else {
			attron(COLOR_PAIR(1));
			sun(10, (maxX/2)-10);			
		}
		///Pulizia della freccia
		if (fire) {
			mvprintw(arrowY, arrowX-2, " ");
		}

		score++;
      	///Mostra informazioni utente, con nome, cognome ed età, punteggio massimo e punteggio ottenuto
		mvprintw(1, 6, "%s %s %s", firstUser.name, firstUser.lastName, firstUser.age);
		mvprintw(1, getmaxx(stdscr)-9, "%d:%d", highScore, score);
	///Utilizzo del premio per distruggere i cactus, la scritta prize richiama la funzione computePrize
		prize = computePrize(score, usedPrize);
		mvprintw(3, 6, "Prize: %d    ", prize);
		///Se il punteggio è 1 e l'utente preme il tasto "k" per sparare, viene mostrata la "freccia" e la pulizia del cactus. 
		if (prize == 1) {
			if (userInput == 'k') {
				usedPrize++;
				///Fire viene cambiato in vero
				fire = TRUE;
			}
		}
		if (fire) {
			mvprintw(arrowY, arrowX, "*");
			arrowX += 2;
		}
		if ((x+4)-arrowX <= 1 && fire) {
			clearCactus1(y, x-1);
			mvprintw(arrowY, arrowX-2, " ");
			x = getmaxx(stdscr)-20;
			///Fire ritorna a valore falso
			fire = FALSE;
			arrowX = diX+15;
		}
		// ----------
		box(stdscr, ACS_VLINE, ACS_HLINE);
		//for clearing screen
		cleardinosaurUp(diY, diX);
		if (x <= 7) {
			x = getmaxx(stdscr)-20;
            cactusNum = rand() % 2;
		}
        // if input is equal to ' ' then jump
		if (userInput == ' ' && jumping<0) {
			diY -= 7;
			jumping = 3;
		}
		showdinosaur(diY, diX);
		if (userInput == ' ') {
			cleardinosaurDown(diY, diX);		
		}
		if (x-diX <= 7) {
			x -= 10;
		}
        if (cactusNum == 0) {
        	cactus1(y, x);
		}
		else {
			cactus2(y, x);
		}
		if (x-diX <= 7) {
			x += 10;
		}
		gameStatus = checkGame(y, x, diY, diX);
        // Bring back dinosaur
		jumping--;
		if (jumping==0) {
			diY += 7;
		}
		mvhline(y+1, 1, '-', getmaxx(stdscr)-3);
        refresh();
        clearCactus1(y, x);
		refresh();
        usleep(delayTime);
        x -= 7;
        delayTime = computeTime(delayTime);
		userInput = 'q';
	}

	endGame(score, highScore, diY, diX, firstUser);
	attroff(COLOR_PAIR(1));
}


//
// START of tests section
//

// sample variables to be tested
int foo = 4;
int bar = 5;

// init tests vars
int tests_run = 0;
int tests_passed = 0;

// sample test function 1
static char * test_foo() {
    mu_assert("error, foo != 7", foo == 7);
}

// sample test function 2
static char * test_bar() {
    mu_assert("error, bar != 5", bar == 5);
}

// put all tests here
void all_tests() {
	mu_run_test(test_foo);
	mu_run_test(test_bar);
}

// call this to run all tests
int run_all_tests(int argc, char **argv) {
	if(argc<2 || strcmp(argv[1],"-test")!=0) {
		return -1;
	}
	
	printf("--- RUNNING TESTS ---\n");
    all_tests();
	printf("--- SUMMARY ---\n");
    printf("Total number of tests: %d\n", tests_run);
	printf("Tests passed: %d\n", tests_passed);
	return tests_run-tests_passed;
}
//
// END of tests section
//
