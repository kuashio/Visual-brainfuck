//---------------------------------------------------------------------------

#ifndef inputH
#define inputH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RXSpin.hpp"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TInputForm : public TForm
{
__published:	// IDE-managed Components
  TLabeledEdit *Edit1;
  TButton *BEnterChar;
  TRxSpinEdit *EditChar;
  TBitBtn *BPause;
  TBitBtn *BResume;
  void __fastcall BEnterCharClick(TObject *Sender);
  void __fastcall EditCharExit(TObject *Sender);
  void __fastcall EditCharBottomClick(TObject *Sender);
  void __fastcall EditCharTopClick(TObject *Sender);
  void __fastcall Edit1Change(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
  void __fastcall BResumeClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TInputForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInputForm *InputForm;
//---------------------------------------------------------------------------
#endif
