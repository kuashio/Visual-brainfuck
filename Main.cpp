                                                                                //
                                                                               //
                                                                              //
                                                                             //
                                                                            //
                                                                           //
                                                                          //
                                                                         //
//----------------------------------------------------------------------//---
#include <vcl.h>                                                       //
#pragma hdrstop                                                       //
#include "Main.h"                                                    //
#include "SplashScreen.h"                                           //
#include "About.h"                                                 //
#include "input.h"                                                //
#include "Wait.h"                                                //
#include "RunThread.h"                                          //
//#include "LoadThread.h"                                      //
#include <stdio.h>                                            //
//-----------------------------------------------------------//--------------
#pragma link "dccommon"                                     //
#pragma link "dcmemo"                                      //
#pragma link "dcSyntax"                                   //
#pragma link "dcsystem"                                  //
#pragma link "dcstring"                                 //
#pragma link "dccommon"                                //
#pragma link "dcmemo"                                 //
#pragma link "dcstring"                              //
#pragma link "dcSyntax"                             //
#pragma link "dcsystem"                            //
#pragma link "CSPIN"                              //
#pragma link "RXSpin"                            //
#pragma resource "*.dfm"                        //
                                               //
                                              //
TMainForm *MainForm;                         //
//------------------------------------------//---------------------------------
/**** Turing Machine Variables****/        //
                                          //
#define MaxMem   30000                   //
#define MaxCode 110000                  //
                                       //
unsigned char MemoryArray[MaxMem];    // Memory Tape
char ProgramArray[MaxCode];          // Program Tape
AnsiString InputBuffer;             // Input Buffer
int p=0;                           // The Pointer
int c;                            // Cycle nesting depth counter
int pc=0;                        // The Program Counter
//------------------------------//-------------------------------------------
int ColInfo[MaxCode];          // Column location for instructions
int LineInfo[MaxCode];        // Line location for instructions
//---------------------------//----------------------------------------------
//Editor Variables          //
                           //
TList *bookmarks;         //
TPoint caret;            //
AnsiString LastJump;    //
AnsiString LastSet;    //
AnsiString LastChar1; //
RunThread *Run;      //
LoadThread *Load;   //
bool running=false,//
   modified=false,//
terminated=false,//
    force=false;//
               //
//------------//-------------------------------------------------------------
bool __fastcall TMainForm::isRunning(){
  return(running);
}
//---------------------------------------------------------------------------
int __fastcall TMainForm::right(int ptr){
  return((ptr!=(MaxMem-1))?ptr+1:0);
}
int __fastcall TMainForm::left(int ptr){
  return(ptr?ptr-1:MaxMem-1);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::RIGHT(){
  p=right(p);
}
void __fastcall TMainForm::LEFT(){
  p=left(p);
}
void __fastcall TMainForm::PLUS(){
  MemoryArray[p]++;
}
void __fastcall TMainForm::MINUS(){
  MemoryArray[p]--;
}
void __fastcall TMainForm::COMA(){
  int offset=2;
  if(InputTxt->Text.Length()){
    if(InputTxt->Text[1]!= '\\' || InputTxt->Text.Length()==1){
      if(IgnoreCR->Checked && InputTxt->Text.Length()>1
        && InputTxt->Text[1]== '\r' && InputTxt->Text[2]== '\n'){
          MemoryArray[p]=10;
          offset=3;
      }
      else{
        MemoryArray[p]=(unsigned char)InputTxt->Text[1];
      }
    }
    else{   // if textLength>1 && firs char= backslash
      switch(InputTxt->Text[2]){
        case '0':
                  MemoryArray[p]=0;
                  offset=3; break;
        case 'n':
                  MemoryArray[p]=10;
                  offset=3; break;
        case 't':
                  MemoryArray[p]=9;
                  offset=3; break;
        case 'b':
                  MemoryArray[p]=8;
                  offset=3; break;
        case 'r':
                  MemoryArray[p]=13;
                  offset=3; break;
        case '\\':
                  offset=3;
        default:
                  MemoryArray[p]='\\'; break;
      }
    }
    InputTxt->Text=InputTxt->Text.SubString(offset,InputTxt->Text.Length()-1);
  }
  else{
    //ask for input in a dialog
    TInputForm *InForm=new TInputForm(this);
    if(InForm->ShowModal()==mrAbort){
      SBPauseClick(this);
      if(running)pc--;
      return;
    }
//    OutputTxt->SetFocus();           by kuashio
    delete(InForm);
    COMA();
  }
}
void __fastcall TMainForm::DOT(){
  AnsiString temp/*=OutputTxt->Text*/;
  //MainForm->OutputTxt->SetFocus();
//  OutputTxt->SelStart=OutputTxt->Text.Length();
  switch(MemoryArray[p]){
    //case 10: /*OutputTxt->Lines->Add("");*/ break;
    case 13: if(IgnoreCR->Checked){
               OutputTxt->SelStart=OutputTxt->Text.Length()-2;
               return;
             }
             break;
    case 8:   //backspace
        OutputTxt->Text=OutputTxt->Text.SubString(1,OutputTxt->Text.Length()-3);
        break;
    default:
//        OutputTxt->Text.cat_printf("%c",MemoryArray[p]);
        OutputTxt->Text=OutputTxt->Text.SubString(1,OutputTxt->Text.Length()-2);
//        OutputTxt->Text.Insert(temp.sprintf("%c",MemoryArray[p]),OutputTxt->Text.Length());
        OutputTxt->Text=OutputTxt->Text+temp.sprintf("%c",MemoryArray[p]);
        //int len=OutputTxt->Text.Length();
        //OutputTxt->Lines->Delete(OutputTxt->Lines->Count-1);
//        OutputTxt->Lines->Strings[OutputTxt->Lines->Count].
//          Insert(temp.sprintf("%c",MemoryArray[p]),
//            OutputTxt->Lines->Strings[OutputTxt->Lines->Count].Length());
        break;
  }
  //int a=1;
  //a++;
  OutputTxt->Lines->Add("");
  OutputTxt->SelStart=OutputTxt->Text.Length()-2;
//  OutputTxt->SetFocus();       by kuashio
}

void __fastcall TMainForm::OPEN(){
  int counter=1;
  if(!MemoryArray[p]){
    while(counter){
      pc++;
      if(ProgramArray[pc]=='[') counter++;
      if(ProgramArray[pc]==']') counter--;
    }
  }
}
void __fastcall TMainForm::CLOSE(){
  int counter=1;
  if(MemoryArray[p]){
    while(counter){
      pc--;
      if(ProgramArray[pc]==']') counter++;
      if(ProgramArray[pc]=='[') counter--;
    }
  }
}


void __fastcall TMainForm::Step(){
  switch(ProgramArray[pc]){
    case'<':p=(p?p-1:MaxMem-1);/*LEFT();*/break;
    case'>':p=((p!=(MaxMem-1))?p+1:0); /*RIGHT();*/ break;
    case'+':MemoryArray[p]++;/*PLUS();*/break;
    case'-':MemoryArray[p]--;/*MINUS();*/break;
    case',':COMA();break;
    case'.':DOT();break;
    case'[':OPEN();break;
    case']':CLOSE();break;
    case'~':SBPauseClick(this);break;
  }
  pc++;
/*  if (bookmarks->IndexOf((void *)LineInfo[pc])+1){
    MainForm->SBPauseClick(this);
  }*/
  if ((ProgramArray[pc]=='E')||(ProgramArray[pc]=='N')||(ProgramArray[pc]==' ')){
    running=false;
    InputTxt->Text=InputBuffer;
    SBStep->Enabled=true;
    MStep->Enabled=true; // estos eran los ultimos falses
    //pc--;
  }
}
//---------------------------------------------------------------------------
int __fastcall TMainForm::getLine(int charindex){
  int i=20;
  while(charindex>LineInfo[i-20]){
    i++;
    if((i-20)==(ProgramTxt->Lines->Count)) return(-1);
  }
  return(i-19);  // 1-based
}
//---------------------------------------------------------------------------
bool virgo=true;

int __fastcall TMainForm::unbalancedold(){
  int counter=0;
/*
  if(!virgo){
    PleaseWait->Show();
    PleaseWait->Bar->MaxValue=ProgramTxt->Text.Length();
    PleaseWait->Label1->Caption="Looking for unbalanced Brackets...";
    Application->ProcessMessages();
  }
  for(int i=1;i<=ProgramTxt->Text.Length();i++){
    if(!virgo){
      PleaseWait->Bar->Progress=i;
    }
    switch(ProgramTxt->Text[i]){
      case '[':counter++;break;
      case ']': counter--;
                if(counter==-1)
                  return (true);
                break;
    }
  }                */
  return (counter);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::load(){
  Load=new LoadThread(false);
  PleaseWait->ShowModal();
}
/*
  if(unbalanced()){
  //PleaseWait->Label2->Visible=false;
    MessageBox(Handle,"Please balance your brackets.\nTry indenting your code.","Brackets Error",MB_OK|MB_ICONERROR);
    if(!virgo){PleaseWait->Close();}
    return;
  }
  if(!virgo){
    PleaseWait->Bar->Progress=0;
//    PleaseWait->Bar->Progress=;
    PleaseWait->Label1->Caption="Loading Program...";
    Application->ProcessMessages();
  }
  OutputTxt->Text="";
  running=true;
  memset(ProgramArray,0,MaxCode);
  memset(MemoryArray,0,MaxMem);
  InputBuffer=InputTxt->Text;
  p=0;
  pc=20;
  for(int i=0;i<MaxMem;i++){
    LineInfo[i]=0;
  }

  InputBuffer=InputTxt->Text;

  char buff[25];
  strcpy(buff,"BrainFuck Code BEGIN");
  memcpy(ProgramArray,buff,20);
  int j=20;
  bool ya=false;
  //caret=ProgramTxt->CaretPoint;
//  ProgramTxt->MemoSource->JumpToChar(1);
//    ProgramTxt->MemoSource->SetCaretPoint(TPoint(1,1));
  for(int line=0;line<=ProgramTxt->Lines->Count;line++){
    for(int i=0;i<ProgramTxt->Lines->Strings[line].Length();i++){
      PleaseWait->Bar->Progress++;
      switch((ProgramTxt->Lines->Strings[line])[i+1]){
        case '~': if (!UseBP->Checked) break;
        case '<': case '>': case '+': case '-':
        case '.': case ',': case '[': case ']':
          ProgramArray[j] = (ProgramTxt->Lines->Strings[line])[i+1];
  //        ProgramTxt->CaretPoint.x++;
          LineInfo[line]=j;
          j++;
          ya=true;
        break;
        default:
          ProgramTxt->CaretPoint.x++;
        break;
      }
    }
  }
  // ProgramTxt->CaretPoint=caret;
  if (!ya){
    ProgramArray[j] = ' ';
    j++;
  }
  strcpy(buff,"END BrainFuck Code  ");
  memcpy(&ProgramArray[j],buff,20);
  modified=false;
  if(!virgo){PleaseWait->Close();}
  else virgo=false;
}            */
//---------------------------------------------------------------------------
void __fastcall TMainForm::refresh(){
  int i=13, j=left(p);
  AnsiString temp;

  if((running)||(force)){
    caret.x=ColInfo[pc];
    caret.y=LineInfo[pc];
    if(force){
      caret.x=ColInfo[pc-1]+1;
      caret.y=LineInfo[pc-1];
    }
    MemoSource1->CaretPoint=caret;
    MemoSource1->SetBookmark(1);
  }
  Prev->Enabled=true;
  Next->Enabled=true;

  if (ProgramArray[pc-1]=='N')
    Prev->Enabled=false;


  if ((ProgramArray[pc]=='E')||(ProgramArray[pc]=='N')||(ProgramArray[pc]==' ')){ //pc+1   //E
    running=false;
    SBStep->Enabled=true;
    MStep->Enabled=true;         // estos tambien
    Next->Enabled=false;
  }
  else{
    //MStep->Enabled=true;
    //SBStep->Enabled=true;
  }

  char format[5];
  switch(Display->ItemIndex){
    case 0: strcpy(format,"%u");break;
    case 1: strcpy(format,"%X");break;
    case 2: strcpy(format,"%c");break;
  }

  pWatch->Text=temp.sprintf("%u",p);

  while (i+1){
    MemoryTape->Cells[i][0]=temp.sprintf(format,MemoryArray[j]);
    j=left(j);
    i--;
  }
  j=p;
  for(i=14;i<29;i++){
    MemoryTape->Cells[i][0]=temp.sprintf(format,MemoryArray[j]);
    j=right(j);
  }
  j=pc-20;
  for (i=0;i<41;i++){
      ProgramTape->Cells[i][0]=ProgramArray[j+i];
  }

}

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
  SetFileName("Untitled.bf");
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::InitReels(){
  memset(MemoryArray,0,MaxMem);
  pc=20;
  p=0;
  running=false;
  char buff[45];
  strcpy(buff,"brainfuck Code BEGIN END brainfuck Code   ");
  for (int i=0; i<42; i++){
    ProgramArray[i]=buff[i];
  }
  refresh();
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
  bookmarks=new TList();
  struct TGridRect coord;
  coord.Top=0;
  coord.Left=14;
  coord.Right=14;

  terminated=true;
  MainForm->WindowState=wsMaximized;

	Application->OnHint = ShowHint;
  int i;

  /*char buff[50];
  strcpy(buff,">>+++++[<+++>-]<---.,.>+++[<+++>-]<+.--..");
  for (i=0; i<41; i++){
    ProgramTape->Cells[i][0]=buff[i];
  }
  */
  InitReels();

  MemoryTape->Selection=coord;
  coord.Left=20;
  coord.Right=20;
  ProgramTape->Selection=coord;
  LastJump="0";
  LastSet="0";
  LastChar1="0";
  ResetFlechas();
  FileNew(Sender);
  ProgramTxt->Enabled=true;

  MRun->Hint=SBRun->Hint;
  MPause->Hint=SBPause->Hint;
  MStep->Hint=SBStep->Hint;
  MStop->Hint=SBStop->Hint;
  MReset->Hint=SBReset->Hint ;
  MakeExecutable1->Hint=SBExe->Hint;
  OpenDialog->InitialDir=(ExtractFilePath(Application->ExeName)+"\sample code"); //akiiii
  SaveEXE->InitialDir=(ExtractFilePath(Application->ExeName)+"\output"); //akiiii
  SaveDialog->InitialDir=(ExtractFilePath(Application->ExeName)+"\sample code"); //akiiii

}
//----------------------------------------------------------------------------
void __fastcall TMainForm::ShowHint(TObject *Sender)
{
	StatusLine->SimpleText = Application->Hint;
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::FileNew(TObject *Sender)
{
  SBPauseClick(Sender);
  CheckFileSave();
  SetFileName("Untitled.bf");
  ProgramTxt->Lines->Clear();
  MemoSource1->Modified  = false;
  modified=false;
  running=false;
  bookmarks->Clear();
//  bookmarks=new TList();
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::CheckFileSave(void)
{
  if(MemoSource1->Modified)
  {
    switch(MessageBox(Handle, "Save current changes?", "File Modified",MB_YESNOCANCEL | MB_ICONQUESTION))
    {
      case ID_YES:
          FileSave(this);
          break;

      case ID_CANCEL:
          Abort();
    };
  }
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::SetFileName(const AnsiString FileName)
{
  char lpBuf[100] = "Visual brainfuck - ";
  strcat(lpBuf, ExtractFileName(FileName).c_str());
  //strcat(lpBuf, "]");

  Caption = lpBuf;
  FFileName = FileName;
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::FileOpen(TObject *Sender)
{
  SBPauseClick(Sender);
  CheckFileSave();
	if (OpenDialog->Execute())
	{
    ProgramTxt->Lines->LoadFromFile(OpenDialog->FileName);
    SetFileName(OpenDialog->FileName);
    ProgramTxt->SetFocus();
    MemoSource1->Modified = false;
    modified=false;
    ProgramTxt->ReadOnly = OpenDialog->Options.Contains(ofReadOnly);
		running=false;
    bookmarks->Clear();
//    bookmarks=new TList();
	}
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::FileSave(TObject *Sender)
{
  SBPauseClick(Sender);
  if ( !strcmp(FFileName.c_str(), "Untitled.bf" ) )
    FileSaveAs(Sender);
  else
  {
    ProgramTxt->Lines->SaveToFile(FFileName);
    MemoSource1->Modified = false;
    modified=false;
  }
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::FileSaveAs(TObject *Sender)
{
  SBPauseClick(Sender);
  if ( SaveDialog->Execute() )
  {
    AnsiString f=SaveDialog->FileName;
    // Options + OverwritePrompt = true, thus no need to check.
    if(!(SaveDialog->FileName.Pos(".")))
      f+=SaveDialog->FilterIndex==3?".txt":".bf";
    ProgramTxt->Lines->SaveToFile(f);
    SetFileName(f);
    MemoSource1->Modified = false;
    modified=false;
  }
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::FilePrint(TObject *Sender)
{
  try{
    SBPauseClick(Sender);

    if(PrintDialog->Execute() ){
      //AnsiString as=ProgramTxt->Text;
      //ProgramTxt->Text="\n\n"+ProgramTxt->Text;
      ProgramTxt->Print();
      //ProgramTxt->Text=as;
    }
  }
  catch(...){
    MessageBox(Handle,"Something went Wrong, Zurrie!","Whoops!",MB_OK);
  }
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::FilePrintSetup(TObject *Sender)
{
  SBPauseClick(Sender);
	PrintSetupDialog->Execute();
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::FileExit(TObject *Sender)
{
	Close();
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::EditUndo(TObject *Sender)
{
	//---- Add code to perform Edit Undo ----
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::EditCut(TObject *Sender)
{
	//---- Add code to perform Edit Cut ----
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::EditCopy(TObject *Sender)
{
	//--- Add code to perform Edit Copy ----
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::EditPaste(TObject *Sender)
{
	//---- Add code to perform Edit Paste ----
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::HelpContents(TObject *Sender)
{
  ShellExecute(NULL,NULL,"vbfHelp.htm",NULL,
    (ExtractFilePath(Application->ExeName)+"\help").c_str(),4);
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::HelpSearch(TObject *Sender)
{
	Application->HelpCommand(HELP_PARTIALKEY, Longint(""));
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::HelpHowToUse(TObject *Sender)
{
	Application->HelpCommand(HELP_HELPONHELP, 0);
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::HelpAbout(TObject *Sender)
{
//	ShellAbout(NULL,"Visual BrainFuck v1.0.0","Developed by Kuashio",0);
  AboutBox->ShowModal();
}

//----------------------------------------------------------------------------
int aha=0;
void __fastcall TMainForm::RadioGroup1Click(TObject *Sender)
{
  refresh();/*
  char buff[50];
  strcpy(buff,"hola\nhola\nculohola\nhola\nculohola\nhola\nculohola\nhola\nculo");
  //Program->ReadOnly=false;
  //Output->Clear();
  MainForm->OutputTxt->Text=buff;
  MainForm->OutputTxt->SelStart=MainForm->OutputTxt->Text.Length();
  MainForm->OutputTxt->SetFocus();
  if (aha){
    MainForm->SBStep->Enabled=false;
    aha=0;
    return;
  }
  aha=1;
    MainForm->SBStep->Enabled=true;*/
}
//---------------------------------------------------------------------------

bool __fastcall TMainForm::checkModified(){
  if (modified && running)
    switch(MessageBox(Handle,"Source has been modified. Rebuild?","Information",MB_YESNOCANCEL|MB_ICONINFORMATION)){
      case IDYES: load();
      case IDNO: modified=false;return(true);
      case IDCANCEL: return(false);
    }
  if (!running)load();
  return(true);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SBRunClick(TObject *Sender)
{
  if(!checkModified()) return;
  refresh();
  if (!running) return;
//  OutputTxt->SetFocus(); //by kuashio
//  OutputTxt->Enabled=false;
  MainForm->SBPause->Visible=true;
  MainForm->SBRun->Visible=false;
  MainForm->SBStop->Visible=true;
  MainForm->SBReset->Visible=false;
  MainForm->SBStep->Enabled=false;

  MPause->Enabled=true;
  MRun->Enabled=false;
  MStop->Enabled=true;
  MReset->Enabled=false;
  MStep->Enabled=false;
  terminated=false;
  Run=new RunThread(false);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SBStepClick(TObject *Sender)
{
  if(ProgramArray[pc]==' '||ProgramArray[pc]=='E'){
    if (Run!=NULL) Run->Terminate();
    terminated=true;
    refresh();
    }

  if(!checkModified()) return;
  if (running){
//    OutputTxt->SetFocus();  by kuashio
    Step();
    refresh();
  }  /*
  else{
    SBStep->Enabled=false;
  }*/
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SBPauseClick(TObject *Sender)
{
  if (Run!=NULL) Run->Terminate();
  terminated=true;
  MainForm->SBPause->Visible=false;
  MainForm->SBRun->Visible=true;
  MainForm->SBStop->Visible=false;
  MainForm->SBReset->Visible=true;
  MainForm->SBStep->Enabled=true;

  MPause->Enabled=false;
  MRun->Enabled=true;
  MStop->Enabled=false;
  MReset->Enabled=true;
  MStep->Enabled=true;
  refresh();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SBResetClick(TObject *Sender)
{
  if (Run!=NULL) Run->Terminate();
  terminated=true;
  MainForm->SBStep->Enabled=true;
  MStep->Enabled=true;
  load();
  refresh();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SBStopClick(TObject *Sender)
{
  if (Run!=NULL) Run->Terminate();
  terminated=true;
  MainForm->SBPause->Visible=false;
  MainForm->SBRun->Visible=true;
  MainForm->SBStop->Visible=false;
  MainForm->SBReset->Visible=true;
  MainForm->SBStep->Enabled=true;

  MPause->Enabled=false;
  MRun->Enabled=true;
  MStop->Enabled=false;
  MReset->Enabled=true;
  MStep->Enabled=true;

  running=false;
  //InputTxt->Text=InputBuffer;
  force=true;
  refresh();
  force=false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
  try
  {                 
    SBPauseClick(Sender);
    CheckFileSave();
  }
  catch(...)
  {
    CanClose = false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormShow(TObject *Sender)
{
  ProgramTxt->SetFocus();
  ::Sleep(2500);
/*
  if(Splash){
    delete Splash;
    Splash = NULL;
  }*/
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TextEncoder1Click(TObject *Sender)
{
  ShellExecute(NULL,NULL,"Encoder.exe",NULL,
    ExtractFilePath(Application->ExeName).c_str(),4);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::OokTranslator1Click(TObject *Sender)
{
  AnsiString w="";
  ShellExecute(NULL,NULL,"Ook.exe",NULL,
    ExtractFilePath(Application->ExeName).c_str(),4);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ResetFlechas(){
  Flecha0->Down=true;
  Flecha1->Down=true;
  Flecha2->Down=true;
  Flecha3->Down=true;
  Flecha4->Down=true;
}

void __fastcall TMainForm::print(AnsiString ins){
      caret= MemoSource1->CaretPoint;
      MemoSource1->Insert(ins);
      caret.x+=ins.Length();
      MemoSource1->CaretPoint=caret;
}

void __fastcall TMainForm::println(){
      caret= MemoSource1->CaretPoint;
      MemoSource1->InsertLine();
      caret.y++;
      caret.x=1;
      MemoSource1->CaretPoint=caret;
}

void __fastcall TMainForm::println(AnsiString ins){
      print(ins);
      println();
}

void __fastcall TMainForm::ProgramTxtMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if (Button==mbLeft){
    if (!Flecha0->Down || !Flecha1->Down || !Flecha2->Down
      ||!Flecha3->Down || !Flecha4->Down){
      //int caret=ProgramTxt->CaretCharPos;
      caret= MemoSource1->GetCaretPoint();
      //AnsiString as=ProgramTxt->Text, ins;

      if(SBSEEK20->Down){ println();
        println("Seeks two 0s to the right: Stops at leftmost 0");
        println("[>]>[[>]>]< ");
      }
      else if(SBSEEK0->Down) print("Seeks 0 to the right [>] ");
      else if(SBMOV->Down){ println();
        println("  *p = AxB plus C");
        println("  Replace A B C with as many plus signs as needed");
        println("  Requires one free cell to the right");
        println("  [-]>[-]A[<B>-]<C ");
      }
      else if(SBOK->Down)
        print(" Insert a newline character and send to output: [-]++++++++++. ");
      else if(SBINPUT->Down){ println();
        println("  PROMPT");
        println("  Prints a '?' character and takes a byte from input");
        println("  Requires one free cell to the right");
        println("  [-]>[-]++++++++[<++++++++>-]<-., ");
      }

      else if(SBCOM->Down)
        print("[-][{ Commented Code Here (Balanced brackets required) }][-]");
      else if(SBCLR0->Down || SBCLR->Down)
        print("Clear current cell [-] ");
      else if(SBBR->Down)
        print(" ~ ");

      else if(SBIF->Down) print("if(*p!=0) [Then Code Here[-]] ");
      else if(SBMOVE->Down){ println();
        println("  MOVE");
        println("  Moves contents of current cell to next cell to the right");
        println("  Leaves pointer at current cell; containing 0");
        println("  Requires one free cell to the right");
        println("  >[-]<[>+<-] ");
      }
      else if(SBDUP->Down){ println();
        println("  DUPLICATE");
        println("  Duplicates current cell into next cell to the right");
        println("  Leaves pointer at current cell; unchanged");
        println("  Requires two free cells to the right");
        println("  >[-]>[-]<<[>>+<<-]>>[<+<+>>-]<< ");
      }
      else if(SBSWAP->Down){ println();
        println("  SWAP");
        println("  Swaps current cell with next cell to the right");
        println("  Leaves pointer at current cell");
        println("  Requires current cell; cell to swap; and 1 free cell to the right");
        println("  >>[-]<<[>>+<<-]>[<+>-]>[<+>-]<< ");
      }
      else if(SBTOUPPER->Down){ println();
        println("  TO UPPERCASE");
        println("  Turns current cell into uppercase");
        println("  Please make sure it's a letter (a_z;A_Z)");
        println("  Leaves pointer at current cell");
        println("  Requires one free cell to the right");
        println("  >[-]++++[<-------->-]<");
      }
      else if(SBTOLOWER->Down){ println();
        println("  TO LOWERCASE");
        println("  Turns current cell into lowercase");
        println("  Please make sure it's a letter (a_z;A_Z)");
        println("  Leaves pointer at current cell");
        println("  Requires one free cell to the right");
        println("  >[-]++++[<++++++++>-]< ");
      }
      else if(SBFLUSH->Down)
        print(" Flushes the whole input through the output ,[.,] ");

      else if(SBHW->Down){ println();
        println("  HELLO WORLD");
        println("  Leaves pointer at current cell unchanged");
        println("  Requires two free cells to the right");
        println("  >[-] >[-]++++++++[<+++++++++>-]<.>+++");
        println("  ++[<++++++>-]<-.+++++++..+++.>+++++++");
        println("  ++[<--------->-]<++.>+++++++[<+++++++");
        println("  +>-]<-.>+++++[<+++++>-]<-.+++.------.");
        println("  --------.>++++++++[<-------->-]<---.<");
      }
      else if(SB666->Down){ println();
        println("  666; THE NUMBER OF THE BEAST");
        println("  Leaves pointer at current cell unchanged");
        println("  Requires two free cells to the right");
        println("  >[-]>[-]+++++++[<++++++++>-]<--...< ");
      }
      else if(SBASCII->Down){ println();
        println("  ASCII CHARACTER SET");
        println("  Prints ASCII characters");
        println("  Leaves pointer at current cell containing 0");
        println("  [-].+ Start from 0; Remove this line to start from current value");
        println("  [.+] ");
      }
      else if(SBREV->Down){ println();
        println("  PRINT BACKWARDS");
        println("  Prints the whole input backwards");
        println("  Leaves pointer at current cell containing 0");
        println("  Requires free cells to the right to hold the input");
        println("  [-]>,[>,]<[.<] ");
      }

      else if(SBADD->Down){ println();
        println("  ADD");
        println("  Adds the current cell plus the next to the right");
        println("  The next cell to the right will be lost; replaced with 0");
        println("  Leaves pointer at current cell containing the sum");
        println("  Requires current cell and one cell to add to the right");
        println("  >[<+>-]< ");
      }
      else if(SBSUB->Down){ println();
        println("  SUBTRACT");
        println("  Subtracts the current cell minus the next to the right");
        println("  The next cell to the right will be lost; replaced with 0");
        println("  Leaves pointer at current cell containing the difference");
        println("  Requires current cell and one cell to subtract to the right");
        println("  >[<->-]< ");
      }
      else if(SBMUL->Down){ println();
        println("  MULTIPLY");
        println("  Multiplies the current cell times the next to the right");
        println("  The next cell to the right will remain unchanged");
        println("  The result will be stored two cells to the right");
        println("  Leaves pointer at current cell containing 0");
        println("  Requires current cell with operand; next cell with operand;");
        println("  the next cell to store the product; and the next as a temp value");
        println("  >>[-]>[-]<<< [>[>+>+<<-]>>[<<+>>-]<<<-]");
      }
      else if(SBDIV->Down){ println();
        println("  INTEGER (QUOTIENT) DIVIDE");
        println("  Divides the current cell by the next to the right");
        println("  Leaves pointer at current cell containing the quotient");
        println("  The next 5 cells will contain 0");
        println("  Requires current cell with dividend; next cell with divisor");
        println("  and the next 4 cells as temp values");
        println("  >>[-]>[-]>[-]<<<<[>[->+>+<<]>[-<<-[");
        println("  >]>>>[<[>>>-<<<[-]]>>]<<]>>>+<<[-<<");
        println("  +>>]<<<]>[-]>>>>[-<<<<<+>>>>>]<<<<<");
      }
      else if(SBCHARTOINT->Down){ println();
        println("  CHAR TO INT");
        println("  Turns current number ASCII character to number");
        println("  Please make sure it's a numeric character ('0'_'9')");
        println("  Leaves pointer at current cell");
        println("  Requires one free cell to the right");
        println("  >[-]++++++[<-------->-]< ");
      }
      else if(SBINTTOCHAR->Down){ println();
        println("  INT TO CHAR");
        println("  Turns current number to its number ASCII character");
        println("  Please make sure it's a decimal digit (0_9)");
        println("  Leaves pointer at current cell");
        println("  Requires one free cell to the right");
        println("  >[-]++++++[<++++++++>-]< ");
      }

      else if(SBNOT->Down){ println();
        println("  LOGICAL NOT");
        println("  Replaces current cell with the negation of next cell");
        println("  Leaves pointer at current cell");
        println("  Requires one cell to the right with the operand; which will be lost (0)");
        println("  0x01=\"true\";0x00=\"false\"");
        println("  [-]+>[<->[-]]< ");
      }
      else if(SBAND->Down){ println();
        println("  LOGICAL AND");
        println("  Performs a logical AND operation to the next 2 cells");
        println("  Leaves pointer at current cell with the result");
        println("  Requires two cells to the right with the operands; which will be lost (0)");
        println("  0x01=\"true\";0x00=\"false\"");
        println("  [-]>[>[<<+>>[-]]<[-]]< ");
      }
      else if(SBOR->Down){ println();
        println("  LOGICAL OR");
        println("  Performs a logical OR operation to the next 2 cells");
        println("  Leaves pointer at current cell with the result");
        println("  Requires two cells to the right with the operands; which will be lost (0);");
        println("  and one more to the right as a temp variable; which will also be lost (0)");
        println("  0x01=\"true\";0x00=\"false\"");
        println("  [-]>>>[-]<<[>>+<<[-]]>[>+<[-]]>[<<<+>>>[-]]<<< ");
      }
      else if(SBXOR->Down){ println();
        println("  LOGICAL EXCLUSIVE OR");
        println("  Performs a logical XOR operation to the next 2 cells");
        println("  Leaves pointer at current cell with the result");
        println("  Requires two cells to the right with the operands; which will be lost (0);");
        println("  and one more to the right as a temp variable; which will also be lost (0)");
        println("  0x01=\"true\";0x00=\"false\"");
        println("  [-]+>>>[-]<<[>>+<<[-]]>[>+<[-]]>-[<<<->>>[-]]<<< ");
      }

      else if(SBIFELSE->Down){
        println();
        println("  ================ IF THEN ELSE ================");
        println("  Implements an IF_THEN_ELSE statement");
        println("  Leaves pointer at current cell; containing 0");
        println("  Requires one cell to the right; leaving it in 0");
        println("  0x01=\"true\";0x00=\"false\"");
        println();
        println("   if(*p==A)");
        println("     THEN code");
        println("   else");
        println("     ELSE code");
        println();
        println("  Enter minus operator A times: ----------------");
        println("  >[-]+<[");
        println("  enter ELSE code here");
        println("  >-<[-]]>[");
        println("  enter THEN code here");
        println("  [-]]<");
        println("  ================ IF BLOCK END ================");
        println();
      }

      ResetFlechas();
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PageControl1Change(TObject *Sender)
{
  ResetFlechas();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::MenuItem6Click(TObject *Sender)
{
  ProgramTxt->CopyToClipboard();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MenuItem7Click(TObject *Sender)
{
  ProgramTxt->PasteFromClipboard();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MenuItem5Click(TObject *Sender)
{
  ProgramTxt->CutToClipboard();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MenuItem3Click(TObject *Sender)
{
 MemoSource1->Redo();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ProgramTxtEnter(TObject *Sender)
{
    EditProgram->Visible=true;
    Edit1->Caption="E&dit";
    EditProgram->Caption="&Edit";
    Edit1->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Panel4Enter(TObject *Sender)
{
    Edit1->Visible=true;
    EditProgram->Caption="E&dit";
    Edit1->Caption="&Edit";
    EditProgram->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Undo2Click(TObject *Sender)
{
 MemoSource1->Undo();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SelectAll3Click(TObject *Sender)
{
  MemoSource1->SelectAll();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Toggle(int linea){
  //MainForm->ProgramTxt->TempHighlightLineWithStyle(linea,STxtStBreakPnt);

  //int temp=bookmarks->IndexOf((void *)linea);
  //if (bookmarks==NULL)  bookmarks=new TList();
  if (!(bookmarks->Remove((void *)linea)+1))// si no lo enkontraste
    bookmarks->Add((void *)linea);
/*  else
    MainForm->ProgramTxt->ToggleImageAndTextStyle(STxtStBreakPnt);*/
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ProgramTxtClickGutter(TObject *Sender,
  int LinePos, int ImageIndex, TShiftState Shift){

  if(terminated && ProgramTxt->Lines->Count>=LinePos){
    /*caret.y=LinePos;
    caret.x=0;
    MemoSource1->CaretPoint=caret;
    int l=ProgramTxt->Lines->Strings[LinePos].Length();

    if (!(bookmarks->IndexOf((void *)LinePos)+1) && ProgramTxt->Text.Length() )
      print("~ ");
    else
      if (bookmarks->IndexOf((void *)LinePos)+1)
        if(ProgramTxt->Lines->Strings[LinePos].SubString(0,2)=="~ ")
          ProgramTxt->Lines->Strings[LinePos]=ProgramTxt->Lines->Strings[LinePos].SubString(3,l-1);
        else
          if ((l==1) &&(ProgramTxt->Lines->Strings[LinePos].SubString(0,1)=="~"))
            ProgramTxt->Lines->Strings[LinePos]="";
                                    */
    ProgramTxt->ToggleImageAndTextStyle(STxtStBreakPnt);
    Toggle(LinePos);
              /*
    caret.y=LinePos;
    caret.x=0;
    MemoSource1->CaretPoint=caret;*/
  }
    //MemoSource1->SetBookmark(1);  //Kuashio: asi pones el Instruction Pointer
    //MemoSource1->TempHighlightLine(LinePos,ProgramTxt->TextStyles->IndexOfName("BreakPoint"));
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormActivate(TObject *Sender)
{
  /*::Sleep(delay);
  if(Splash){
    delete Splash;
    Splash = NULL; tstrings
  }     */
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::WordWrap1Click(TObject *Sender)
{
  if(WordWrap1->Checked){
    WordWrap1->Checked=false;
    ProgramTxt->WordWrap=false;
  }else{
    WordWrap1->Checked=true;
    ProgramTxt->WordWrap=true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::KuashiosWebsite1Click(TObject *Sender)
{
  ShellExecute(0,0,"http://kuashio.blogspot.com/",0,0,4);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
  Application->HelpCommand(HELP_QUIT, 0);
  if (Run!=NULL)
    Run->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::comaClick(TObject *Sender)
{
  running=true;  // nueva proeba 4 de agosto!!!!!
  COMA();
  refresh();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::dotClick(TObject *Sender)
{                                           
  running=true;  // nueva proeba 4 de agosto!!!!!
  DOT();
  dot->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::LeftClick(TObject *Sender)
{                                                
  running=true;  // nueva proeba 4 de agosto!!!!!
  LEFT();
  refresh();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RightClick(TObject *Sender)
{
  running=true;  // nueva proeba 4 de agosto!!!!!
  RIGHT();
  refresh();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::plusClick(TObject *Sender)
{
  running=true;  // nueva proeba 4 de agosto!!!!!
  PLUS();
  refresh();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::minusClick(TObject *Sender)
{
  running=true;  // nueva proeba 4 de agosto!!!!!
  MINUS();
  refresh();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PrevClick(TObject *Sender)
{
  running=true;  // nueva proeba 4 de agosto!!!!!
  Next->Enabled=true;
  pc--;
  refresh();

  //MStep->Enabled=true;
  //SBStep->Enabled=true;
  //ProgramTxt->SetFocus();
  //ProgramTape->Cells[20][0]=ProgramTxt->MemoSource->CurLinePos;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::NextClick(TObject *Sender)
{

  running=true;  // nueva proeba 4 de agosto!!!!!
  Prev->Enabled=true;
  pc++;
  refresh();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EditJumpExit(TObject *Sender)
{
  if(EditJump->Text.Pos("-") || EditJump->Text.Pos("+") || !EditJump->Text.Length() )
    EditJump->Text=LastJump;
  if (EditJump->Value>MaxMem-1)EditJump->Value=MaxMem-1;
  if (EditJump->Value<0)EditJump->Value=0;
  LastJump=EditJump->Text;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EditSetExit(TObject *Sender)
{

  if(EditSet->Text.Pos("-") || EditSet->Text.Pos("+") || !EditSet->Text.Length() )
    EditSet->Text=LastSet;
  if (EditSet->Value>255)EditSet->Value=255;
  if (EditSet->Value<0)EditSet->Value=0;
  LastSet=EditSet->Text;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Button1Click(TObject *Sender)
{
  p=EditJump->Value;
  refresh();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Button2Click(TObject *Sender)
{
  MemoryArray[p]=EditSet->Value;
  refresh();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EditJumpBottomClick(TObject *Sender)
{
  if(!EditJump->Value)EditJump->Value=EditJump->MaxValue;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EditJumpTopClick(TObject *Sender)
{
  if(EditJump->Value==EditJump->MaxValue)EditJump->Value=0;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EditSetBottomClick(TObject *Sender)
{
  if(!EditSet->Value)EditSet->Value=EditSet->MaxValue;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EditSetTopClick(TObject *Sender)
{
  if(EditSet->Value==EditSet->MaxValue)EditSet->Value=0;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::BEnterCharClick(TObject *Sender)
{
  AnsiString temp;
  if(EditChar->Value==0){
    InputTxt->Text = InputTxt->Text + "\\0";
  }
  else{
    InputTxt->Text = InputTxt->Text + temp.sprintf("%c",(int)EditChar->Value);
  }
  InputTxt->SetFocus();
  InputTxt->SelStart=InputTxt->Text.Length();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EditCharExit(TObject *Sender)
{
  if(EditChar->Text.Pos("-") || EditChar->Text.Pos("+") || !EditChar->Text.Length() )
    EditChar->Text=LastChar1;
  if (EditChar->Value>255)EditChar->Value=255;
  if (EditChar->Value<0)EditChar->Value=0;
  LastChar1=EditChar->Text;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EditCharBottomClick(TObject *Sender)
{
  if(!EditChar->Value)EditChar->Value=EditChar->MaxValue;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EditCharTopClick(TObject *Sender)
{
  if(EditChar->Value==EditChar->MaxValue)EditChar->Value=0;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ProgramTxtChange(TObject *Sender)
{
  if (running)modified=true;
  MStep->Enabled=true;
  SBStep->Enabled=true;
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::OutputTxtEnter(TObject *Sender)
{
  if(!terminated)ProgramTxt->SetFocus();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::MakeExecutable1Click(TObject *Sender){
  char count;
  SBPauseClick(Sender);
  if(!ProgramTxt->Lines->GetText()[0]){
    MessageBox(Handle,"Write some code!","Program text empty!",MB_OK|MB_ICONERROR);
    return;
  }

  //load();

  DeleteFile((ExtractFilePath(Application->ExeName)+"/BFdotNet/vbf.bf").c_str());
  ProgramTxt->Lines->SaveToFile(ExtractFilePath(Application->ExeName)+"/BFdotNet/vbf.bf");
  DeleteFile((ExtractFilePath(Application->ExeName)+"/BFdotNet/vbf.exe").c_str());

  ShellExecute(NULL,NULL,"BFdotNet.exe","-s vbf.bf -e vbf.exe -w",
                (ExtractFilePath(Application->ExeName)+"BFdotNet").c_str(),4);

  if ( SaveEXE->Execute() )
  {
    AnsiString f=SaveEXE->FileName;

    // Options + OverwritePrompt = true, thus no need to check.
    //if(!(SaveEXE->FileName.Pos(".")))
    //  f+=".com";

    while (!CopyFile((ExtractFilePath(Application->ExeName)+"/BFdotNet/vbf.exe").c_str(),
          f.c_str(),FALSE)
          &&
        (MessageBox(Handle,"Failed. Retry must to the trick ;)","HEY",MB_RETRYCANCEL|MB_ICONQUESTION) == IDRETRY)
    );

    ShellExecute(Handle,"explore",ExtractFilePath(f).c_str(),ExtractFilePath(f).c_str(),ExtractFilePath(f).c_str(),4);
  }

}
//---------------------------------------------------------------------------


void __fastcall TMainForm::SBExeClick(TObject *Sender){
   MakeExecutable1Click(Sender);
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::VisualBrainFuckHelp1Click(TObject *Sender)
{
  HelpContents(Sender);
}
//---------------------------------------------------------------------------

