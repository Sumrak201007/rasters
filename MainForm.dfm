object FormMain: TFormMain
  Left = 290
  Top = 134
  Width = 874
  Height = 505
  Caption = 'Merging raster'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object PretreatmentPageControl: TPageControl
    Left = 0
    Top = 0
    Width = 858
    Height = 467
    ActivePage = TabSheet1
    Align = alClient
    TabIndex = 0
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = #1055#1086#1076#1075#1086#1090#1086#1074#1082#1072' '#1080#1079#1086#1073#1088#1072#1078#1077#1085#1080#1103
      object ScrollBox1: TScrollBox
        Left = 200
        Top = 0
        Width = 649
        Height = 433
        TabOrder = 0
        object PretreatmentImage: TImage
          Left = 0
          Top = 0
          Width = 105
          Height = 105
        end
      end
      object Save_LoadGroupBox: TGroupBox
        Left = 0
        Top = 0
        Width = 193
        Height = 145
        Caption = #1057#1086#1093#1088#1072#1085#1077#1085#1080#1077' '#1080' '#1079#1072#1075#1088#1091#1079#1082#1072
        TabOrder = 1
        object OpenPictureButton: TButton
          Left = 8
          Top = 16
          Width = 177
          Height = 25
          Caption = #1047#1072#1075#1088#1091#1079#1082#1072' '#1080#1079#1086#1073#1088#1072#1078#1077#1085#1080#1103' '#1089' '#1076#1080#1089#1082#1072
          TabOrder = 0
          OnClick = OpenPictureButtonClick
        end
        object ImageToDBButton: TButton
          Left = 8
          Top = 80
          Width = 177
          Height = 25
          Caption = #1057#1086#1093#1088#1072#1085#1077#1085#1080#1077' '#1080#1079#1086#1073#1088#1072#1078#1077#1085#1080#1103' '#1074' '#1041#1044
          TabOrder = 1
          OnClick = ImageToDBButtonClick
        end
        object ImageFromDBButton: TButton
          Left = 8
          Top = 48
          Width = 177
          Height = 25
          Caption = #1047#1072#1075#1088#1091#1079#1082#1072' '#1080#1079#1086#1073#1088#1072#1078#1077#1085#1080#1103' '#1080#1079' '#1041#1044
          TabOrder = 2
          OnClick = ImageFromDBButtonClick
        end
        object Edit1: TEdit
          Left = 8
          Top = 112
          Width = 177
          Height = 21
          TabOrder = 3
          Text = '1'
        end
      end
      object PretreatmentProcessingGroupBox: TGroupBox
        Left = 0
        Top = 152
        Width = 193
        Height = 145
        Caption = #1055#1088#1077#1076#1074#1072#1088#1080#1090#1077#1083#1100#1085#1072#1103' '#1086#1073#1088#1072#1073#1086#1090#1082#1072
        TabOrder = 2
        object BinarizeButton: TButton
          Left = 8
          Top = 16
          Width = 177
          Height = 25
          Caption = #1041#1080#1085#1072#1088#1080#1079#1072#1094#1080#1103' ('#1072#1074#1090#1086')'
          TabOrder = 0
          OnClick = BinarizeButtonClick
        end
        object Button1: TButton
          Left = 8
          Top = 48
          Width = 177
          Height = 25
          Caption = #1041#1080#1085#1072#1088#1080#1079#1072#1094#1080#1103' ('#1088#1091#1095#1085#1072#1103')'
          TabOrder = 1
          OnClick = Button1Click
        end
        object FindColorButton: TButton
          Left = 8
          Top = 80
          Width = 177
          Height = 25
          Caption = #1042#1099#1076#1077#1083#1077#1085#1080#1077
          TabOrder = 2
          OnClick = FindColorButtonClick
        end
      end
      object FiltrationButton: TButton
        Left = 8
        Top = 264
        Width = 177
        Height = 25
        Caption = #1057#1075#1083#1072#1078#1080#1074#1072#1085#1080#1077
        TabOrder = 3
        OnClick = FiltrationButtonClick
      end
    end
  end
  object OpenPictureDialog1: TOpenPictureDialog
    Left = 824
    Top = 152
  end
  object DataSource1: TDataSource
    Left = 824
    Top = 120
  end
  object IBDatabase1: TIBDatabase
    Connected = True
    DatabaseName = 'MERGING_RASTER.FDB'
    Params.Strings = (
      'user_name=sysdba'
      'password=masterkey')
    LoginPrompt = False
    DefaultTransaction = IBTransaction1
    IdleTimer = 0
    SQLDialect = 3
    TraceFlags = []
    Left = 824
    Top = 24
  end
  object IBQuery1: TIBQuery
    Database = IBDatabase1
    Transaction = IBTransaction1
    BufferChunks = 1000
    CachedUpdates = False
    Left = 824
    Top = 88
  end
  object IBTransaction1: TIBTransaction
    Active = False
    DefaultDatabase = IBDatabase1
    AutoStopAction = saNone
    Left = 824
    Top = 56
  end
end
