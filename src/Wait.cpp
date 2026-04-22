//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Wait.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGAUGES"
#pragma resource "*.dfm"
TPleaseWait *PleaseWait;
//---------------------------------------------------------------------------
__fastcall TPleaseWait::TPleaseWait(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPleaseWait::BCancelClick(TObject *Sender)
{
  MainForm->Load->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TPleaseWait::FormCloseQuery(TObject *Sender,
      bool &CanClose)
{
  MainForm->Load->Terminate();
}
//---------------------------------------------------------------------------

