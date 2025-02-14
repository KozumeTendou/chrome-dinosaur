/**ncurses = è una libreria di funzioni software che gestisce il display di un'applicazione su un terminale a caratteri.*/
///unist = è una libreria che consente l'accesso alle API dello standard POSIX
///time = è l’header file ‘standard’ di C che fornisce un accesso standardizzato alle funzioni di acquisizione e manipolazione del tempo.
/**stdlib = è l'header file che, all'interno della libreria standard del C, dichiara funzioni e costanti di utilità generale: allocazione della memoria, controllo dei processi, e altre funzioni generali comprendenti anche i tipi di dato.*/
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

///Vengono richiamate le librerie utlizzate, dove vengono specificate la procedure per il funzionamento del gioco
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

///Corpo del gioco dichiarato nel file game.h
void startEngine(int highScore, struct user firstUser) {
    srand(time(NULL));
	int x, y, diX=5, prize=0, usedPrize=0, score=0, delayTime = 300000
    , gameStatus=1, cactusNum=0;
    ///stdscr = Lo schermo standard. All'inizializzazione di curses, viene creata una finestra predefinita chiamata stdscr, che è la dimensione dello schermo del terminale.

	int maxX=getmaxx(stdscr);
	x = maxX-20;
	y = getmaxy(stdscr)-6;
	int diY = y;
	int arrowX=(diX+15), arrowY=(diY-3);
	char userInput;
	int jumping=-1;
    bool fire=FALSE;
    clear();
   /**nodelay = La funzione specifica se la modalità ritardo o la modalità senza ritardo è attiva per lo schermo associato alla finestra specificata. Se è TRUE, questa schermata è impostata su No Delay Mode. Se è FALSE, questa schermata è impostata su Delay Mode. Lo stato iniziale è FALSE.*/
	nodelay(stdscr, TRUE);
	///init_pair = Modifica la definizione di una coppia di colori. Richiede tre argomenti: il numero della coppia di colori da modificare, il numero del colore di primo piano e il numero del colore di sfondo.
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
				///La variabile fire viene cambiato in vero
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
		///Per pulizia dello schermo
		cleardinosaurUp(diY, diX);
		if (x <= 7) {
			x = getmaxx(stdscr)-20;
            cactusNum = rand() % 2;
		}
        ///Se l'input è uguale alla pressione della barra spaziatrice allora il dinosauro salta
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
        ///Riporta il dinosauro
		jumping--;
		if (jumping==0) {
			diY += 7;
		}
	///mvhline = disegna una linea che procede verso l'ultima colonna della stessa linea.
		mvhline(y+1, 1, '-', getmaxx(stdscr)-3);
        refresh();
        clearCactus1(y, x);
		refresh();
        usleep(delayTime);
        x -= 7;
        delayTime = computeTime(delayTime);
		userInput = 'q';
	}
///Finisce il gioco e vengono salvate le informazioni
	endGame(score, highScore, diY, diX, firstUser);
	attroff(COLOR_PAIR(1));
}


//
///INIZIO della sezione Test
//


///Variabili campione da testare
int foo = 4;
int bar = 5;


///Inizializzazione variabili test
int tests_run = 0;
int tests_passed = 0;

///Funzione di test del campione 1
static char * test_foo() {
    mu_assert("error, foo != 7", foo == 7);
}

///Funzione di test del campione 2
static char * test_bar() {
    mu_assert("error, bar != 5", bar == 5);
}

void test_checkGame()
{
   mu_assert("ERROR in function 1 checkGame, abs != 4", abs <= 4);
   mu_assert("ERROR in function 2 checkGame, abs != 3", abs < 4);
   mu_assert("ERROR in function 3 checkGame, abs != 2", abs < 4);
   mu_assert("ERROR in function 4 checkGame, abs != 1", abs < 4);
   mu_assert("ERROR in function 5 checkGame, abs != 5", abs <= 4);
   mu_assert("ERROR in function 6 checkGame, abs != 6", abs < 4);
   mu_assert("ERROR in function 7 checkGame, abs != -1", abs < 4);
   mu_assert("ERROR in function 8 checkGame, abs != 0", abs < 4);
   mu_assert("ERROR in function 9 checkGame, abs != 8", abs < 4);
   mu_assert("ERROR in function 10 checkGame, abs != 9", abs < 4);
}
void test_computeTime()
{
   mu_assert("ERROR in function 1 computeTime, delayTime != 250000", delayTime >= 250000);
   mu_assert("ERROR in function 2 computeTime, delayTime != 200000", delayTime >= 200000);
   mu_assert("ERROR in function 3 computeTime, delayTime != 1000", delayTime -= 1000);
   mu_assert("ERROR in function 4 computeTime, delayTime != 600", delayTime -= 600);
   mu_assert("ERROR in function 5 computeTime, delayTime != 200", delayTime -= 200);
   mu_assert("ERROR in function 6 computeTime, delayTime != 300", delayTime >= 300);
   mu_assert("ERROR in function 7 computeTime, delayTime != 400", delayTime >= 400);
   mu_assert("ERROR in function 8 computeTime, delayTime != 210000", delayTime >= 210000);
   mu_assert("ERROR in function 9 computeTime, delayTime != 230000", delayTime >= 230000);
   mu_assert("ERROR in function 10 computeTime, delayTime != 800", delayTime >= 800);
}
void test_computePrize()
{
   mu_assert("ERROR in function 1 computePrize, score != 20", score >= 20);
   mu_assert("ERROR in function 2 computePrize, score != 30", score == 30);
   mu_assert("ERROR in function 3 computePrize, score != 40", score <= 40);
   mu_assert("ERROR in function 4 computePrize, score != 60", score >= 60);
   mu_assert("ERROR in function 5 computePrize, score != 70", score == 70);
   mu_assert("ERROR in function 6 computePrize, score != 80", score <= 80);
   mu_assert("ERROR in function 7 computePrize, score != 100", score >= 100);
   mu_assert("ERROR in function 8 computePrize, score != 110", score == 110);
   mu_assert("ERROR in function 9 computePrize, score != 120", score <= 120);
}

///Mette tutti i test
void all_tests() {
	mu_run_test(test_foo);
	mu_run_test(test_bar);
	mu_run_test(test_checkGame);
	mu_run_test(test_computeTime);
	mu_run_test(test_computePrize);
}

///Esegue tutti i test
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
///FINE della sezione Test
//
