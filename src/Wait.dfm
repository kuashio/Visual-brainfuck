object PleaseWait: TPleaseWait
  Left = 286
  Top = 165
  BorderStyle = bsDialog
  Caption = 'Pre-Processor'
  ClientHeight = 97
  ClientWidth = 350
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCloseQuery = FormCloseQuery
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 350
    Height = 97
    Align = alClient
    BevelInner = bvLowered
    TabOrder = 0
    object Label1: TLabel
      Left = 5
      Top = 9
      Width = 329
      Height = 16
      Alignment = taCenter
      AutoSize = False
      Caption = 'Please Wait...'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Bar: TCGauge
      Left = 11
      Top = 31
      Width = 327
      Height = 27
      ForeColor = clNavy
    end
    object BCancel: TButton
      Left = 131
      Top = 65
      Width = 75
      Height = 25
      Cancel = True
      Caption = 'Cancel'
      TabOrder = 0
      OnClick = BCancelClick
    end
  end
end
