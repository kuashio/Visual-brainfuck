//---------------------------------------------------------------------------

#ifndef LoadThreadH
#define LoadThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>  
//---------------------------------------------------------------------------
class LoadThread : public TThread
{            
private:
protected:
  void __fastcall Execute();
public:
  bool __fastcall unbalanced();
  void __fastcall ShowWait();
  void __fastcall msg();
  void __fastcall askToClr();
  void __fastcall init();
  void __fastcall iteration();
  void __fastcall after();
  void __fastcall close();
  char quit, clearMem;

  __fastcall LoadThread(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
