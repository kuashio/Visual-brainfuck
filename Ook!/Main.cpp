//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "ThreadEnc.h"
//---------------------------------------------------------------------------
#pragma link "CGAUGES"
#pragma resource "*.dfm"
TMainForm *MainForm;
TEncode *Translate;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
}                     
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
  Mensaje->Text = "";
  Salida->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::resize(TObject *Sender)
{
   Mensaje->Height=MainForm->Height*.3;
   Salida->Top  = Mensaje-> Height+40;
   Salida->Height=MainForm->Height-Mensaje->Height-115;
   Label2->Top=Salida->Top-20;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::finThread(TObject *Sender)
{
  if (Salida->Text.Length()){
    Button2->Enabled=false;
    Button1->Enabled=true;
    Button1->SetFocus();
  }
}

//----------------------------------------------------------------------------

void __fastcall TMainForm::Button1Click(TObject *Sender)
{
  Button1->Enabled=false;
  Button2->Enabled=true;
  Button2->SetFocus();
  Translate=new TEncode(false);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Button2Click(TObject *Sender)
{
  Translate->Terminate();
  Button2->Enabled=false;
  Button1->Enabled=true;
  Button1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
  if (Translate!=NULL)
    Translate->Terminate();
}
//---------------------------------------------------------------------------


