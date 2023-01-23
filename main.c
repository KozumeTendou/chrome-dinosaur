/// build with "gcc main.c game.c menu.c appearance.c -lncurses -o dino.exe"

/**ncurses = è una libreria di funzioni software che gestisce il display di un'applicazione su un
terminale a caratteri.*/
#include <ncurses.h>
/**stdio.h = sta per "standard input-output header", è l'header file della libreria standard del C che contiene definizioni di macro, costanti e dichiarazioni di funzioni e tipi usati per le varie operazioni di input/output. */
#include <stdio.h>
///Librerie contenenti le procedure per il funzionamento del gioco
#include "menu.h"
#include "minunit.h"

int main(int argc, char **argv) {
	///Esegue i test (se è stato specificato l'argomento del comando -test)
	int testsResult = run_all_tests(argc, argv);
	if(testsResult > 0)
		return testsResult != 0;

	///Inizio normale
	/**initscr = La funzione determina il tipo di terminale e inizializza tutte le strutture dati di implementazione. La variabile di ambiente specifica il tipo di terminale. La funzione initscr() fa anche in modo che la prima operazione di aggiornamento pulisca lo schermo.*/
	initscr();
	start_color();
	/**curs_set = Imposta la visibilità del cursore. 0: invisibile 1: visibile 2: molto visibile*/
	curs_set(FALSE);
	///Procedura contenuta nel file menu.c, mostra la schermata iniziale dove viene chiesto di inserire le proprie informazioni
	startMenu();
	endwin();

    return 0;
}
