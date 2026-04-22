//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "input.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RXSpin"
#pragma resource "*.dfm"
TInputForm *InputForm;

AnsiString LastChar;
//---------------------------------------------------------------------------
__fastcall TInputForm::TInputForm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TInputForm::BResumeClick(TObject *Sender)
{
  MainForm->InputTxt->Text=Edit1->Text;
  MainForm->InputBuffer=MainForm->InputBuffer+Edit1->Text;
//  this->ModalResult=1;
//  Close();
}
//---------------------------------------------------------------------------
void __fastcall TInputForm::BEnterCharClick(TObject *Sender)
{
  AnsiString temp;
  if(EditChar->Value==0){
    Edit1->Text = Edit1->Text + "\\0";
  }
  else{
    Edit1->Text = Edit1->Text + temp.sprintf("%c",(int)EditChar->Value);
  }
  Edit1->SetFocus();
  Edit1->SelStart=Edit1->Text.Length();
}
//---------------------------------------------------------------------------

void __fastcall TInputForm::EditCharExit(TObject *Sender)
{
  if(EditChar->Text.Pos("-") || EditChar->Text.Pos("+") || !EditChar->Text.Length() )
    EditChar->Text=LastChar;
  if (EditChar->Value>255)EditChar->Value=255;
  if (EditChar->Value<0)EditChar->Value=0;
  LastChar=EditChar->Text;
}
//---------------------------------------------------------------------------

void __fastcall TInputForm::EditCharBottomClick(TObject *Sender)
{
  if(!EditChar->Value)EditChar->Value=EditChar->MaxValue;
}
//---------------------------------------------------------------------------

void __fastcall TInputForm::EditCharTopClick(TObject *Sender)
{
  if(EditChar->Value==EditChar->MaxValue)EditChar->Value=0;
}
//---------------------------------------------------------------------------


void __fastcall TInputForm::Edit1Change(TObject *Sender)
{
  if(Edit1->Text.Length()){
    BResume->Enabled=true;
  }
  else{
    BResume->Enabled=false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TInputForm::FormShow(TObject *Sender)
{
  LastChar="0";
  Edit1->Text="";
  EditChar->Value=0;
}
//---------------------------------------------------------------------------

void __fastcall TInputForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
  ModalResult=mrAbort;
}
//---------------------------------------------------------------------------




