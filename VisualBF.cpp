//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "SplashScreen.h"
//---------------------------------------------------------------------------
USEFORM("Main.cpp", MainForm);
USEFORM("SplashScreen.cpp", Splash);
USEFORM("About.cpp", AboutBox);
USEFORM("input.cpp", InputForm);
USEFORM("Wait.cpp", PleaseWait);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try{//outer finally
    try
    {
      Application->Initialize();
      //TRegistry
      Splash = new TSplash(NULL);
      ::Sleep(1000);
      Splash->Show();
      Splash->Repaint();

      Application->Title = "Visual brainfuck";
     Application->HelpFile = "";
     Application->CreateForm(__classid(TMainForm), &MainForm);
     Application->CreateForm(__classid(TAboutBox), &AboutBox);
     Application->CreateForm(__classid(TPleaseWait), &PleaseWait);
     Application->Run();
    }
    catch (Exception &exception)
    {
       Application->ShowException(&exception);
    }
    catch (...)
    {
       try
       {
         throw Exception("");
       }
       catch (Exception &exception)
       {
         Application->ShowException(&exception);
       }
    }
  }
  __finally{
    if(Splash)
      delete Splash;
  }

  return 0;
}
//---------------------------------------------------------------------------
