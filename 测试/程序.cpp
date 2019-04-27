#include <cflwͼ��_d2d.h>
#include <cflw����_win.h>
#include <cflw����_xi.h>
#include "����.h"
#include <�û�����ӿ�ʵ��_������.h>
#include <�û�����ӿ�ʵ��_����w.h>
#include <�û�����ӿ�ʵ��_����x.h>
#include "����.h"
#include "����.h"
namespace ��ά = cflw::ͼ��::d2d;
namespace ����w = cflw::����::win;
namespace ����x = cflw::����::xi;
//=============================================================================
// ����ʵ��
//=============================================================================
class C����::Cʵ�� {
public:
	HINSTANCE mʵ��;
	HWND m����;
	int m���ڴ�С[2];
	��ά::C��ά m��ά;
	��ά::C�ı����� m�ı�����;
	��ά::tp�ı���ʽ m�ı���ʽ;
	����w::C���� m����w;
	����x::C���� m����x;
	����w::tp���� m����;
	����w::tp��� m���;
	����w::tp���� m����;
	����x::tp�ֱ� m�ֱ�;
	ʱ��::C��ʱ�� m��ʱ��;
	ʱ��::C��֡�� m��֡��;
	�û�����::C�û����� m�û�����;
	�û�����::�ӿ�ʵ��::C������ m������;
	�û�����::�ӿ�ʵ��::C����w m���̽ӿ�;
	�û�����::�ӿ�ʵ��::C���w m���ӿ�;
	�û�����::�ӿ�ʵ��::C����w m�����ӿ�;
	�û�����::�ӿ�ʵ��::C�ֱ�x m�ֱ��ӿ�;
	std::vector<std::unique_ptr<�û�����::W����>> ma����;
	double m֡���� = 0;
	Cʵ��(HINSTANCE pʵ��) : mʵ��{pʵ��} {
		ma����.emplace_back(std::make_unique<W������>());
		ma����.emplace_back(std::make_unique<W����1>());
		ma����.emplace_back(std::make_unique<W����2>());
		ma����.emplace_back(std::make_unique<W����3>());
		ma����.emplace_back(std::make_unique<W����4>());
	}
	//��Ϣ����
	static LRESULT WINAPI f���ڹ���(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch(msg) {
		case WM_CHAR:
			mʵ��->m�û�����.f����_�����ַ�((WCHAR)wParam);
			return 0;
		case WM_DESTROY:
			mʵ��->f����();
			PostQuitMessage(0);
			return 0;
		};
		mʵ��->m����w.f������Ϣ(msg, wParam, lParam);
		//ʹ��Ĭ�ϴ���
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	void f��������() {
		//ע�ᴰ��
		WNDCLASSEX wc;
		wc.cbSize			= sizeof(WNDCLASSEX);			//ʹ��sizeof(WNDCLASSEX)
		wc.style			= CS_CLASSDC;					//��������
		wc.lpfnWndProc		= f���ڹ���;					//���ڹ���
		wc.cbClsExtra		= 0L;							//��չ:
		wc.cbWndExtra		= 0L;							//��չ:
		wc.hInstance		= mʵ��;						//ʵ�����
		wc.hIcon			= LoadIcon(nullptr, IDI_WINLOGO);	//����Ĭ��ͼ��
		wc.hCursor			= LoadCursor(nullptr, IDC_ARROW);	//����Ĭ�Ϲ��
		wc.hbrBackground	= nullptr;							//����Ҫ����
		wc.lpszMenuName		= nullptr;							//����Ҫ�˵�
		wc.lpszClassName	= L"������";					//��������
		wc.hIconSm			= nullptr;
		RegisterClassEx(&wc);
		//���㴰�ڴ�С
		RECT v���ھ��� = {0, 0, c���ڿ��, c���ڸ߶�};
		const DWORD	 c���ڷ�� = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
		AdjustWindowRect(&v���ھ���, c���ڷ��, FALSE);
		m���ڴ�С[0] = v���ھ���.right - v���ھ���.left;
		m���ڴ�С[1] = v���ھ���.bottom - v���ھ���.top;
		//��������
		m���� = CreateWindowW(L"������",	//��������
				L"���ڱ���",					//���ڱ���
				WS_OVERLAPPEDWINDOW,			//���ڷ��
				CW_USEDEFAULT, CW_USEDEFAULT,	//����
				m���ڴ�С[0], m���ڴ�С[1],		//���ڳߴ�
				GetDesktopWindow(),				//���ھ������
				nullptr,							//�˵����
				wc.hInstance,					//ʵ�����
				nullptr);							//����
		//��ʾ����
		ShowWindow(m����, SW_SHOWDEFAULT);
		UpdateWindow(m����);
		//ȡ���ڿͻ�����С
		GetClientRect(m����, &v���ھ���);
		m���ڴ�С[0] = v���ھ���.right - v���ھ���.left;
		m���ڴ�С[1] = v���ھ���.bottom - v���ھ���.top;
	}
	void f��ʼ��() {
		m��ά.f��ʼ��(m����, c����);
		m����w.f��ʼ��(m����, c����);
		m����w.f��������(m����);
		m����w.f�������(m���);
		m����w.f��������(m����);
		m����x.f�����ֱ�(m�ֱ�);
		m���̽ӿ�.f��ʼ��(*m����);
		m���ӿ�.f��ʼ��(*m���);
		m�����ӿ�.f��ʼ��(*m����);
		m�ֱ��ӿ�.f��ʼ��(*m�ֱ�);
		m��ʱ��.f����(c֡��);
		m��֡��.f����();
		m�ı�����.f��ʼ��();
		��ά::S�ı���ʽ���� v�ı���ʽ;
		v�ı���ʽ.fs�ֺ�(10);
		m�ı���ʽ = m�ı�����.fc�ı���ʽ(v�ı���ʽ);
		m�û�����.f��ʼ��();
		m�û�����.fs������(m������);
		m�û�����.f����_s���̽ӿ�(m���̽ӿ�);
		m�û�����.f����_s���ӿ�(m���ӿ�);
		m�û�����.f����_s�����ӿ�(m�����ӿ�);
		m�û�����.f����_s�ֱ��ӿ�(m�ֱ��ӿ�);
		m�û�����.f�½�����(*ma����[4]);
		m������.f��ʼ��(m��ά);
	}
	void f����() {
		//��Ϣѭ��
		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		while (msg.message != WM_QUIT) {	//��Ϣѭ��
			if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {	//����Ϣʱ�Ĵ���,��Ҫ�޸�
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			} else {	//û����Ϣʱ�Ĵ���
				if (m��ʱ��.f�δ�()) {
					m֡���� = m��֡��.f����();
					f����();
					f����();
					f��ʾ();
				}
			}
		}	//��Ϣѭ������
	}
	void f����() {
		//v��ά.f����();
		//v����.f����();
	}
	void f����() {
		m����w.f����();
		m����x.f����();
		m���̽ӿ�.f����();
		m���ӿ�.f����();
		m�����ӿ�.f����();
		m�ֱ��ӿ�.f����();
		m�û�����.f����();
	}
	void f����() {
		m�û�����.f����();
	}
	void f��ʾ() {
		auto &v��Ⱦ���� = m��ά.fg��Ⱦ����();
		v��Ⱦ����.f��ʼ();
		v��Ⱦ����.f����();
		auto v��ͼ�� = m��ά.fc��ͼ��();
		auto v���ı� = m��ά.fc���ı�();
		v��ͼ��->fs��ɫ(t��ɫ(1, 1, 1, 1));
		//���ʮ��
		const t����2 v������� = {m���->f����().x, m���->f����().y};
		v��ͼ��->f��������({v������� + t����2{16, 0}, v������� + t����2{-16, 0}});
		v��ͼ��->f��������({v������� + t����2{0, 16}, v������� + t����2{0, -16}});
		//�ı�
		v���ı�->fs��ʽ(m�ı���ʽ.Get());
		std::wstring v�ı� = L"x= ";
		v�ı� += std::to_wstring(v�������.x);
		v�ı� += L"\ny= ";
		v�ı� += std::to_wstring(v�������.y);
		v���ı�->fs����(v������� + t����2{8, 0});
		v���ı�->f�����ı�(v�ı�);
		//֡����
		v�ı� = std::to_wstring(m֡����);
		v���ı�->fs����(v������� + t����2{0, -32});
		v���ı�->f�����ı�(v�ı�);
		//����
		m�û�����.f��ʾ();
		//����
		v��Ⱦ����.f����();
	}
};
//=============================================================================
// ����
//=============================================================================
std::unique_ptr<C����::Cʵ��> C����::mʵ��;
void C����::f��ʼ��(HINSTANCE p) {
	mʵ�� = std::make_unique<Cʵ��>(p);
	mʵ��->f��������();
	mʵ��->f��ʼ��();
}
void C����::f����() {
	mʵ��->f����();
}
void C����::f����() {
	mʵ��.reset();
}
�û�����::W���� &C����::fg����(int a) {
	return *mʵ��->ma����[a];
}
//=============================================================================
// ������
//=============================================================================
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int) {
	C����::f��ʼ��(hInst);
	C����::f����();
	C����::f����();
}
//
