//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
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
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <ActnList.hpp>
#include <ActnMan.hpp>
#include <StdActns.hpp>
#include "CGAUGES.h"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:
        TLabel *Label1;
        TLabel *Label2;
        TButton *Button1;
  TLabel *Label3;
  TRichEdit *Mensaje;
  TRichEdit *Salida;
  TPopupMenu *PopupMenu1;
  TActionList *ActionList1;
  TEditCut *EditCut1;
  TAction *Action1;
  TEditCopy *EditCopy1;
  TEditPaste *EditPaste1;
  TEditSelectAll *EditSelectAll1;
  TEditUndo *EditUndo1;
  TEditDelete *EditDelete1;
  TMenuItem *N2;
  TMenuItem *Paste1;
  TMenuItem *Copy1;
  TMenuItem *Cut1;
  TMenuItem *N3;
  TMenuItem *Undo1;
  TMenuItem *Delete1;
  TMenuItem *SelectAll1;
  TButton *Button2;
  TCGauge *Bar;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall resize(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall finThread(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:        // private user declarations
public:         // public user declarations
	virtual __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
