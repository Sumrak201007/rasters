//---------------------------------------------------------------------------

#ifndef Unit_porogH
#define Unit_porogH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TPorog_form : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TEdit *MaxPorogEdit;
        TButton *BinarizeNowButton;
        TEdit *MinPorogEdit;
        void __fastcall BinarizeNowButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TPorog_form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPorog_form *Porog_form;
//---------------------------------------------------------------------------
#endif
