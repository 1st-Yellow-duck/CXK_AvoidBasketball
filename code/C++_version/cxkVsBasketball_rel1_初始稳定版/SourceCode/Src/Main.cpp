//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#include "CommonClass.h"
#include "LessonX.h"

#include<mmsystem.h>				//PlaySound������ͷ�ļ�
#pragma comment(lib, "winmm.lib")	//���ӿ⣬PlaySound��������ʹ��
#include <cstdlib>					//itoa()
#include <string>
#include <Windows.h>				//MSGBOX(), ��ȡʱ������Ϊ����
#include <iostream>					//�����
#include <cstdlib>					//�����
#include <sstream>					//score
using namespace std;

//Ĭ��������
const float chickenSpeed = -40;
const float basketballSpeed = 40;
const float cxk_loc_x = -80;
const float cxk_loc_y = 0;
const float chicken_def_pos = 96;
const int chicken_num = 8;

//״ָ̬ʾ
bool running = false;
int score = 0;

//����Ԫ��
CSprite *bgEntry = new CSprite("bgEntry");
CSprite *btnTip = new CSprite("tip");
CTextSprite *scoreText = new CTextSprite("scoreText");
CSprite *cxk = new CSprite("cxk");
CSprite *basketball = new CSprite("basketball");
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

void startGame(){
	running = true;

	bgEntry->SetSpriteVisible(false);
	bgRoom->SetSpriteVisible(true);

	const int soundCnt = 2;
	string sounds[soundCnt] = {"game/data/audio/jntm.wav", "game/data/audio/jntm_crazy.wav"};
	PlaySound(sounds[randNum(soundCnt - 1) - 1].data(),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);

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

	for(int i = 0; i < chicken_num; i++){
		chickenStop(i);
	}
	int result = MessageBoxShow("�˱�", "����ʦ����\n\n������");
	if (result == 6)
	{
		//�����ȷ��
		startGame();
	}else{
		//�����ȡ��
		exit(1);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
//
// ���������
//
//////////////////////////////////////////////////////////////////////////////////////////
int PASCAL WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR     lpCmdLine,
                   int       nCmdShow)
{
	// ��ʼ����Ϸ����
	if( !CSystem::InitGameEngine( hInstance, lpCmdLine ) )
		return 0;

	// To do : �ڴ�ʹ��API���Ĵ��ڱ���
	CSystem::SetWindowTitle("������������");

	bgRoom->SetSpriteVisible(false);
	cxk->SetSpriteVisible(false);
	basketball->SetSpriteVisible(false);
	scoreText->SetSpriteVisible(false);

	// ������ѭ����������Ļͼ��ˢ�µȹ���
	while( CSystem::EngineMainLoop() )
	{
		// ��ȡ���ε���֮���ʱ�����ݸ���Ϸ�߼�����
		float	fTimeDelta	=	CSystem::GetTimeDelta();

		// ִ����Ϸ��ѭ��
		g_GameMain.GameMainLoop( fTimeDelta );

		scoreText->SetTextValue(score);
	};

	// �ر���Ϸ����
	CSystem::ShutdownGameEngine();
	return 0;
}

//==========================================================================
//
// ���沶׽����ƶ���Ϣ�󣬽����õ�������
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
//
void CSystem::OnMouseMove( const float fMouseX, const float fMouseY )
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����
	g_GameMain.OnMouseMove(fMouseX, fMouseY);
	cxk->SetSpritePosition(fMouseX,fMouseY);
}
//==========================================================================
//
// ���沶׽�������Ϣ�󣬽����õ�������
// ���� iMouseType����갴��ֵ���� enum MouseTypes ����
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
//
void CSystem::OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����
	g_GameMain.OnMouseClick(iMouseType, fMouseX, fMouseY);

	//��ʼ��Ϸ
	if(!running)
		startGame();
	else
		initBasketball();
}
//==========================================================================
//
// ���沶׽��굯����Ϣ�󣬽����õ�������
// ���� iMouseType����갴��ֵ���� enum MouseTypes ����
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
//
void CSystem::OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY )
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����
	g_GameMain.OnMouseUp(iMouseType, fMouseX, fMouseY);
}
//==========================================================================
//
// ���沶׽���̰�����Ϣ�󣬽����õ�������
// ���� iKey�������µļ���ֵ�� enum KeyCodes �궨��
// ���� iAltPress, iShiftPress��iCtrlPress�������ϵĹ��ܼ�Alt��Ctrl��Shift��ǰ�Ƿ�Ҳ���ڰ���״̬(0δ���£�1����)
//
void CSystem::OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress )
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����
	g_GameMain.OnKeyDown(iKey, bAltPress, bShiftPress, bCtrlPress);
	/*switch(iKey){
		case KEY_W:
			cxk->SetSpriteLinearVelocityY(-30);
			break;
		case KEY_A:
			cxk->SetSpriteLinearVelocityX(-30);
			break;
		case KEY_S:
			cxk->SetSpriteLinearVelocityY(30);
			break;
		case KEY_D:
			cxk->SetSpriteLinearVelocityX(30);
			break;
	}*/
}
//==========================================================================
//
// ���沶׽���̵�����Ϣ�󣬽����õ�������
// ���� iKey������ļ���ֵ�� enum KeyCodes �궨��
//
void CSystem::OnKeyUp( const int iKey )
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����
	g_GameMain.OnKeyUp(iKey);
	/*switch(iKey){
		case KEY_W:
		case KEY_S:
			cxk->SetSpriteLinearVelocityY(0);
			break;
		case KEY_A:
		case KEY_D:
			cxk->SetSpriteLinearVelocityX(0);
			break;
	}*/
}

//===========================================================================
//
// ���沶׽�������뾫����ײ֮�󣬵��ô˺���
// ����֮��Ҫ������ײ�������ڱ༭�����ߴ��������þ��鷢�ͼ�������ײ
// ���� szSrcName��������ײ�ľ�������
// ���� szTarName������ײ�ľ�������
//
void CSystem::OnSpriteColSprite( const char *szSrcName, const char *szTarName )
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����
	g_GameMain.OnSpriteColSprite(szSrcName, szTarName);

	if(string(szSrcName).find("chicken") == 0){
		if(running && strcmp(szTarName, "cxk") == 0){
			stopGame();
		}else{
			initBasketball();
			int index = szSrcName[7];
			chickenReGo(index);
		}
	}

	if(running && string(szTarName).find("chicken") == 0){
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
// ���沶׽������������߽���ײ֮�󣬵��ô˺���.
// ����֮��Ҫ������ײ�������ڱ༭�����ߴ��������þ��������߽�����
// ���� szName����ײ���߽�ľ�������
// ���� iColSide����ײ���ı߽� 0 ��ߣ�1 �ұߣ�2 �ϱߣ�3 �±�
//
void CSystem::OnSpriteColWorldLimit( const char *szName, const int iColSide )
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����
	g_GameMain.OnSpriteColWorldLimit(szName, iColSide);
	
	if(strcmp(szName,"basketball") == 0 && iColSide == 1){
		initBasketball();
	}else if(string(szName).find("chicken") == 0){
		int index = szName[7] - 48;
		chickenReGo(index);
	}

}