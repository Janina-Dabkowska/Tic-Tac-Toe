//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmTicTac : public TForm
{
__published:	// IDE-managed Components
        TPanel *pnlSetting;
        TLabel *lblDim;
        TEdit *edtDim;
        TButton *btnStart;
        TEdit *edtWin;
        TLabel *lblWin;
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall btnStartClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmTicTac(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmTicTac *frmTicTac;
//---------------------------------------------------------------------------
#endif
