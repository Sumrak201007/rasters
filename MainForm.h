//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ExtDlgs.hpp>
#include <DB.hpp>
#include <IBCustomDataSet.hpp>
#include <IBDatabase.hpp>
#include <IBQuery.hpp>
#include <DBCtrls.hpp>
#include <ADODB.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
        TPageControl *PretreatmentPageControl;
        TTabSheet *TabSheet1;
        TOpenPictureDialog *OpenPictureDialog1;
        TButton *OpenPictureButton;
        TButton *ImageToDBButton;
        TDataSource *DataSource1;
        TIBDatabase *IBDatabase1;
        TIBQuery *IBQuery1;
        TIBTransaction *IBTransaction1;
        TEdit *Edit1;
        TButton *ImageFromDBButton;
        TScrollBox *ScrollBox1;
        TImage *PretreatmentImage;
        TGroupBox *Save_LoadGroupBox;
        TGroupBox *PretreatmentProcessingGroupBox;
        TButton *BinarizeButton;
        void __fastcall OpenPictureButtonClick(TObject *Sender);
        void __fastcall ImageToDBButtonClick(TObject *Sender);
        void __fastcall ImageFromDBButtonClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall BinarizeButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
