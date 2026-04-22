//---------------------------------------------------------------------------

#ifndef WaitH
#define WaitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "CGAUGES.h"
//---------------------------------------------------------------------------
class TPleaseWait : public TForm
{
__published:	// IDE-managed Components
  TLabel *Label1;
  TPanel *Panel1;
  TCGauge *Bar;
  TButton *BCancel;
  void __fastcall BCancelClick(TObject *Sender);
  void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:	// User declarations
public:		// User declarations
  __fastcall TPleaseWait(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPleaseWait *PleaseWait;
//---------------------------------------------------------------------------
#endif
