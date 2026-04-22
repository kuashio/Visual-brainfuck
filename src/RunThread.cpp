//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "RunThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall RunThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall RunThread::RunThread(bool CreateSuspended)
  : TThread(CreateSuspended)
{
  this->FreeOnTerminate=true;
}
bool runing=true, animate;
//---------------------------------------------------------------------------
void __fastcall RunThread::Execute()
{
  Synchronize(init);
  runing=true;
  this->FreeOnTerminate=true;
  while(!Terminated && runing){
    Synchronize(step);
    if(animate)
      Synchronize(refresh);
  }
  Synchronize(stop);
}
//---------------------------------------------------------------------------
void __fastcall RunThread::init(){
  MainForm->terminated=false;
}
//---------------------------------------------------------------------------
void __fastcall RunThread::refresh(){
  MainForm->refresh();
}
//---------------------------------------------------------------------------
void __fastcall RunThread::stop(){
  if(!Terminated){
    MainForm->SBStopClick(this);
    MainForm->terminated=true;
  }
  else MainForm->refresh();
}
//---------------------------------------------------------------------------
void __fastcall RunThread::step(){
    MainForm->Step();
    if (MainForm->bookmarks->IndexOf((void *)MainForm->LineInfo[MainForm->pc])+1){
      MainForm->SBPauseClick(this);
    }
    runing=MainForm->running;
    animate=MainForm->Animate->Checked;
}
