/**La direttiva #ifndef ( o #if !defined ) controlla se un simbolo è stato dichiarato con la direttiva #define in fase di pre-processione del codice. La direttiva è la contrazione di IF Not DEFine.*/
#ifndef GAME_H
#define GAME_H

/**Vengono dichiarate le procedure con variabili X e Y a tipologia intera per mostrare la posizione del dinosauro nel caso di "showdinosaur" è il punteggio e l'utente. Utilizzate nel file game.c per la visione sullo schermo dei componenti del gioco.*/
void startEngine(int highScore, struct user firstUser);
void showdinosaur(int diY, int diX);

#endif
