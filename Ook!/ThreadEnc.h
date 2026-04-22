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
  void __fastcall TEncode::init();    
  void __fastcall TEncode::updateBar();
  void __fastcall TEncode::finish();
};
//---------------------------------------------------------------------------
#endif
