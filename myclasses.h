// Plik nag³ówkowy
//--------------------

#define DMIN 5     //minimalny rozmiar plaanszy
#define DMAX 20    // maksymalny rozmiar planszy
#define FSIZE 30 //rozmiar 1 pola planszy
#define SCOUNT 4 //liczba zaznaczonych krzyzykow lub kolek do wygrania


// Struktura komórki planszy
//--------------------------
struct Cell
{
  char player;
  bool change;
};

// Klasa planszy gry
//----------------------------
class Board
{
  protected:
    Cell ** T;    // Macierz dynamiczna
    int d;      // Liczba wierszy  i kolumn

  public:
    Board(int d); // Konstruktor
    ~Board();                    // Destruktor
    int DimCount();                  // Zwraca wymiar
    Cell & At(int rr,int cc);        // Zwraca referencjê do komórki
};


 