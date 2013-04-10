//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::OpenPictureButtonClick(TObject *Sender)
{
OpenPictureDialog1->Execute();
Graphics::TBitmap* raster = new Graphics::TBitmap();
raster->LoadFromFile(OpenPictureDialog1->FileName);
PretreatmentImage->Picture->Bitmap->Assign(raster);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ImageToDBButtonClick(TObject *Sender)

{   //max id
 /*
IBQuery1->SQL->Clear();
IBQuery1->SQL->Add("SELECT MAX (ID) FROM IMAGE_WITHOUT_PRETREATMENT");
Int max_id = StrToInt(DataSource1->DataSet->);
                                                 */
  IBTransaction1->Active = false;
  IBTransaction1->StartTransaction();
  IBQuery1->SQL->Clear();
  IBQuery1->SQL->Add("INSERT INTO IMAGE_WITHOUT_PRETREATMENT (ID,IMAGE) VALUES ('"+Edit1->Text+"',:pic)");
  IBQuery1->ParamByName("pic")->LoadFromFile(OpenPictureDialog1->FileName,ftBlob);
  IBQuery1->ExecSQL();
  IBTransaction1->Commit();

  ShowMessage("Изображение успешно сохранено");
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ImageFromDBButtonClick(TObject *Sender)
{

IBQuery1->SQL->Clear();
IBQuery1->SQL->Add("SELECT IMAGE FROM IMAGE_WITHOUT_PRETREATMENT WHERE ID='"+Edit1->Text+"'");

IBQuery1->Open();
   if(!IBQuery1->FieldByName("IMAGE")->IsNull){
        TStream *B1 = IBQuery1->CreateBlobStream(IBQuery1->FieldByName("IMAGE"), bmRead);
        TMemoryStream *M1 = new TMemoryStream();
        M1->CopyFrom(B1,B1->Size);
        M1->Position = 0;
        Graphics::TBitmap *bmp  = new Graphics::TBitmap();
        bmp->LoadFromStream(M1);
        delete(M1);
        delete(B1);

        PretreatmentImage->Picture->Bitmap = bmp;
        PretreatmentImage->Refresh();
        IBQuery1->Close();
}
}
//---------------------------------------------------------------------------







void __fastcall TFormMain::FormCreate(TObject *Sender)
{
PretreatmentImage->AutoSize = true;
}
//---------------------------------------------------------------------------

