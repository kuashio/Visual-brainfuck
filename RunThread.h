//---------------------------------------------------------------------------

#ifndef RunThreadH
#define RunThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class RunThread : public TThread
{
private:                       
  void __fastcall refresh();
  void __fastcall init();
  void __fastcall stop();
  void __fastcall step();
protected:
  void __fastcall Execute();
public:
  __fastcall RunThread(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
