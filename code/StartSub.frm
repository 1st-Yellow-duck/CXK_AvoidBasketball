VERSION 5.00
Object = "{6BF52A50-394A-11D3-B153-00C04F79FAA6}#1.0#0"; "wmp.dll"
Begin VB.Form StartSub 
   Caption         =   "��Һ�"
   ClientHeight    =   6270
   ClientLeft      =   120
   ClientTop       =   465
   ClientWidth     =   11175
   Icon            =   "StartSub.frx":0000
   LinkTopic       =   "Form1"
   Picture         =   "StartSub.frx":000C
   ScaleHeight     =   6270
   ScaleWidth      =   11175
   StartUpPosition =   3  '����ȱʡ
   Begin VB.CheckBox noSoundC 
      Caption         =   "����"
      Height          =   255
      Left            =   9360
      TabIndex        =   8
      Top             =   0
      Width           =   735
   End
   Begin VB.CommandButton settingsB 
      Caption         =   "��Ϸ����"
      Height          =   495
      Left            =   10200
      TabIndex        =   7
      Top             =   5280
      Width           =   975
   End
   Begin VB.CommandButton ExitGameB 
      Caption         =   "�˳���Ϸ"
      Height          =   495
      Left            =   9840
      TabIndex        =   6
      Top             =   5760
      Width           =   1335
   End
   Begin VB.CommandButton StartGameShoot 
      Caption         =   "    �������伦     (������,������bug)"
      Height          =   495
      Left            =   240
      TabIndex        =   5
      Top             =   4560
      Width           =   1815
   End
   Begin VB.CheckBox bgFlash 
      Caption         =   "��̬����"
      Height          =   255
      Left            =   10080
      TabIndex        =   4
      Top             =   0
      Width           =   1095
   End
   Begin VB.Timer bgCtrl 
      Enabled         =   0   'False
      Interval        =   1
      Left            =   5400
      Top             =   1320
   End
   Begin VB.Timer ReLoad 
      Enabled         =   0   'False
      Interval        =   1
      Left            =   0
      Top             =   5880
   End
   Begin VB.CommandButton Help_b 
      Caption         =   "��Ϸ����"
      Height          =   375
      Left            =   1920
      TabIndex        =   3
      Top             =   5880
      Width           =   1695
   End
   Begin VB.CommandButton ccc 
      Caption         =   "������ʼ��Ϸ(������)��"
      Height          =   495
      Left            =   4440
      TabIndex        =   2
      Top             =   4680
      Width           =   2055
   End
   Begin VB.Timer nbaStarT 
      Enabled         =   0   'False
      Interval        =   10000
      Left            =   960
      Top             =   720
   End
   Begin VB.Timer TitleCtrl 
      Interval        =   1000
      Left            =   3600
      Top             =   0
   End
   Begin WMPLibCtl.WindowsMediaPlayer nbaStar 
      Height          =   855
      Left            =   480
      TabIndex        =   1
      Top             =   360
      Visible         =   0   'False
      Width           =   1335
      URL             =   ""
      rate            =   1
      balance         =   0
      currentPosition =   0
      defaultFrame    =   ""
      playCount       =   1
      autoStart       =   -1  'True
      currentMarker   =   0
      invokeURLs      =   -1  'True
      baseURL         =   ""
      volume          =   50
      mute            =   0   'False
      uiMode          =   "full"
      stretchToFit    =   0   'False
      windowlessVideo =   0   'False
      enabled         =   -1  'True
      enableContextMenu=   -1  'True
      fullScreen      =   0   'False
      SAMIStyle       =   ""
      SAMILang        =   ""
      SAMIFilename    =   ""
      captioningID    =   ""
      enableErrorDialogs=   0   'False
      _cx             =   2355
      _cy             =   1508
   End
   Begin VB.Image Help_MainSub 
      Height          =   375
      Left            =   1920
      Top             =   5880
      Width           =   1695
   End
   Begin VB.Label ScorePrinter 
      BackColor       =   &H00FF8080&
      BeginProperty Font 
         Name            =   "΢���ź�"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   255
      Left            =   3720
      TabIndex        =   0
      Top             =   5520
      Width           =   1095
   End
   Begin VB.Image StartGameAvoid 
      Height          =   630
      Left            =   1320
      Picture         =   "StartSub.frx":1646E
      Top             =   5160
      Width           =   8340
   End
End
Attribute VB_Name = "StartSub"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim StartFrameCount As Integer
Dim TrueDebugMode As Boolean
Dim TrueLevel As Integer
Dim TrueMaxScore As Integer
Dim TrueLastScore As Integer
Dim TrueSoundMode As Integer

Private Function ChangeOptions()
 Kill App.Path & "\res\options.txt" 'ɾ���ϵ������ļ�
Level = CStr(TrueLevel)
If TrueDebugMode = False Then
 DebugMode = "False"
ElseIf TrueDebugMode = True Then
 DebugMode = "True"
End If
MaxScore = CStr(TrueMaxScore)
SoundMode = Val(TrueSoundMode)
Open App.Path & "\res\options.txt" For Output As #1
  Print #1, Level '�ؿ�
  Print #1, DebugMode '����ģʽ
  Print #1, MaxScore '��߷�
  Print #1, SoundMode '��������
Close #1
End Function

Private Sub ExitGameB_Click()
End
End Sub

Private Sub form_load()
'===========================
Dim Level As String, DebugMode As String, MaxScore As String, LastScore As String
TrueLevel = 1
TrueDebugMode = False
TrueMaxScore = 0
TrueLastScore = 0
'====================���浵������===============
NormalStart:
If Dir(App.Path & "\res\options.txt") = "" Then
 Open App.Path & "\res\options.txt" For Output As #2
  Print #2, "1" '�ؿ�
  Print #2, "False" '����ģʽ
  Print #2, "0" '��߷�
  Print #2, "0"
 Close #2
End If
On Error GoTo ResetApp
Open App.Path & "\res\options.txt" For Input As #3
 Line Input #3, Level
 Line Input #3, DebugMode
 Line Input #3, MaxScore
 Line Input #3, SoundMode
Close #3
 
 TrueLevel = Val(Level)
 TrueMaxScore = Val(MaxScore)
 If DebugMode = "f" Or DebugMode = "F" Or DebugMode = "false" Then DebugMode = "False"
 If DebugMode = "t" Or DebugMode = "T" Or DebugMode = "true" Then DebugMode = "True"
 If Level = "" Then Level = 1: TrueLevel = 1
 If MaxScore = "" Then Level = 1: TrueMaxScore = 1
 If DebugMode = "False" Then
  TrueDebugMode = False
 ElseIf DebugMode = "True" Then
  TrueDebugMode = True
 End If
 TrueSoundMode = Val(SoundMode)
 ChangeOptions

'MsgBox "����ģʽ=" & Str(TrueDebugMode) & "�ؿ�=" & Str(TrueLevel) & "��߷�=" & Str(TrueMaxScore) & "��ǰ��" & Str(TrueLastScore), okonly, "DeveloperDebugMode"
'End
'����ߴ�left480*top480
'�������ߴ�left960*top1320
'==============================����ģʽ����============================
If TrueDebugMode = True Then
bgFlash.Height = 375
bgFlash.Width = 1815
bgFlash.Left = 9360
bgFlash.Caption = "  ���ö�̬����   (�ѽ�������ģʽ)"
End If
noSoundC.Value = Val(TrueSoundMode)
'===========================���浵��ϣ����濪ʼ��Ϸ�����������========================
ScorePrinter.Caption = "��߷֣�" & CStr(TrueMaxScore)
StartFrameCount = -1
'=====================��Ӧ�����OnErrorRescue��ʹ�õĳ�ʼ������=================
Exit Sub
ResetApp:
Close #3
Kill App.Path & "\res\options.txt"
GoTo NormalStart
End Sub

Private Sub Help_MainSub_Click()
MsgBox "WASD���ƶ��������������ײ��������Ϸ������" + vbCrLf + "��������ƿ�����bug��Ϊ��64λWin10 1803�汾��ϵͳ�ϳ��������صļ���������" + vbCrLf + "�����û����϶��ԱߵĹ������ƶ���������" + vbCrLf + "������沼�ֲ�С�ĳ������⣬�����½ǵļ��ָ�" + vbCrLf + "�����������ˣ��" + vbCrLf + "����CTRl������ESC������F�����������Ĵ���----�̱�ģʽ" + vbCrLf + "(CRTL(����rap����)�����ǰ�F����̹�ˣ���)" + vbCrLf + "�̱�ģʽ��Ҫ���ĵ�ǰ�÷֡�5���ܴ�����ÿ����һ�λ�۳���5�ֵĵ�ǰ��(����ģʽ����)" + vbCrLf + "���߲������κ���ʦ����" + vbCrLf + "========�������ص�����ģʽ=======" + vbCrLf + "������������������Խ������ܣ��޵�ģʽ���Զ���̱̼��ܴ����۷�����ͷ�����" + vbCrLf + "�ҲŲ����������ǰѱ�exeĿ¼��resĿ¼�µ�options.txt�ĵڶ��иĳ�True��������Ϸ�ͽ���ɹ���", okonly, "��Ϸ����"
End Sub
Private Sub Help_b_click()
Call Help_MainSub_Click
End Sub

Private Sub settingsB_Click()
SettingsF.Show
End Sub

Private Sub StartGameAvoid_Click()
If noSoundC.Value = 0 Then
 nbaStar.URL = App.Path + "\res\cxkEng.mp3"
 nbaStar.Controls.play
 nbaStarT.Enabled = True
Else
 Call nbaStarT_Timer
End If
End Sub
Private Sub bgCtrl_Timer() '��̬����
StartFrameCount = StartFrameCount + 1
Me.Picture = LoadPicture(App.Path + "\res\StartFrame\StartPerFrame" + CStr(StartFrameCount) + ".gif")
If StartFrameCount >= 180 Then StartFrameCount = -1
If bgFlash.Value = 0 Then bgCtrl.Enabled = False: Me.Picture = LoadPicture(App.Path + "\res\cxk_bg_word.gif")
End Sub
Private Sub bgFlash_Click() '��̬�������ƹ�ѡ��
'bgFlash.Value��ֵΪ1�����ѹ�ѡ��0Ϊδ��ѡ
If bgFlash.Value = 1 Then
 MsgBox "��ѡ��Ϊʵ���Թ���" + vbCrLf + "���ֵ�����Կ��ܻ���ֿ��١�������Կ�����رմ�ѡ�", vbExclamation + vbOKOnly, "������̬����"
 bgCtrl.Enabled = True
ElseIf bgFlash.Value = 0 Then
 bgCtrl.Enabled = False
 Me.Picture = LoadPicture(App.Path + "\res\cxk_bg_word.gif")
End If
End Sub
Private Sub nbaStarT_Timer()
CXK_Avoid_Main.Enabled = True
'Me.Hide
CXK_Avoid_Main.Show
Load CXK_Avoid_Main
Unload Me
CXK_Avoid_Main.ResetGameT.Enabled = True
End Sub
Private Sub ccc_click()
CXK_Avoid_Main.Enabled = True
'Me.Hide
CXK_Avoid_Main.Show
Load CXK_Avoid_Main
Unload Me
CXK_Avoid_Main.ResetGameT.Enabled = True
End Sub


Private Sub ReLoad_Timer()
Call form_load
ReLoad.Enabled = False
End Sub

Private Sub StartGameShoot_Click()
'MsgBox "��ģ�����ڿ�����..."
Unload Me
Load CXK_Shoot_Main
CXK_Shoot_Main.Show
CXK_Shoot_Main.ResetGameT.Enabled = True
End Sub

Private Sub TitleCtrl_Timer()
If Me.Caption = "��Һ�" Then
 Me.Caption = "������ϰʱ��������"
ElseIf Me.Caption = "������ϰʱ��������" Then
 Me.Caption = "������ϰ��"
ElseIf Me.Caption = "������ϰ��" Then
 Me.Caption = "������"
ElseIf Me.Caption = "������" Then
 Me.Caption = "ϲ��"
ElseIf Me.Caption = "ϲ��" Then
 Me.Caption = "��"
ElseIf Me.Caption = "��" Then
 Me.Caption = "��"
ElseIf Me.Caption = "��" Then
 Me.Caption = "rap"
ElseIf Me.Caption = "rap" Then
 Me.Caption = "����"
ElseIf Me.Caption = "����" Then
 Me.Caption = "Music��"
ElseIf Me.Caption = "Music��" Then
 Me.Caption = "(�������Բ�����̫��)"
ElseIf Me.Caption = "(�������Բ�����̫��)" Then
 Me.Caption = "����̫��"
ElseIf Me.Caption = "����̫��" Then
 Me.Caption = "����ʵ����̫��"
ElseIf Me.Caption = "����ʵ����̫��" Then
 Me.Caption = "Ŷbaby"
ElseIf Me.Caption = "Ŷbaby" Then
 Me.Caption = "����ʵ����̫��~"
ElseIf Me.Caption = "����ʵ����̫��~" Then
 Me.Caption = "(The End)"
ElseIf Me.Caption = "(The End)" Then
 Me.Caption = "��Һ�"
End If
End Sub
