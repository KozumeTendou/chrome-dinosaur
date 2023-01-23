/**ncurses = è una libreria di funzioni software che gestisce il display di un'applicazione su un
terminale a caratteri.*/
#include <ncurses.h>
///unistd = è il file header che consente l'accesso alle API dello standard POSIX
#include <unistd.h>
/**time = è l’header file ‘standard’ di C che fornisce un accesso standardizzato alle funzioni di
acquisizione e manipolazione del tempo.*/
#include <time.h>
/**stdlib = è l'header file che, all'interno della libreria standard del C, dichiara funzioni e costanti di utilità generale: allocazione della memoria, controllo dei processi, e altre funzioni
generali comprendenti anche i tipi di dato.*/
#include <stdlib.h>
///Librerie contenenti le procedure per il funzionamento del gioco
#include "menu.h"
#include "game.h"
#include "appearance.h"


void startMenu() {
	struct user firstUser;
	int highScore;
    ///Legge il punteggio massimo dal file hightScore.txt e viene salvato nella variabile highScoreFile
	FILE *highScoreFile;
	highScoreFile = fopen("./highScore.txt", "r");
	///fscanf = serve a leggere da un file in modo formattato, chiaramente dopo l’apertura con fopen.
	fscanf(highScoreFile, "%d", &highScore);
	///fclose = serve a chiudere un file dopo averlo utilizzato.
	fclose(highScoreFile);
	int maxX = getmaxx(stdscr)/2;
	int maxY = getmaxy(stdscr)/2;
	/**init_pair = Modifica la definizione di una coppia di colori. Richiede tre argomenti: il numero della coppia di colori da modificare, il numero del colore di primo piano e il numero del colore di sfondo.*/
	init_pair(3,COLOR_GREEN,COLOR_BLACK);
///attron = Attiva gli attributi denominati "attrs" senza attivare o disattivare altri attributi.
	attron(COLOR_PAIR(3));
///Chiamata la procedura
	showTrex(maxY, maxX);
///attroff = Disattiva gli attributi con nome "attrs" senza influire sugli altri.
	attroff(COLOR_PAIR(3));
    ///Prende e mostra le informazioni date in input dall'utente
	mvprintw(maxY+1, maxX-28, "Write inputs and press Enter to start the Game.");
    mvprintw(maxY+2, maxX-26, "When you had prize, fire it with 'k' key!");
	mvprintw(maxY+3, maxX-21, "You can jump with space key!");
	mvprintw(maxY+4, maxX-15, "Name: ");
	getstr(firstUser.name);
	mvprintw(maxY+5, maxX-15, "Last name: ");
	getstr(firstUser.lastName);
	mvprintw(maxY+6, maxX-15, "Age: ");
	getstr(firstUser.age);
	///noecho = Disabilita l'eco dei caratteri digitati dall'utente da parte di Curses.getch mentre vengono digitati.
	noecho();
	startEngine(highScore, firstUser);
}

void endGame(int score, int highScore, int diY, int diX, struct user firstUser) {
	nodelay(stdscr, FALSE);
	init_pair(2,COLOR_RED,COLOR_BLACK);
    ///Salva il punteggio confrontandolo con quello massimo stabilito nel file hightScore
	if (score > highScore) {
		highScore = score;
		FILE *highScoreFile;
		highScoreFile = fopen("./highScore.txt", "w");
		fprintf(highScoreFile, "%d", highScore);
		fclose(highScoreFile);
	}
	int maxX = getmaxx(stdscr)/2;
	int maxY = getmaxy(stdscr)/2;
///attron = Attiva gli attributi denominati "attrs" senza attivare o disattivare altri attributi.
	attron(COLOR_PAIR(2));
	///Viene chiamata la procedura showLoss e sullo sfondo viene cambiato l'aspetto del dinosauro
	showLoss(maxY, maxX);
	mvprintw(diY-4, diX, "          X-X ");
	mvprintw(diY, diX, "      ||");
	char keyToExit = getch();
    ///Uscire o continuare. Se viene premuto il tasto "r" il gioco ricomincia, se si preme il tasto "q" finisce il gioco e vengono mostrati i risultati
	if (keyToExit == 'r') {
		attroff(COLOR_PAIR(2));
		startEngine(highScore, firstUser);
	}
	else if (keyToExit == 'q') {
		return;
	}
	else {
		endGame(score, highScore, diY, diX, firstUser);
	}
}
