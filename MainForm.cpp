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
// Определение порога
int otsuThreshold(unsigned char *image, int size)
{
  // Посчитаем минимальную и максимальную яркость всех пикселей
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
  // Заполним гистограмму нулями
  for (int t = 0; t < histSize; t++)
    hist[t] = 0;
  //вычислим высоту элементов гистограммы
  for (int i = 0; i < size; i++)
    hist[image[i] - min]++;
  // два вспомогательных числа:
  int m = 0; // m - сумма высот всех элементов гистограммы, домноженных на положение их середины
  int n = 0; // n - сумма высот всех элементов гистограммы
  for (int t = 0; t <= max - min; t++)
  {
    m += t * hist[t];
    n += hist[t];
  }
  float maxSigma = -1; // Максимальное значение межклассовой дисперсии
  int threshold = 0; // Порог, соответствующий maxSigma
  int alpha1 = 0; // Сумма высот всех элементов гистограммы для класса 1
  int beta1 = 0; // Сумма высот всех элементов гистограммы для класса 1, домноженных на положение их середины
  // Переменная alpha2 не нужна, т.к. она равна m - alpha1
  // Переменная beta2 не нужна, т.к. она равна n - alpha1
  // t пробегается по всем возможным значениям порога
  for (int t = 0; t < max - min; t++)
  {
    alpha1 += t * hist[t];
    beta1 += hist[t];
    // Считаем вероятность класса 1.
    float w1 = (float)beta1 / n;
    //w2 не нужна, т.к. она равна 1 - w1
    // a = a1 - a2, где a1, a2 - средние арифметические для классов 1 и 2
    float a = (float)alpha1 / beta1 - (float)(m - alpha1) / (n - beta1);
    // считаем sigma
    float sigma = w1 * (1 - w1) * a * a;
    // Если sigma больше текущей максимальной, то обновляем maxSigma и порог
    if (sigma > maxSigma)
    {
      maxSigma = sigma;
      threshold = t;
    }
  }
  //порог отсчитывался от min, а не от нуля
  threshold += min;
  //порог посчитан, возвращаем его
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
typedef unsigned char imageInt; //тип пикселей полутонового изображения - 8 бит без знака = 0..255
// Определение порога методом Отсу

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

