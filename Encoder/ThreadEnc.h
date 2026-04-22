//---------------------------------------------------------------------------

#ifndef ThreadEncH
#define ThreadEncH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class TEncode : public TThread
{
private:
protected:
  void __fastcall Execute();
public:
  __fastcall TEncode(bool CreateSuspended);
  void __fastcall init();    
  void __fastcall updateBar();
  void __fastcall finish();
};
//---------------------------------------------------------------------------
#endif
