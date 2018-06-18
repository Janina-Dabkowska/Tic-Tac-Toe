
#include <stdlib.h>
#include "myclasses.h"
// Klasa planszy gry
//------------------

// Konstruktor planszy
//--------------------
 Board::Board(int w)
{
  // Ustalamy liczb� wierszy
  d = w;
  if(d < DMIN) d = DMIN;  // Je�li d nie mie�ci si� w zakresie,
  if(d > DMAX) d = DMAX;  // to je odpowiednio dopasowujemy


  // Tworzymy macierz p�l
  T = new Cell * [d];
  for(int i = 0; i < d; i++)
  {
    T[i] = new Cell [d];

    // Ka�d� kom�rk� pola inicjujemy

    for(int j = 0; j < d; j++)
    {
      T[i][j].player = 'n';
      T[i][j].change = false;
    }
  }
}

// Destruktor planszy
//-------------------
Board::~Board()
{
  for(int i = 0; i < d; i++) delete [] T[i]; // Usuwamy wiersze
  delete [] T;                               // Usuwamy tablic� wierszy
}

// Zwraca wymiar
//----------------------
int Board::DimCount()
{
  return d;
}

// Zwraca referencj� do kom�rki planszy
// rr - numer wiersza
// cc - numer kolumny
//-------------------------------------
Cell & Board::At(int rr,int cc)
{
  return T[rr][cc];
}


