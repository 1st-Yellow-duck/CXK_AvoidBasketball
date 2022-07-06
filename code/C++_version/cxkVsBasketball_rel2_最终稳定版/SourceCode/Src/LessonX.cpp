/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <Stdio.h>
#include "CommonClass.h"
#include "LessonX.h"


#include<mmsystem.h>				//PlaySound������ͷ�ļ�
#pragma comment(lib, "winmm.lib")	//���ӿ⣬PlaySound��������ʹ��
#include <cstdlib>					//itoa()
#include <string>
#include <Windows.h>				//MSGBOX(), ��ȡʱ������Ϊ����
#include <iostream>					//�����
#include <cstdlib>					//�����, ��ҳ��ת
#include <sstream>					//score
using namespace std;

//Ĭ��������
const string githubAddr = "https://github.com/CoolestEnoch/CXK_AvoidBasketball";
const float chickenSpeed = -40;
const float basketballSpeed = 40;
const float cxk_loc_x = -80;
const float cxk_loc_y = 0;
const float chicken_def_pos = 100;
const int chicken_num = 8;
const int caibiLim = 5;

//״ָ̬ʾ
bool running = false;
int score = 0;

//����Ԫ��
CSprite *bgEntry = new CSprite("bgEntry");
CSprite *btnTip = new CSprite("tip");
CTextSprite *scoreText = new CTextSprite("scoreText");
CSprite *cxk = new CSprite("cxk");
CSprite *caibi = new CSprite("caibi");
CSprite *basketball = new CSprite("basketball");
CSprite *btnHelp = new CSprite("btnHelp");
CSprite *bgRoom = new CSprite("bgRoom");
string chickens[chicken_num] = {"chicken0", "chicken1", "chicken2", "chicken3", "chicken4", "chicken5", "chicken6", "chicken7"};
CSprite *chickensPtr[chicken_num];

int randNum(int maxRange){
	srand(unsigned int(GetTickCount64()));
	return ( rand() % ( maxRange + 1 ) + 1 );
}

void initBasketball(){
	if(running){
		basketball->SetSpritePosition(cxk->GetSpritePositionX()+15, cxk->GetSpritePositionY());
		basketball->SetSpriteLinearVelocityX(basketballSpeed);
	}
}

int MessageBoxShow(const char* title, const char* msg) {
	static HINSTANCE hInstance = GetModuleHandle(0);
	tagMSGBOXPARAMSA* tms = new tagMSGBOXPARAMSA;
	tms->cbSize = sizeof(*tms);
	tms->hwndOwner = NULL;
	tms->lpszCaption = title;
	tms->lpszText = msg;
	tms->dwStyle = MB_USERICON + MB_YESNO;
	tms->lpszIcon = MAKEINTRESOURCEA(105);
	tms->hInstance = hInstance;
	int result = MessageBoxIndirectA(tms);
	return result;
}

void chickenReGo(int index){
	if(running){
		chickensPtr[index]->SetSpritePositionX(chicken_def_pos);
		chickensPtr[index]->SetSpriteLinearVelocityX(chickenSpeed);
	}
}

void chickenStop(int i){
	chickensPtr[i]->SetSpriteLinearVelocityX(0);
	chickensPtr[i]->SetSpritePositionX(chicken_def_pos);
}

void resetChicken(){
	for(int i = 0; i < chicken_num; i++){
		chickenStop(i);
	}
}

void startGame(){
	running = true;

	btnHelp->SetSpriteVisible(false);
	bgEntry->SetSpriteVisible(false);
	bgRoom->SetSpriteVisible(true);

	string sounds[2] = {"game/data/audio/jntm_crazy.wav", "game/data/audio/jntm.wav"};
	PlaySound(sounds[randNum(1) - 1].data(),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);

	cxk->SetSpriteVisible(true);
	basketball->SetSpriteVisible(true);
	scoreText->SetSpriteVisible(true);
	initBasketball();

	if(btnTip->GetSpritePositionY() == 32){
		btnTip->SetSpriteLinearVelocityY(30);
	}

	//�������һֻ��
	for(int i = 0; i < chicken_num; i++){
		chickensPtr[i] = new CSprite(chickens[i].data());
	}
	int index = randNum(chicken_num - 1);
	chickenReGo(index - 1);
	//chickens[0].SetSpriteLinearVelocityX(-40);
}

void stopGame(){
	running = false;
	score = 0;

	basketball->SetSpriteLinearVelocityX(0);
	basketball->SetSpriteVisible(false);
	scoreText->SetSpriteVisible(false);

	cxk->SetSpritePosition(cxk_loc_x,cxk_loc_y);
	cxk->SetSpriteLinearVelocity(0,0);

	for(int i = 0; i < chicken_num; i++){
		chickenStop(i);
	}
	int result = MessageBoxShow("�˱�", "��ʦ������~~~\n\n������");
	if (result == 6)
	{
		//�����ȷ��
		startGame();
	}else{
		//�����ȡ��
		exit(1);
	}
}
////////////////////////////////////////////////////////////////////////////////
//
//
CGameMain		g_GameMain;	

//==============================================================================
//
// ����ĳ�������Ϊ��GameMainLoop����Ϊ��ѭ��������������ÿ֡ˢ����Ļͼ��֮�󣬶��ᱻ����һ�Ρ�

//==============================================================================
//
// ���캯��
CGameMain::CGameMain()
{
	m_iGameState			=	0;
}
//==============================================================================
//
// ��������
CGameMain::~CGameMain()
{
}

//==============================================================================
//
// ��Ϸ��ѭ�����˺���������ͣ�ĵ��ã�����ÿˢ��һ����Ļ���˺�����������һ��
// ���Դ�����Ϸ�Ŀ�ʼ�������С������ȸ���״̬. 
// ��������fDeltaTime : �ϴε��ñ��������˴ε��ñ�������ʱ��������λ����
void CGameMain::GameMainLoop( float	fDeltaTime )
{
	scoreText->SetTextValue(score);
	switch( GetGameState() )
	{
		// ��ʼ����Ϸ�������һ���������
	case 1:
		{
			GameInit();
			SetGameState(2); // ��ʼ��֮�󣬽���Ϸ״̬����Ϊ������
		}
		break;

		// ��Ϸ�����У����������Ϸ�߼�
	case 2:
		{
			// TODO �޸Ĵ˴���Ϸѭ�������������ȷ��Ϸ�߼�
			if( true )
			{
				GameRun( fDeltaTime );
			}
			else // ��Ϸ������������Ϸ���㺯����������Ϸ״̬�޸�Ϊ����״̬
			{				
				SetGameState(0);
				GameEnd();
			}
		}
		break;

		// ��Ϸ����/�ȴ����ո����ʼ
	case 0:
	default:
		break;
	};
}
//=============================================================================
//
// ÿ�ֿ�ʼǰ���г�ʼ���������һ���������
void CGameMain::GameInit()
{
	bgRoom->SetSpriteVisible(false);
	cxk->SetSpriteVisible(false);
	basketball->SetSpriteVisible(false);
	scoreText->SetSpriteVisible(false);
}
//=============================================================================
//
// ÿ����Ϸ������
void CGameMain::GameRun( float fDeltaTime )
{
	
}
//=============================================================================
//
// ������Ϸ����
void CGameMain::GameEnd()
{
}
//==========================================================================
//
// ����ƶ�
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
void CGameMain::OnMouseMove( const float fMouseX, const float fMouseY )
{
	cxk->SetSpriteLinearVelocity(0,0);
	cxk->SetSpritePosition(fMouseX,fMouseY);
}
//==========================================================================
//
// �����
// ���� iMouseType����갴��ֵ���� enum MouseTypes ����
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
void CGameMain::OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{
	if((fMouseX > (btnHelp->GetSpritePositionX() - btnHelp->GetSpriteWidth()/2)) && (fMouseX < (btnHelp->GetSpritePositionX() + btnHelp->GetSpriteWidth()/2)) && 
		(fMouseY > (btnHelp->GetSpritePositionY() - btnHelp->GetSpriteHeight()/2)) && (fMouseY < (btnHelp->GetSpritePositionY() + btnHelp->GetSpriteHeight()/2))){
			stringstream ss;
			ss << "WASD���߷�����ƶ�������������������";
			ss << 5;
			ss << "�ֵ�ʱ��CTRL�����Կ����С�" << endl << endl;
			ss << "���ʿ�Դ��Ŀ��ַ?";
			int respond = MessageBoxShow("����", ss.str().data());
			if(respond == 6){
				//�����ȷ��
				string cmd = "start " + githubAddr;
				system(cmd.data());
			}else{
				//�����ȡ��
			}
	}else{
		//��ʼ��Ϸ
		if(!running)
			startGame();
		else
			initBasketball();
	}
}
//==========================================================================
//
// ��굯��
// ���� iMouseType����갴��ֵ���� enum MouseTypes ����
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
void CGameMain::OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY )
{
	
}
//==========================================================================
//
// ���̰���
// ���� iKey�������µļ���ֵ�� enum KeyCodes �궨��
// ���� iAltPress, iShiftPress��iCtrlPress�������ϵĹ��ܼ�Alt��Ctrl��Shift��ǰ�Ƿ�Ҳ���ڰ���״̬(0δ���£�1����)
void CGameMain::OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress )
{	
	switch(iKey){
	case KEY_W:
	case KEY_UP:
		cxk->SetSpriteLinearVelocityY(-30);
		break;
	case KEY_A:
	case KEY_LEFT:
		cxk->SetSpriteLinearVelocityX(-30);
		break;
	case KEY_S:
	case KEY_DOWN:
		cxk->SetSpriteLinearVelocityY(30);
		break;
	case KEY_D:
	case KEY_RIGHT:
		cxk->SetSpriteLinearVelocityX(30);
		break;
	case KEY_LCONTROL:
	case KEY_RCONTROL:
	case KEY_CONTROL:
		if(running && score >= caibiLim){
			score -= caibiLim;
			caibi->SetSpriteLinearVelocityX(basketballSpeed + 5);
		}
		break;
	case KEY_SPACE:
		if(!running)
			startGame();
		else
			initBasketball();
	}
}
//==========================================================================
//
// ���̵���
// ���� iKey������ļ���ֵ�� enum KeyCodes �궨��
void CGameMain::OnKeyUp( const int iKey )
{
	switch(iKey){
	case KEY_W:
	case KEY_S:
	case KEY_UP:
	case KEY_DOWN:
		cxk->SetSpriteLinearVelocityY(0);
		break;
	case KEY_A:
	case KEY_D:
	case KEY_LEFT:
	case KEY_RIGHT:
		cxk->SetSpriteLinearVelocityX(0);
		break;
	}
}
//===========================================================================
//
// �����뾫����ײ
// ���� szSrcName��������ײ�ľ�������
// ���� szTarName������ײ�ľ�������
void CGameMain::OnSpriteColSprite( const char *szSrcName, const char *szTarName )
{
	if(string(szSrcName).find("chicken") == 0){
		if(running && strcmp(szTarName, "cxk") == 0){
			stopGame();
		}else{
			initBasketball();
			int index = szSrcName[7];
			chickenReGo(index);
		}
	}

	if(running && string(szTarName).find("chicken") == 0 && strcmp(szSrcName, "caibi") != 0){
		score++;
	}

	if(running){
		int index = randNum(chicken_num - 1);
		if(chickensPtr[index - 1]->GetSpriteLinearVelocityX() == 0)
			chickenReGo(index - 1);
	}
}
//===========================================================================
//
// ����������߽���ײ
// ���� szName����ײ���߽�ľ�������
// ���� iColSide����ײ���ı߽� 0 ��ߣ�1 �ұߣ�2 �ϱߣ�3 �±�
void CGameMain::OnSpriteColWorldLimit( const char *szName, const int iColSide )
{
	if(strcmp(szName,"basketball") == 0 && iColSide == 1){
		initBasketball();
	}else if(string(szName).find("chicken") == 0){
		int index = szName[7] - 48;
		chickenReGo(index);
	}else if(strcmp(szName, "caibi") == 0){
		caibi->SetSpritePositionX(-128);
		caibi->SetSpriteLinearVelocityX(0);
		resetChicken();
	}
}

