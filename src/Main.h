//---------------------------------------------------------------------------
#ifndef MainH
#define MainH

#include "LoadThread.h"
#include "dccommon.hpp"
#include "dcmemo.hpp"
#include "dcstring.hpp"
#include "dcSyntax.hpp"
#include "dcsystem.hpp"
#include "RXSpin.hpp"
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <StdActns.hpp>
#include <StdCtrls.hpp>

#define MaxMem   30000
#define MaxCode 110000
//---------------------------------------------------------------------------
#include <sysutils.hpp>
#include <windows.hpp>
#include <messages.hpp>
#include <sysutils.hpp>
#include <classes.hpp>
#include <graphics.hpp>
#include <controls.hpp>
#include <forms.hpp>
#include <dialogs.hpp>
#include <stdctrls.hpp>
#include <buttons.hpp>
#include <extctrls.hpp>
#include <menus.hpp>
#include <Buttons.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <StdCtrls.hpp>
#include <Graphics.hpp>
#include <Grids.hpp>
#include <ActnList.hpp>
#include <StdActns.hpp>
#include <QRCtrls.hpp>
#include <QuickRpt.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include <ActnMan.hpp>
#include "dccommon.hpp"
#include "dcmemo.hpp"
#include "dcstring.hpp"
#include "dcSyntax.hpp"
#include "dcsystem.hpp"
#include "CSPIN.h"
#include "RXSpin.hpp"
/*#include "dccommon.hpp"
#include "dcmemo.hpp"
#include "dcSyntax.hpp"
#include "dcsystem.hpp"
#include "dcstring.hpp"*/
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:   
	TMainMenu *MainMenu;
	TMenuItem *FileNewItem;
	TMenuItem *FileOpenItem;
	TMenuItem *FileSaveItem;
	TMenuItem *FileSaveAsItem;
	TMenuItem *FilePrintItem;
	TMenuItem *FilePrintSetupItem;
	TMenuItem *FileExitItem;
	TMenuItem *HelpContentsItem;
	TMenuItem *HelpHowToUseItem;
	TMenuItem *HelpAboutItem;
	TStatusBar *StatusLine;
	TOpenDialog *OpenDialog;
	TSaveDialog *SaveDialog;
	TPrintDialog *PrintDialog;
	TPrinterSetupDialog *PrintSetupDialog;
	TPanel *SpeedBar;
	TSpeedButton *SpeedButton1;  // &New
	TSpeedButton *SpeedButton2;  // &Open...
	TSpeedButton *SpeedButton3;  // &Save
	TSpeedButton *SpeedButton4;  // &Paste
	TSpeedButton *SpeedButton11;
  TImage *Image1;
  TImage *Image2;
  TStringGrid *MemoryTape;
  TImage *Image3;
  TImage *Image4;
  TStringGrid *ProgramTape;
  TLabel *Label1;
  TLabel *Label2;
  TLabel *Label3;
  TGroupBox *GroupBox1;
  TImage *Image5;
  TImage *Image6;
  TRichEdit *InputTxt;
  TPopupMenu *PopupMenu1;
  TMenuItem *Undo1;
  TMenuItem *MenuItem1;
  TMenuItem *Cut1;
  TMenuItem *Copy1;
  TMenuItem *Paste1;
  TMenuItem *MenuItem2;
  TMenuItem *SelectAll1;
  TActionList *ActionList1;
  TEditCut *EditCut1;
  TEditCopy *EditCopy1;
  TEditPaste *EditPaste1;
  TEditSelectAll *EditSelectAll1;
  TEditUndo *EditUndo1;
  TLabel *Label4;
  TLabel *Label5;
  TSpeedButton *SBRun;
  TMenuItem *RunMenu;
  TMenuItem *MRun;
  TMenuItem *MStep;
  TMenuItem *MStop;
  TMenuItem *MReset;
  TSpeedButton *SBStep;
  TSpeedButton *SBPause;
  TSpeedButton *SBStop;
  TSpeedButton *SBReset;
  TPanel *Panel1;
  TPanel *Panel2;
  TPanel *Panel3;
  TPanel *Panel4;
  TPanel *Panel5;
  TPanel *Panel6;
  TSplitter *Splitter1;
  TSplitter *Splitter3;
  TRadioGroup *Display;
  TMenuItem *VisualBrainFuckHelp1;
  TMenuItem *Tools1;
  TMenuItem *TextEncoder1;
  TMenuItem *OokTranslator1;
  TPageControl *PageControl1;
  TTabSheet *TabSheet1;
  TTabSheet *TabSheet2;
  TSpeedButton *Flecha0;
  TSpeedButton *SBINPUT;
  TTabSheet *TabSheet3;
  TSpeedButton *Flecha3;
  TSpeedButton *Flecha2;
  TTabSheet *TabSheet4;
  TSpeedButton *Flecha1;
  TSpeedButton *SBMOV;
  TImage *Image7;
  TImage *Image8;
  TMenuItem *MPause;
  TMenuItem *CKTGenerator1;
  TMenuItem *N5;
  TMenuItem *KuashiosWebsite1;
  TImageList *ImageList1;
  TSpeedButton *SBIF;
  TSpeedButton *SBDUP;
  TSpeedButton *SBFLUSH;
  TSpeedButton *SBSWAP;
  TSpeedButton *SBMOVE;
  TSpeedButton *SBHW;
  TSpeedButton *SB666;
  TSpeedButton *SBASCII;
  TSpeedButton *SBCLR;
  TSpeedButton *SBADD;
  TSpeedButton *SBSUB;
  TSpeedButton *SBMUL;
  TSpeedButton *SBDIV;
  TSpeedButton *SpeedButton21;
  TSpeedButton *SBREV;
  TSpeedButton *SBBR;
  TSpeedButton *SBCLR0;
  TSaveDialog *SaveDialog1;
  TDCMemo *ProgramTxt;
  TSyntaxParser *Panzer;
  TPopupMenu *PopupMenu2;
  TMenuItem *MenuItem3;
  TMenuItem *MenuItem4;
  TMenuItem *MenuItem5;
  TMenuItem *MenuItem6;
  TMenuItem *MenuItem7;
  TMenuItem *MenuItem8;
  TMenuItem *MenuItem9;
  TMemoSource *MemoSource1;
  TMenuItem *Undo2;
  TMenuItem *EditProgram;
  TMenuItem *SelectAll3;
  TMenuItem *N7;
  TMenuItem *Paste2;
  TMenuItem *Copy2;
  TMenuItem *Cut2;
  TMenuItem *N8;
  TMenuItem *Undo3;
  TMenuItem *Undo4;
  TMenuItem *Edit1;
  TMenuItem *SelectAll4;
  TMenuItem *N9;
  TMenuItem *Paste3;
  TMenuItem *Copy3;
  TMenuItem *Cut3;
  TMenuItem *N10;
  TMenuItem *Undo5;
  TMenuItem *N2;
  TMenuItem *WordWrap1;
  TSpeedButton *SBCOM;
  TSpeedButton *SBOK;
  TSpeedButton *SBSEEK0;
  TSpeedButton *SBSEEK20;
  TSpeedButton *SBTOUPPER;
  TSpeedButton *SBTOLOWER;
  TSpeedButton *SBCHARTOINT;
  TTabSheet *Logic;
  TSpeedButton *Flecha4;
  TSpeedButton *SBNOT;
  TSpeedButton *SBAND;
  TSpeedButton *SBOR;
  TSpeedButton *SBXOR;
  TSpeedButton *SBIFELSE;
  TCheckBox *UseBP;
  TGroupBox *GroupBox2;
  TButton *Left;
  TButton *Right;
  TButton *plus;
  TButton *minus;
  TButton *coma;
  TButton *dot;
  TButton *Prev;
  TButton *Next;
  TButton *Button1;
  TButton *Button2;
  TRxSpinEdit *EditJump;
  TRxSpinEdit *EditSet;
  TLabeledEdit *pWatch;
  TMenuItem *Options1;
  TMenuItem *MakeExecutable1;
  TMenuItem *N6;
  TMenuItem *N11;
  TImage *Image9;
  TRxSpinEdit *EditChar;
  TButton *BEnterChar;
  TCheckBox *Animate;
  TRichEdit *OutputTxt;
  TImage *Image10;
  TImage *Image11;
  TSpeedButton *SBINTTOCHAR;
  TSaveDialog *SaveEXE;
  TCheckBox *IgnoreCR;
  TSpeedButton *SBExe;  // E&xit
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ShowHint(TObject *Sender);
	void __fastcall FileNew(TObject *Sender);
	void __fastcall FileOpen(TObject *Sender);
	void __fastcall FileSave(TObject *Sender);
	void __fastcall FileSaveAs(TObject *Sender);
	void __fastcall FilePrint(TObject *Sender);
	void __fastcall FilePrintSetup(TObject *Sender);
	void __fastcall FileExit(TObject *Sender);
	void __fastcall EditUndo(TObject *Sender);
	void __fastcall EditCut(TObject *Sender);
	void __fastcall EditCopy(TObject *Sender);
	void __fastcall EditPaste(TObject *Sender);
	void __fastcall HelpContents(TObject *Sender);
	void __fastcall HelpSearch(TObject *Sender);
	void __fastcall HelpHowToUse(TObject *Sender);
	void __fastcall HelpAbout(TObject *Sender);
  void __fastcall RadioGroup1Click(TObject *Sender);
  void __fastcall SBRunClick(TObject *Sender);
  void __fastcall SBPauseClick(TObject *Sender);
  void __fastcall SBStopClick(TObject *Sender);
  void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall TextEncoder1Click(TObject *Sender);
  void __fastcall ProgramTxtMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall PageControl1Change(TObject *Sender);
  void __fastcall MenuItem6Click(TObject *Sender);
  void __fastcall MenuItem7Click(TObject *Sender);
  void __fastcall MenuItem5Click(TObject *Sender);
  void __fastcall MenuItem3Click(TObject *Sender);
  void __fastcall ProgramTxtEnter(TObject *Sender);
  void __fastcall Panel4Enter(TObject *Sender);
  void __fastcall Undo2Click(TObject *Sender);
  void __fastcall SelectAll3Click(TObject *Sender);
  void __fastcall OokTranslator1Click(TObject *Sender);
  void __fastcall ProgramTxtClickGutter(TObject *Sender, int LinePos,
          int ImageIndex, TShiftState Shift);
  void __fastcall FormActivate(TObject *Sender);
  void __fastcall WordWrap1Click(TObject *Sender);
        void __fastcall KuashiosWebsite1Click(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall SBResetClick(TObject *Sender);
  void __fastcall comaClick(TObject *Sender);
  void __fastcall dotClick(TObject *Sender);
  void __fastcall LeftClick(TObject *Sender);
  void __fastcall RightClick(TObject *Sender);
  void __fastcall plusClick(TObject *Sender);
  void __fastcall minusClick(TObject *Sender);
  void __fastcall PrevClick(TObject *Sender);
  void __fastcall NextClick(TObject *Sender);
  void __fastcall EditJumpExit(TObject *Sender);
  void __fastcall EditSetExit(TObject *Sender);
  void __fastcall Button1Click(TObject *Sender);
  void __fastcall Button2Click(TObject *Sender);
  void __fastcall EditJumpBottomClick(TObject *Sender);
  void __fastcall EditJumpTopClick(TObject *Sender);
  void __fastcall EditSetBottomClick(TObject *Sender);
  void __fastcall EditSetTopClick(TObject *Sender);
  void __fastcall BEnterCharClick(TObject *Sender);
  void __fastcall EditCharBottomClick(TObject *Sender);
  void __fastcall EditCharExit(TObject *Sender);
  void __fastcall EditCharTopClick(TObject *Sender);
  void __fastcall SBStepClick(TObject *Sender);
  void __fastcall ProgramTxtChange(TObject *Sender);
  void __fastcall OutputTxtEnter(TObject *Sender);
        void __fastcall MakeExecutable1Click(TObject *Sender);
  void __fastcall SBExeClick(TObject *Sender);
  void __fastcall VisualBrainFuckHelp1Click(TObject *Sender);


private:
	AnsiString FFileName;
	bool FUpdating;
	int FDragOfs;
	bool FDragging;
	TTextAttributes *__fastcall CurrText(void);
	void __fastcall GetFontNames(void);
	void __fastcall SetFileName(const AnsiString FileName);
	void __fastcall CheckFileSave(void);
	//void __fastcall SetupRuler(void);
	//void __fastcall SetEditRect(void);
	//void __fastcall ShowHint(TObject *Sender);
  void __fastcall ResetFlechas(void);
  void __fastcall print(AnsiString ins);
  void __fastcall println();
  void __fastcall println(AnsiString ins);

  void __fastcall RIGHT();
  void __fastcall LEFT();
  void __fastcall PLUS();
  void __fastcall MINUS();
  void __fastcall COMA();
  void __fastcall DOT();
  void __fastcall OPEN();
  void __fastcall CLOSE();

  bool __fastcall checkModified();

  int __fastcall right(int ptr);
  int __fastcall left(int ptr);
  int __fastcall getLine(int charindex);
  int __fastcall unbalancedold();
  void __fastcall load();

  void __fastcall Toggle(int linea);


public:         // public user declarations
	virtual __fastcall TMainForm(TComponent* Owner);
  bool __fastcall isRunning();
  void __fastcall Step();
  void __fastcall refresh();
  void __fastcall InitReels();
  
  AnsiString InputBuffer;
  LoadThread *Load;


  unsigned char MemoryArray[MaxMem];
  char ProgramArray[MaxCode];
  int p;
  int pc;
  bool running,modified,terminated,force;
  int ColInfo[MaxCode];
  int LineInfo[MaxCode];
  bool virgo;
  TList *bookmarks;
};
//---------------------------------------------------------------------------
extern TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
