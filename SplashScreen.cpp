//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SplashScreen.h"
//#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSplash *Splash;
//---------------------------------------------------------------------------
__fastcall TSplash::TSplash(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TSplash::Timer1Timer(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------


