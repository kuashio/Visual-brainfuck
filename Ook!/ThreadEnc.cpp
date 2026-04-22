//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#include <stdlib.h>
#pragma hdrstop

#include "ThreadEnc.h"
#include "main.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TEncode::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TEncode::TEncode(bool CreateSuspended)
  : TThread(CreateSuspended)
{
  this->FreeOnTerminate=true;
}
//---------------------------------------------------------------------------

char buffIn[100000], buffOut[150000];
short j, isBF;
int Trunc;
unsigned long i, outlen, lastLine=1;
int f;
char *pointer, temp[11];

//---------------------------------------------------------------------------
void __fastcall TEncode::Execute()
{
  lastLine=1;
  isBF=false;
  Trunc=false;
  outlen=1;
  j=0;
  try{
    Synchronize(init);

    if (isBF)
      strcpy(buffOut,"Ook! Code:\n");
    else{
      strcpy(buffOut,"brainfuck Code:\n");
      pointer=buffIn+i-1;
    }
    while(!Trunc && i<(unsigned)f&&(!this->Terminated)){
      Synchronize(updateBar);
      if(isBF){
        j=(char)buffIn[i];
        switch(j){
          case '>':strcat(buffOut,"Ook. Ook? "); outlen+=10; break;
          case '<':strcat(buffOut,"Ook? Ook. "); outlen+=10; break;
          case '+':strcat(buffOut,"Ook. Ook. "); outlen+=10; break;
          case '-':strcat(buffOut,"Ook! Ook! "); outlen+=10; break;
          case ',':strcat(buffOut,"Ook. Ook! "); outlen+=10; break;
          case '.':strcat(buffOut,"Ook! Ook. "); outlen+=10; break;
          case '[':strcat(buffOut,"Ook! Ook? "); outlen+=10; break;
          case ']':strcat(buffOut,"Ook? Ook! "); outlen+=10; break;
        }
        i++;
      }
      else{
        strncpy(temp,pointer,9);
        temp[10]='\0';
        if      (!strcmp(temp,"Ook. Ook?")){strcat(buffOut,">"); outlen++;}
        else if (!strcmp(temp,"Ook? Ook.")){strcat(buffOut,"<"); outlen++;}
        else if (!strcmp(temp,"Ook. Ook.")){strcat(buffOut,"+"); outlen++;}
        else if (!strcmp(temp,"Ook! Ook!")){strcat(buffOut,"-"); outlen++;}
        else if (!strcmp(temp,"Ook. Ook!")){strcat(buffOut,","); outlen++;}
        else if (!strcmp(temp,"Ook! Ook.")){strcat(buffOut,"."); outlen++;}
        else if (!strcmp(temp,"Ook! Ook?")){strcat(buffOut,"["); outlen++;}
        else if (!strcmp(temp,"Ook? Ook!")){strcat(buffOut,"]"); outlen++;}
        pointer+=10;
        pointer=strstr(pointer,"Ook");
        //pointer=buffIn+i-1;
        i=pointer-buffIn;

      }
      if (outlen>100000)
        Trunc=1;

      if(outlen-lastLine>50){     // "word wrapping"
        lastLine=outlen;
        strcat(buffOut,"\n");
      }
    }
    if(Trunc){
      strcat(buffOut,"\nWARNING: Truncated because size limit was exceeded!");
      MessageBox(NULL,
      "The resulting code has been truncated because the size limit was exceeded."
      ,"Warning!",MB_OK|MB_ICONWARNING);
    }
    if(this->Terminated){
      strcat(buffOut,"\nWARNING: Truncated because of termination!");
      MessageBox(NULL,
      "The resulting code has been truncated because of thread termination."
      ,"Warning!",MB_OK|MB_ICONWARNING);
    }
    Synchronize(finish);
  }
  __finally{}
}

//---------------------------------------------------------------------------

void __fastcall TEncode::init(){
  try{
    f=MainForm->Mensaje->Text.Length();
    strcpy(buffIn,MainForm->Mensaje->Text.c_str());
    MainForm->Salida->Clear();
    MainForm->Bar->MaxValue=f+1;
    if(!(i=MainForm->Mensaje->Text.Pos("Ook")))
      isBF=true;
  }
  __finally{}
}

//---------------------------------------------------------------------------

void __fastcall TEncode::updateBar(){
  try{
    MainForm->Bar->Progress=i;
  }
  __finally{}
}

//---------------------------------------------------------------------------

void __fastcall TEncode::finish(){
  try{
  strcat(buffOut,"\nTranslated by Kuashio");
  MainForm->Salida->Text=buffOut;
  MainForm->Bar->Progress=i+1;
  }
  __finally{}
}
//---------------------------------------------------------------------------
