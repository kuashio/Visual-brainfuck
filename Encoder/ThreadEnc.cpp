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

int f;            //length
char buffIn[100000], buffOut[150000], firstTime=true;
short j;
int Trunc=0;
unsigned long i, outlen=1, lastLine=1;

void __fastcall TEncode::Execute()
{
  try{
    firstTime=true;
    Trunc=false;
    outlen=1;
    lastLine=1;
    j=0;
    Synchronize(init);
    for(i=0;(!Trunc && i<(unsigned)f&&(!this->Terminated));i++){
      Synchronize(updateBar);

      if((!Trunc)&&(buffIn[i]==13)){
        if(j==10){
          strcat(buffOut,".");
          outlen++;
        }
        else{
          if (!firstTime) strcat(buffOut,"[-]");
          strcat(buffOut,"++++++++++.");
          j=10;
          outlen+=14;
          i++;
        }
      }
      else{
        if((!Trunc) && (buffIn[i]!=10)){
          unsigned char sep = abs(buffIn[i]-j);  // calculate separation between last an current chars
          if(sep>16){
            unsigned char introot, k;
            float root;
            root=sqrt(sep);
            introot=(int)(root+0.5);

            strcat(buffOut,">");
            for (k=0; k<introot;k++){
              strcat(buffOut,"+");
            }
            strcat(buffOut,"[<");

            if(j<buffIn[i]){
              for (k=0; k<introot;k++){
                strcat(buffOut,"+");
              }
              j+=introot*introot;
              if((int)(2*root+0.5)>(2*introot)){
                strcat(buffOut,"+");
                j+=introot;
                outlen++;
              }
            }
            else{
              for (k=0; k<introot;k++){
                strcat(buffOut,"-");
              }
              j-=introot*introot;
              if((int)(2*root+0.5)>(2*introot)){
                strcat(buffOut,"-");
                j-=introot;
                outlen++;
              }
            }
            strcat(buffOut,">-]<");
            outlen+=2*introot+7;
          }

          while (j!=buffIn[i]){
            if(j<buffIn[i]){
              strcat(buffOut,"+");
              j++;
            }
            else{
              strcat(buffOut,"-");
              j--;
            }
            outlen++;
          }
          if (outlen>100000){
            Trunc=1;
          }
          if(j!=13){
           strcat(buffOut,".");
           outlen++;
          }
        }
      }
      j=(char)buffIn[i];
      /*if (Trunc){
        i=(unsigned long)MainForm->Mensaje->Text.Length();
      }        */
      firstTime=false;
      if(outlen-lastLine>40){     // "word wrapping"
        lastLine=outlen;
        strcat(buffOut,"\n");
      }

    }
    //MainForm->Bar2->Position=i+1;
    if(Trunc){
      strcat(buffOut,"\nWARNING: Truncated because size limit was exceeded!");
      MessageBox(NULL,
      "The resulting brainfuck code has been truncated because the size limit was exceeded."
      ,"Warning!",MB_OK|MB_ICONWARNING);
    }
    if(this->Terminated){
      strcat(buffOut,"\nWARNING: Truncated because of termination!");
      MessageBox(NULL,
      "The resulting brainfuck code has been truncated because of thread termination."
      ,"Warning!",MB_OK|MB_ICONWARNING);
    }
    Synchronize(finish);
  }
  __finally{
  }

}
//---------------------------------------------------------------------------

void __fastcall TEncode::init(){
  try{
    strcpy(buffIn,MainForm->Mensaje->Text.c_str());
    strcpy(buffOut,"brainfuck Code:\n>[-]<[-]");
    f=MainForm->Mensaje->Text.Length();
    MainForm->Salida->Clear();
    MainForm->Bar->MaxValue=f+1;
  }
  __finally{}
}
//---------------------------------------------------------------------------

void __fastcall TEncode::finish(){
  try{
    MainForm->Bar->Progress=i+1;
    strcat(buffOut,"\nEncoded by Kuashio");
    MainForm->Salida->Text = buffOut;
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


