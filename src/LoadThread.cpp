//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Main.h"
#include "Wait.h"
#include "LoadThread.h"
#pragma package(smart_init)

#define MaxMem   30000
#define MaxCode 110000
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall LoadThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall LoadThread::LoadThread(bool CreateSuspended)
  : TThread(CreateSuspended)
{
  FreeOnTerminate=true;
}
//---------------------------------------------------------------------------

bool ya;
int j, line, i;
char buff[25];

bool __fastcall LoadThread::unbalanced(){
  int counter=0;
    Synchronize(ShowWait);
  for(int i=1;(!Terminated) && (i<=MainForm->ProgramTxt->Text.Length());i++){
      PleaseWait->Bar->Progress=i;
    switch(MainForm->ProgramTxt->Text[i]){
      case '[':counter++;break;
      case ']': counter--;
                if(counter==-1)
                  return (true);
                break;
    }
  }
  if(Terminated) return(false);
  PleaseWait->Bar->Progress=PleaseWait->Bar->MaxValue;
  return (counter);
}

//---------------------------------------------------------------------------
void __fastcall LoadThread::Execute()
{
  ::Sleep(10);
  if(unbalanced()){
    Synchronize(msg);
    return;
  }
  if(!Terminated){
    Synchronize(askToClr);
    if (!quit){
      Synchronize(init);
      j=20;
      ya=false;
      for(line=0;(!Terminated) && (line<=MainForm->ProgramTxt->Lines->Count);line++){
        for(i=0;(!Terminated) && (i<MainForm->ProgramTxt->Lines->Strings[line].Length());i++){
          Synchronize(iteration);
        }
      }
      Synchronize(after);
    }
  }
  Synchronize(close);
}

//---------------------------------------------------------------------------
void __fastcall LoadThread::after(){
  PleaseWait->Bar->Progress=PleaseWait->Bar->MaxValue;
  if (!ya){
    MainForm->ProgramArray[j] = ' ';
    j++;
  }
  strcpy(buff,"END brainfuck Code   ");
  memcpy(&(MainForm->ProgramArray[j]),buff,21);
  MainForm->modified=false;
}
//---------------------------------------------------------------------------
void __fastcall LoadThread::iteration(){
  PleaseWait->Bar->Progress++;
  switch((MainForm->ProgramTxt->Lines->Strings[line])[i+1]){
    case '~': if (!MainForm->UseBP->Checked) break;
    case '<': case '>': case '+': case '-':
    case '.': case ',': case '[': case ']':
      MainForm->ProgramArray[j] = (MainForm->ProgramTxt->Lines->Strings[line])[i+1];
      MainForm->LineInfo[j]=line;
      MainForm->ColInfo[j]=i;
      j++;
      ya=true;
    break;
    default:
      MainForm->ProgramTxt->CaretPoint.x++;
    break;
  }
}
//---------------------------------------------------------------------------
void __fastcall LoadThread::msg(){
    MessageBox(MainForm->Handle,"Please balance your brackets.\nTry indenting your code.","Brackets Error",MB_OK|MB_ICONERROR);
    MainForm->InitReels();
    MainForm->refresh();
    PleaseWait->Close();
}
char clearMem=false;
char quit=false;
//---------------------------------------------------------------------------
void __fastcall LoadThread::askToClr(){
    switch(MessageBox(MainForm->Handle,"Clear Memory Tape?","About to Load Program",
           MB_YESNOCANCEL|MB_ICONQUESTION)){
      case IDYES:    clearMem=true; break;
      case IDNO:     clearMem=false; break;
      case IDCANCEL: quit=true;
    }
}
//---------------------------------------------------------------------------
void __fastcall LoadThread::init(){
    PleaseWait->Bar->Progress=0;
    PleaseWait->Label1->Caption="Loading Program...";
    Application->ProcessMessages();

    MainForm->OutputTxt->Text="";
    MainForm->running=true;
    memset(MainForm->ColInfo,0,MaxCode);
    memset(MainForm->LineInfo,0,MaxCode);
    memset(MainForm->ProgramArray,0,MaxCode);
    if (clearMem){
      memset(MainForm->MemoryArray,0,MaxMem);
      MainForm->p=0;
    }
    MainForm->InputBuffer=MainForm->InputTxt->Text;
    MainForm->pc=20;
    for(int i=0;i<MaxMem;i++){
      MainForm->LineInfo[i]=0;
    }
    MainForm->InputBuffer=MainForm->InputTxt->Text;

    strcpy(buff,"brainfuck Code BEGIN");
    memcpy(MainForm->ProgramArray,buff,20);
}
//---------------------------------------------------------------------------
void __fastcall LoadThread::close(){
  if(Terminated){
    MainForm->InitReels();
  }
  PleaseWait->Close();
}
//---------------------------------------------------------------------------
void __fastcall LoadThread::ShowWait()
{
    //PleaseWait->ShowModal();
    PleaseWait->Bar->MaxValue=MainForm->ProgramTxt->Text.Length();
    PleaseWait->Label1->Caption="Looking for Unbalanced Brackets...";
    Application->ProcessMessages();
}

//---------------------------------------------------------------------------