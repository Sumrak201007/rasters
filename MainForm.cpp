//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
#include "Unit_porog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
TPorog_form *Porog_form;
unsigned char *my_pict;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
// ����������� ������
int otsuThreshold(unsigned char *image, int size)
{
  // ��������� ����������� � ������������ ������� ���� ��������
  int min = image[0];
  int max = image[0];
  for (int i = 1; i < size; i++)
  {
    int value = image[i];
    if (value < min)
      min = value;
    if (value > max)
      max = value;
  }

  int histSize = max - min + 1;
  int* hist = new int[histSize];
  // �������� ����������� ������
  for (int t = 0; t < histSize; t++)
    hist[t] = 0;
  //�������� ������ ��������� �����������
  for (int i = 0; i < size; i++)
    hist[image[i] - min]++;
  // ��� ��������������� �����:
  int m = 0; // m - ����� ����� ���� ��������� �����������, ����������� �� ��������� �� ��������
  int n = 0; // n - ����� ����� ���� ��������� �����������
  for (int t = 0; t <= max - min; t++)
  {
    m += t * hist[t];
    n += hist[t];
  }
  float maxSigma = -1; // ������������ �������� ������������ ���������
  int threshold = 0; // �����, ��������������� maxSigma
  int alpha1 = 0; // ����� ����� ���� ��������� ����������� ��� ������ 1
  int beta1 = 0; // ����� ����� ���� ��������� ����������� ��� ������ 1, ����������� �� ��������� �� ��������
  // ���������� alpha2 �� �����, �.�. ��� ����� m - alpha1
  // ���������� beta2 �� �����, �.�. ��� ����� n - alpha1
  // t ����������� �� ���� ��������� ��������� ������
  for (int t = 0; t < max - min; t++)
  {
    alpha1 += t * hist[t];
    beta1 += hist[t];
    // ������� ����������� ������ 1.
    float w1 = (float)beta1 / n;
    //w2 �� �����, �.�. ��� ����� 1 - w1
    // a = a1 - a2, ��� a1, a2 - ������� �������������� ��� ������� 1 � 2
    float a = (float)alpha1 / beta1 - (float)(m - alpha1) / (n - beta1);
    // ������� sigma
    float sigma = w1 * (1 - w1) * a * a;
    // ���� sigma ������ ������� ������������, �� ��������� maxSigma � �����
    if (sigma > maxSigma)
    {
      maxSigma = sigma;
      threshold = t;
    }
  }
  //����� ������������ �� min, � �� �� ����
  threshold += min;
  //����� ��������, ���������� ���
  return threshold;
}
//------------------------------------------------------------------------------

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

  ShowMessage("����������� ������� ���������");
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
typedef unsigned char imageInt; //��� �������� ������������ ����������� - 8 ��� ��� ����� = 0..255
// ����������� ������ ������� ����

void __fastcall TFormMain::BinarizeButtonClick(TObject *Sender)
{
  Graphics::TBitmap *b = PretreatmentImage->Picture->Bitmap;
my_pict = new unsigned char [b->Width*b->Height];
for (int i=0;i<=b->Width-1;i++)
for (int j=0;j<=b->Height-1;j++)

/*my_pict[i*b->Width+j]=byte(PretreatmentImage->Picture->Bitmap->Canvas->Pixels[i][j]);
for(int i=0; i<256; i++) g[i]=0;
for(int i=0; i<b->Width-1; i++)  */

//for(int j=0; j<b->Height-1; j++)  g[byte(PretreatmentImage->Picture->Bitmap->Canvas->Pixels[i][j])]++;


  PretreatmentImage->Picture->Bitmap->Assign(PretreatmentImage->Picture->Bitmap);
  //Graphics::TBitmap *b = PretreatmentImage->Picture->Bitmap;
  int porog = otsuThreshold(my_pict,b->Width*b->Height);
  for (int i=0;i<=PretreatmentImage->Width-1;i++)
  for (int j=0;j<=PretreatmentImage->Height-1;j++)
  if (byte(PretreatmentImage->Picture->Bitmap->Canvas->Pixels[i][j])<=porog)
     PretreatmentImage->Picture->Bitmap->Canvas->Pixels[i][j]=clBlack;
  else
     PretreatmentImage->Picture->Bitmap->Canvas->Pixels[i][j]=clWhite;
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::Button1Click(TObject *Sender)
{
  PretreatmentImage->Picture->Bitmap->Assign(PretreatmentImage->Picture->Bitmap);
  int porog;
  Porog_form->ShowModal();
  porog=StrToInt(Porog_form->Edit1->Text);
  for (int i=0;i<=PretreatmentImage->Width-1;i++)
  for (int j=0;j<=PretreatmentImage->Height-1;j++)
  if (byte(PretreatmentImage->Picture->Bitmap->Canvas->Pixels[i][j])<=porog)
    PretreatmentImage->Picture->Bitmap->Canvas->Pixels[i][j]=clBlack;
  else
    PretreatmentImage->Picture->Bitmap->Canvas->Pixels[i][j]=clWhite;

}
//---------------------------------------------------------------------------

