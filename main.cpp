/*==============================================================================

   DirectX�̏����� [main.cpp]
                                                         Author : 
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#include	"main.h"
#include	"01_Scene.h"
#include	"01_BOSSscene.h"
#include	"00_title.h"
#include	"01.5_StageSelect.h"
#include	"Result.h"
#include	"weapon_shop.h"
#include	"weapon_select.h"
#include	"data.h"

#include	"keyboard.h"

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#pragma comment (lib, "d3d11.lib")		
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "d3dx11.lib")	
#pragma comment (lib, "d3dx9.lib")	
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib,"xinput.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME			"GameWindow"				// �E�C���h�E�̃N���X��
#define WINDOW_CAPTION		"DirectX�̏�����"			// �E�C���h�E�̃L���v�V������
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);


//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

#ifdef _DEBUG
int		g_CountFPS;							// FPS�J�E���^
char	g_DebugStr[2048] = WINDOW_CAPTION;	// �f�o�b�O�����\���p




#endif

SCENE g_Scene = SCENE_NONE;	// �V�[����������Ԃ�

//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	// ���Ԍv���p
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	
	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = CLASS_NAME;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);

	RegisterClass(&wc);
	
	// �E�B���h�E�̍쐬
	HWND hWnd = CreateWindow(CLASS_NAME,
						WINDOW_CAPTION,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,																		// �E�B���h�E�̍����W
						CW_USEDEFAULT,																		// �E�B���h�E�̏���W
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME)*2,									// �E�B���h�E����
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME)*2+GetSystemMetrics(SM_CYCAPTION),	// �E�B���h�E�c��
						NULL,
						NULL,
						hInstance,
						NULL);

	// DirectX�̏�����(�E�B���h�E���쐬���Ă���s��)
	if(FAILED(Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	// �t���[���J�E���g������
	timeBeginPeriod(1);	// ����\��ݒ�
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// �V�X�e���������~���b�P�ʂŎ擾
	dwCurrentTime = dwFrameCount = 0;
	
	// �E�C���h�E�̕\��(Init()�̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG			msg;

	// ���b�Z�[�W���[�v
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();					// �V�X�e���������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1�b���ƂɎ��s
			{
#ifdef _DEBUG
				g_CountFPS = dwFrameCount;
#endif
				dwFPSLastTime = dwCurrentTime;				// FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;							// �J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60�b���ƂɎ��s
			{
				dwExecLastTime = dwCurrentTime;	// ��������������ۑ�

#ifdef _DEBUG	// �f�o�b�O�ł̎�����FPS��\������
				wsprintf(g_DebugStr, WINDOW_CAPTION);
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " FPS:%d", g_CountFPS);
				SetWindowText(hWnd, g_DebugStr);
#endif

				Update();			// �X�V����
				Draw();				// �`�揈��

				dwFrameCount++;		// �����񐔂̃J�E���g�����Z
			}
		}
	}
	
	timeEndPeriod(1);				// ����\��߂�

	// �I������
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Keyboard_ProcessMessage(uMsg, wParam, lParam);

	switch (uMsg) {
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;

	case WM_CLOSE:
		if (MessageBox(hWnd, "�{���ɏI�����Ă�낵���ł����H", "�m�F", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	};

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �����_�����O�����̏�����
	InitRenderer(hInstance, hWnd, bWindow);


	//���͏����̏�����
	InitInput(hInstance, hWnd);
	Keyboard_Initialize();

	//�T�E���h������
	InitSound(hWnd);
	
	InitPolygon();	//�|���S��������

	//����N�����̃f�[�^������
	InitData();

	SetScene(SCENE_TITLE);	// �^�C�g���V�[��������

	


	return S_OK;
}


//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	UninitPolygon();	//�|���S���I������
	UninitSound();//�T�E���h�I������
	


	SetScene(SCENE_NONE);	// �^�C�g���V�[��������

	//���͏����̏I��
	UninitInput();

	// �����_�����O�̏I������
	UninitRenderer();
}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	//���͏����̍X�V
	UpdateInput();
	

	UpdatePolygon();	//�|���S���X�V����

	switch (g_Scene)
	{
	case SCENE_TITLE:
		Updatetitle();
		//Keyboard_IsKeyDown(K);
		break;
	case SCENE_SELECT:
		UpdateStageSelect();

		break;

	case SCENE_GAME://�X�e�[�W01
		UpdateScene();
		break;

	case SCENE_STAGE02://�X�e�[�W02
		UpdateScene();
		break;

	case SCENE_STAGE03://�X�e�[�W03
		UpdateScene();
		break;

	case SCENE_STAGE04://�X�e�[�W04
		UpdateScene();
		break;

	case SCENE_BOSS01:
		UpdateBossScene();
		break;
	case SCENE_BOSS02:
		UpdateBossScene();
		break;
	case SCENE_BOSS03:
		UpdateBossScene();
		break;
	case SCENE_BOSS04:
		UpdateBossScene();
		break;
	case SCENE_RESULT:
		UpdateResultScene();
		break;
	case SCENE_SHOP:
		UpdateWeaponShop();
		break;
	case SCENE_SKILL_SET:
		UpdateWeaponSelect();
		break;
	}

	


	
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@�N���A
	Clear();

	// 2D�`��Ȃ̂Ő[�x����
	SetDepthEnable(false);

	DrawPolygon();	//�|���S���`�揈��



	switch (g_Scene)
	{
	case SCENE_TITLE:
		Drawtitle();
		break;

	case SCENE_SELECT:
		DrawStageSelect();
		break;

	case SCENE_GAME:
		DrawBScene();//�X�e�[�W01
		break;

	case SCENE_STAGE02://�X�e�[�W02
		DrawBScene();
		break;

	case SCENE_STAGE03://�X�e�[�W03
		DrawBScene();
		break;

	case SCENE_STAGE04://�X�e�[�W04
		DrawBScene();
		break;

	case SCENE_BOSS01:
		DrawBossScene();
		break;
	case SCENE_BOSS02:
		DrawBossScene();
		break;
	case SCENE_BOSS03:
		DrawBossScene();
		break;
	case SCENE_BOSS04:
		DrawBossScene();
		break;
	case SCENE_RESULT:
		DrawResultScene();
		break;

	case SCENE_SHOP:
		DrawWeaponShop();
		break;

	case SCENE_SKILL_SET:
		DrawWeaponSelect();
		break;
	}



	// �o�b�N�o�b�t�@�A�t�����g�o�b�t�@����ւ�
	Present();
}

void SetScene(SCENE Scene)
{
	// ���݂̃V�[���̏I������
	switch (g_Scene)
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE://�^�C�g��
		Uninittitle();
		break;

	case SCENE_SELECT://�X�e�[�W�Z���N�g
		UninitStageSelect();
		break;

	case SCENE_GAME://�X�e�[�W01
		UninitScene();
		break;

	case SCENE_STAGE02://�X�e�[�W02
		UninitScene();
		break;

	case SCENE_STAGE03://�X�e�[�W03
		UninitScene();
		break;

	case SCENE_STAGE04://�X�e�[�W04
		UninitScene();
		break;

	case SCENE_BOSS01:
		UninitBossScene();
		break;

	case SCENE_BOSS02:
		UninitBossScene();
		break;

	case SCENE_BOSS03:
		UninitBossScene();
		break;

	case SCENE_BOSS04:
		UninitBossScene();
		break;

	case SCENE_RESULT:
		UninitResultScene();
		break;

	case SCENE_SHOP:
		UninitWeaponShop();
		break;

	case SCENE_SKILL_SET:
		UninitWeaponSelect();
		break;
	}

	StopSoundAll();//���ׂĂ̍Đ����~

	// �V�[����Ԃ��X�V
	g_Scene = Scene;

	// ���̃V�[���̏���������
	switch (g_Scene)
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE://�^�C�g��
		Inittitle();
		break;

	case SCENE_SELECT://�X�e�[�W�Z���N�g
		InitStageSelect();
		break;

	case SCENE_GAME://�X�e�[�W01
		InitScene();
		break;

	case SCENE_STAGE02://�X�e�[�W02
		InitScene();
		break;

	case SCENE_STAGE03://�X�e�[�W03
		InitScene();
		break;

	case SCENE_STAGE04://�X�e�[�W04
		InitScene();
		break;


	case SCENE_BOSS01:
		InitBossScene();
		break;

	case SCENE_BOSS02:
		InitBossScene();
		break;

	case SCENE_BOSS03:
		InitBossScene();
		break;

	case SCENE_BOSS04:
		InitBossScene();
		break;
	case SCENE_RESULT:
		InitResultScene();
		break;
	case SCENE_SHOP:
		InitWeaponShop();
		break;
	case SCENE_SKILL_SET:
		InitWeaponSelect();
		break;
	}
}

SCENE GetScene()
{
	return g_Scene;
}
