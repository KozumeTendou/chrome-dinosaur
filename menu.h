/**La direttiva #ifndef ( o #if !defined ) controlla se un simbolo è stato dichiarato con la direttiva #define in fase di pre-processione del codice. La direttiva è la contrazione di IF Not DEFine.*/
#ifndef MENU_H
#define MENU_H

///struct = struttura, viene dichiarata la lunghezza delle informazioni che l'utente inserirà
struct user {
	char name[20];
	char lastName[20];
	char age[3];
};

void startMenu();
void endGame(int score, int highScore, int diY, int diX, struct user firstUser);

#endif
