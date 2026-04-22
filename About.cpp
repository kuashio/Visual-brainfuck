//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "About.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TAboutBox *AboutBox;
//---------------------------------------------------------------------
__fastcall TAboutBox::TAboutBox(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------


void __fastcall TAboutBox::OKButtonClick(TObject *Sender)
{
  EEGG->Visible=false;
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TAboutBox::CommentsClick(TObject *Sender)
{
  ShellExecute(0,0,"http://kuashio.blogspot.com/",0,0,1);  
}
//---------------------------------------------------------------------------


void __fastcall TAboutBox::ProgramIconMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if(Shift.Contains(ssCtrl) && Shift.Contains(ssDouble) && (Button==mbLeft)){
    if (MessageBox(0,"Did you HAVE to do that?","Hey!",MB_YESNO)==IDYES)
      EEGG->Visible=true;
      Comments->Top=212+60;
      Version->Top=135+100;
  }
}
//---------------------------------------------------------------------------











