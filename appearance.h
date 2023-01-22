/**La direttiva #ifndef ( o #if !defined ) controlla se un simbolo è stato dichiarato con la direttiva #define in fase di preprocessione del codice. La direttiva è la contrazione di IF Not DEFine.*/
#ifndef APPEARANCE_H
#define APPEARANCE_H

///Vengono dichiarate le procedure con variabili X e Y a tipologia intera. Utilizzate nel file appearance.c per la visione sullo schermo dei componenti del gioco, specificando le coordinate.
void dinosaur1(int y, int x);
void dinosaur2(int y, int x);
void cactus1(int y, int x);
void cactus2(int y, int x);
void sun(int y, int x);
void moon(int y, int x);
void showLoss(int y, int x);
void showTrex(int x, int y);
void clearCactus1(int y, int x);
void cleardinosaurDown(int diY, int diX);
void cleardinosaurUp(int diY, int diX);

#endif
