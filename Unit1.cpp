//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include "myclasses.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmTicTac *frmTicTac;

Board * mboard = NULL;         // Plansza gry
bool Playing = false;          // Je�li gra si� toczy, to true
Graphics::TBitmap * bm = NULL; // Wska�nik bitmapy planszy
char Player='o';//kolko=1, krzyzyk=2
int w = 4;//ilosc pol do wygrania
//---------------------------------------------------------------------------
void DrawMBCell(int r,int c)
{
  int x = FSIZE * c ;               // Obliczamy wsp�rz�dne kom�rki na bitmapie
  int y = FSIZE * r;

  TRect cell(x,y,x+FSIZE,y+FSIZE); // Tworzymy prostok�t obejmuj�cy kom�rk�

  // W zale�no�ci od zawarto�ci kom�rki rysujemy r�ne tre�ci
  // w obr�bie prostok�ta kom�rki

    bm->Canvas->Brush->Color = clWhite;     // Tu rysujemy bia�e t�o
    bm->Canvas->FillRect(cell);

 if (mboard->At(r,c).player == 'o')
 {
     if (mboard->At(r,c).change)  bm->Canvas->Pen->Color = clRed;
     else bm->Canvas->Pen->Color = clGreen;
     bm->Canvas->Pen->Width = 3;
     bm->Canvas->Ellipse(x+2,y+2,x+FSIZE-2,y+FSIZE-2);
 }
   if (mboard->At(r,c).player =='x')
   {
       if (mboard->At(r,c).change)  bm->Canvas->Pen->Color = clRed;
       else bm->Canvas->Pen->Color = clBlue;
       bm->Canvas->Pen->Width = 3;
       bm->Canvas->MoveTo(x+2,y+2);
       bm->Canvas->LineTo(x+FSIZE-2,y+FSIZE-2);
       bm->Canvas->MoveTo(x+FSIZE-2,y+2);
       bm->Canvas->LineTo(x+2,y+FSIZE-2);
   }

   // Na koniec rysujemy kratk�
  bm->Canvas->Pen->Width = 1;
  bm->Canvas->Pen->Color = clMaroon;      // Kolor linii
  bm->Canvas->MoveTo(x,y);                // Punkt startowy
  bm->Canvas->LineTo(x+FSIZE-1,y);        // Linia pozioma
  bm->Canvas->LineTo(x+FSIZE-1,y+FSIZE);  // Linia pionowa
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void DrawMB()
{
  for(int i = 0; i < mboard->DimCount(); i++)
    for(int j = 0; j < mboard->DimCount(); j++)
      DrawMBCell(i,j);                      // Rysujemy kolejne kom�rki planszy
}
//---------------------------------------------------------------------------
bool Filled (Board  * myboard)
{ bool score=true;
 for(int i = 0; i < myboard->DimCount(); i++)
  {
    for(int j = 0; j < mboard->DimCount(); j++)
    {
      if(myboard->At(i,j).player == 'n') score=false;
    }
  }
 return score;
}
//---------------------------------------------------------------------------
 bool horizontalWin( int r, int c)
{  char mPlayer = mboard->At(r,c).player;
   bool score;
   int  indexLeft=c, indexRight=c;
   int signCount = 1;  //liczba kom�rek ze znakiem mPlayer
   int i=c+1;
     while( ( signCount<w)&&(i<mboard->DimCount())&&(mboard->At(r,i).player == mPlayer))  //sprawdzamy w wierszu po prawej
      {
         signCount++;
         indexRight++;
         i++;
      } 
      if (signCount == w)score = true;
      else
      {
         i=c-1;
         while( ( signCount<w)&&(i>=0)&&(mboard->At(r,i).player == mPlayer))  //sprawdzamy w wierszu po lewej
         {
              signCount++;
              indexLeft--;
              i--;
          }
        if (signCount == w) score = true;
        else
         {
          score = false;
         }
       }
       if (score)
       {
       for (int k=indexLeft;k<=indexRight;k++)
        {

         mboard->At(r,k).change=true;
         DrawMBCell(r,k);

        }

       }
    return score;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool verticalWin(int r, int c)
{
  char mPlayer = mboard->At(r,c).player;
   bool score;
   int  indexTop=r, indexBottom=r;
   int signCount = 1;  //liczba kom�rek ze znakiem mPlayer
   int i=r+1;
     while( ( signCount<w)&&(i<mboard->DimCount())&&(mboard->At(i,c).player == mPlayer))  //sprawdzamy w kolumnie poni�ej
      {
         signCount++;
         indexBottom++;
         i++;
      } //while 1
      if (signCount == w)score = true;
      else
      {
         i=r-1;
         while( ( signCount<w)&&(i>=0)&&(mboard->At(i,c).player == mPlayer))  //sprawdzamy w kolumnie powy�ej
         {
              signCount++;
              indexTop--;
              i--;
          }
        if (signCount == w) score = true;
        else
         {
          score = false;
         }
       }
       if (score)
       {
       for (int k=indexTop;k<=indexBottom;k++)
        {
         mboard->At(k,c).change=true;
         DrawMBCell(k,c);
        }
       }
    return score;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool diagonalLeftWin(int r, int c)
{
char mPlayer = mboard->At(r,c).player;
   bool score;
   int  indexTop=r, indexBottom=r, indexLeft=c, indexRight=c;
   int signCount = 1;  //liczba kom�rek ze znakiem mPlayer
   int i=r+1; int j=c+1;
     while( ( signCount<w)&&(i<mboard->DimCount())&&(j<mboard->DimCount())&&(mboard->At(i,j).player == mPlayer))  //sprawdzamy w dol w prawo
      {
         signCount++;
         indexBottom++; indexRight++;
         i++; j++;
      }
      if (signCount == w)score = true;
      else
      {
         i=r-1; j=c-1;
         while( ( signCount<w)&&(i>=0)&&(j>=0)&&(mboard->At(i,j).player == mPlayer))  //sprawdzamy w gore w lewo
         {
              signCount++;
              indexTop--; indexLeft--;
              i--;j--;
          }
        if (signCount == w) score = true;
        else
         {
          score = false;
         }
       }
       if (score)
       {    int k=indexTop;int l= indexLeft;
       while ((k<=indexBottom)&&(l<=indexRight))
        {
         mboard->At(k,l).change=true;
         DrawMBCell(k,l);
          k++;
          l++;
        }
       }
    return score;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool diagonalRightWin(int r, int c)
{
char mPlayer = mboard->At(r,c).player;
   bool score;
   int  indexTop=r, indexBottom=r, indexLeft=c, indexRight=c;
   int signCount = 1;  //liczba kom�rek ze znakiem mPlayer
   int i=r+1; int j=c-1;
     while( ( signCount<w)&&(i<mboard->DimCount())&&(j>=0)&&(mboard->At(i,j).player == mPlayer))  //sprawdzamy w dol w lewo
      {
         signCount++;
         indexBottom++; indexLeft--;
         i++; j--;
      }
      if (signCount == w)score = true;
      else
      {
         i=r-1; j=c+1;
         while( ( signCount<w)&&(i>=0)&&(j<=mboard->DimCount())&&(mboard->At(i,j).player == mPlayer))  //sprawdzamy w gore w prawo
         {
              signCount++;
              indexTop--; indexRight++;
              i--;j++;
          }
        if (signCount == w) score = true;
        else
         {
          score = false;
         }
       }
       if (score)
       {    int k=indexTop;int l=indexRight ;
       while ((k<=indexBottom)&&(l>=indexLeft))
        {
         mboard->At(k,l).change=true;
         DrawMBCell(k,l);
          k++;
          l--;
        }
       }
    return score;
}
//---------------------------------------------------------------------------
bool Win( int r, int c)
{ if( horizontalWin(r,c) || verticalWin( r, c) || diagonalLeftWin( r, c) || diagonalRightWin( r, c) )
    return true;
    else return false;

}

//---------------------------------------------------------------------------
__fastcall TfrmTicTac::TfrmTicTac(TComponent* Owner)
        : TForm(Owner)
{
ShowMessage("Witaj w grze K�ko i Krzy�yk! \n"
	"Wygrywa gracz, kt�ry wci�nie 5 swoich znak�w  na kolejnych polach planszy\n"
	"w pionie, poziomie lub uko�nie w lewo lub prawo. \n\n"
	"Mo�esz  zmienia� wymiar planszy od 5 do 20 \n oraz ilo�� jednakowych znak�w dla wygranej\n\n"
	"Mi�ej zabawy!\n");
}
//---------------------------------------------------------------------------
void __fastcall TfrmTicTac::FormPaint(TObject *Sender)
{
Canvas->Draw(0,pnlSetting->Height,bm);
}
//---------------------------------------------------------------------------
void __fastcall TfrmTicTac::btnStartClick(TObject *Sender)
{
 if(mboard) delete mboard;  // Usuwamy poprzedni� plansz� gry
  if(bm) delete bm;  // oraz jej bitmap�

  int d = edtDim->Text.ToInt();   // Odczytujemy rozmiar planszy


  mboard = new Board(d);       // Tworzymy now� plansz�

  d = mboard->DimCount();              // Odczytujemy wymiar  planszy
  w = edtWin->Text.ToInt(); //odcztujemy ilosc pol do wygrania
  if (w < SCOUNT) w = SCOUNT;
  if (w > d) w = d;
  edtDim->Text  = IntToStr(d);    // Korygujemy pola edycyjne
  edtWin->Text  = IntToStr(w);

  ClientWidth = FSIZE * d;         // Obliczamy wymiary okna
  ClientHeight = pnlSetting->Height + FSIZE * d;

  bm = new Graphics::TBitmap;      // Tworzymy now� bitmap� dla planszy
  bm->Width = FSIZE * d;           // Obliczamy rozmiar jej p��tna Canvas
  bm->Height = FSIZE * d;

  DrawMB();                        // Rysujemy ca�� plansz�

  Invalidate();                    // Uniewa�niamy okno, co spowoduje
                                   // przerysowanie jego tre�ci
  Playing = true;                  // Oznaczamy gr� jako aktywn�
}
//---------------------------------------------------------------------------

void __fastcall TfrmTicTac::FormCreate(TObject *Sender)
{

  DoubleBuffered = true;   // Okno podw�jnie buforowane - nie b�dzie migota�
  btnStartClick(Sender);   // Inicjujemy plansz� poprzez onClick dla przycisku START
}
//---------------------------------------------------------------------------

void __fastcall TfrmTicTac::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(Playing)                         // Sprawdzamy, czy gra jest w toku
 {
    int r = (Y - pnlSetting->Height) / FSIZE; // Obliczamy wsp�rz�dne kom�rki
    int c =  X / FSIZE;                       // klikni�tej przez gracza

    if(Button == mbLeft)                     // Lewy przycisk myszki
    {
    if  (mboard->At(r,c).player == 'n') //mozna cos wstawic
       {   if (Player == 'o')
               {
               mboard->At(r,c).player='o';
               DrawMBCell(r,c);   DrawMB();
               Invalidate();
              if (Win(r,c))
                   {
                     DrawMB();
                     Invalidate();
                     if(Application->MessageBox(
                        "Wygra� gracz O . \n" "Chcesz rozpocz�� now� gr�?","Potwierd�",
		        MB_YESNO | MB_ICONQUESTION) == IDYES )
		           {
                              DoubleBuffered = true;
                              btnStartClick(Sender);
                           } else Application->Terminate();
                     }
               else if (Filled(mboard))
                    {
                          if(Application->MessageBox(
	        	"Remiz. \n" "Chcesz rozpocz�� now� gr�?","Potwierd�",
	        	MB_YESNO | MB_ICONQUESTION) == IDYES )
                        {
                                DoubleBuffered = true;
                                 btnStartClick(Sender);
                        } else Application->Terminate();

                    }
                else
               Player='x';
               }

           else if ( Player =='x')
            {
                mboard->At(r,c).player = 'x';
                DrawMBCell(r,c);
                DrawMB();
                Invalidate();
                if (Win(r,c))
                    {
                        DrawMB();
                        Invalidate();
                        if(Application->MessageBox(
		          "Wygra� gracz X \n" "Chcesz rozpocz�� now� gr�?","Potwierd�",
                          MB_YESNO | MB_ICONQUESTION) == IDYES )
		              {
                                   DoubleBuffered = true;
                                    btnStartClick(Sender);
                              }
                        else Application->Terminate();
                    }
                 else if (Filled(mboard))
                    {
                        if(Application->MessageBox(
	        	"Remiz. \n" "Chcesz rozpocz�� now� gr�?","Potwierd�",
	        	MB_YESNO | MB_ICONQUESTION) == IDYES )
                        {
                                DoubleBuffered = true;
                                 btnStartClick(Sender);
                        }
                        else Application->Terminate();
                    }
                else
                Player='o';
            }
         }
      }
    }
 }


//---------------------------------------------------------------------------

void __fastcall TfrmTicTac::FormClose(TObject *Sender,
      TCloseAction &Action)
{
 if(Application->MessageBox(
    "Czy na pewno zako�czy� program?","Potwierd�",
    MB_YESNO | MB_ICONQUESTION) == IDNO )
		{
			Action=caNone;
		}
}
//---------------------------------------------------------------------------

