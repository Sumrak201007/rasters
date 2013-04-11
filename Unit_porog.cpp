//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit_porog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPorog_form *Porog_form;
//---------------------------------------------------------------------------
__fastcall TPorog_form::TPorog_form(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPorog_form::Button1Click(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------
