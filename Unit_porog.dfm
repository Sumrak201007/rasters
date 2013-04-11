object Porog_form: TPorog_form
  Left = 599
  Top = 261
  Width = 173
  Height = 152
  Caption = 'Porog_form'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 8
    Width = 113
    Height = 13
    Caption = #1042#1074#1077#1076#1080#1090#1077' '#1087#1086#1088#1086#1075' (0..255)'
  end
  object MaxPorogEdit: TEdit
    Left = 24
    Top = 48
    Width = 121
    Height = 21
    TabOrder = 0
    Text = '100'
  end
  object BinarizeNowButton: TButton
    Left = 48
    Top = 80
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 1
    OnClick = BinarizeNowButtonClick
  end
  object MinPorogEdit: TEdit
    Left = 24
    Top = 24
    Width = 121
    Height = 21
    TabOrder = 2
    Text = '100'
  end
end
