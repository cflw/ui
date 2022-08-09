#include <cflw图形_d2d.h>
#include <cflw输入_win.h>
#include <cflw输入_xi.h>
#include "程序.h"
#include <用户界面接口实现_图形d2d.h>
#include <用户界面接口实现_输入w.h>
#include <用户界面接口实现_输入x.h>
#include <用户界面接口实现_音频x.h>
#include "常量.h"
#include "资源.h"
#include "头.h"
import 窗口_主窗口;
import 窗口_按钮;
import 窗口_复选框;
import 窗口_表格;
import 窗口_选项卡;
namespace 二维 = cflw::图形::d2d;
namespace 输入w = cflw::输入::win;
namespace 输入x = cflw::输入::xi;
namespace 音频x = cflw::音频::xa2;
//==============================================================================
// 程序实现
//==============================================================================
class C程序::C实现 {
public:
	HINSTANCE m实例;
	HWND m窗口;
	int m窗口大小[2];
	二维::C二维 m二维;
	二维::C文本工厂 m文本工厂;
	二维::tp文本格式 m文本格式;
	输入w::C输入 m输入w;
	输入x::C输入 m输入x;
	输入w::tp键盘 m键盘;
	输入w::tp鼠标 m鼠标;
	输入w::tp触摸 m触摸;
	输入x::tp手柄 m手柄;
	音频x::C音频 m音频;
	音频x::C播放控制 m播放控制;
	时间::C计时器 m计时器;
	时间::C计帧器 m计帧器;
	用户界面::C用户界面 m用户界面;
	用户界面::接口实现::d2d::C图形 m图形接口;
	用户界面::接口实现::win::C键盘 m键盘接口;
	用户界面::接口实现::win::C鼠标 m鼠标接口;
	用户界面::接口实现::win::C触摸 m触摸接口;
	用户界面::接口实现::xi::C手柄 m手柄接口;
	用户界面::接口实现::xa::C音频 m音频接口;
	std::vector<std::unique_ptr<用户界面::W窗口>> ma窗口;
	C图片资源 ma图片;
	double m帧速率 = 0;
	C实现(HINSTANCE a实例) : m实例(a实例) {
		ma窗口.emplace_back(std::make_unique<W主窗口>());
		ma窗口.emplace_back(std::make_unique<W窗口1>());
		ma窗口.emplace_back(std::make_unique<W窗口2>());
		ma窗口.emplace_back(std::make_unique<W窗口3>());
		ma窗口.emplace_back(std::make_unique<W窗口4>());
	}
	//消息过程
	static LRESULT WINAPI f窗口过程(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch(msg) {
		case WM_CHAR:
			m实现->m用户界面.f输入_接收字符((WCHAR)wParam);
			return 0;
		case WM_DESTROY:
			m实现->f销毁();
			PostQuitMessage(0);
			return 0;
		};
		m实现->m输入w.f窗口消息(msg, wParam, lParam);
		//使用默认处理
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	void f创建窗口() {
		//注册窗口
		WNDCLASSEX wc;
		wc.cbSize			= sizeof(WNDCLASSEX);			//使用sizeof(WNDCLASSEX)
		wc.style			= CS_CLASSDC;					//窗口类型
		wc.lpfnWndProc		= f窗口过程;					//窗口过程
		wc.cbClsExtra		= 0L;							//扩展:
		wc.cbWndExtra		= 0L;							//扩展:
		wc.hInstance		= m实例;						//实例句柄
		wc.hIcon			= LoadIcon(nullptr, IDI_WINLOGO);	//载入默认图标
		wc.hCursor			= LoadCursor(nullptr, IDC_ARROW);	//载入默认光标
		wc.hbrBackground	= nullptr;							//不需要背景
		wc.lpszMenuName		= nullptr;							//不需要菜单
		wc.lpszClassName	= L"窗口类";					//设置类名
		wc.hIconSm			= nullptr;
		RegisterClassEx(&wc);
		//计算窗口大小
		RECT v窗口矩形 = {0, 0, c窗口宽度, c窗口高度};
		const DWORD	 c窗口风格 = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
		AdjustWindowRect(&v窗口矩形, c窗口风格, FALSE);
		m窗口大小[0] = v窗口矩形.right - v窗口矩形.left;
		m窗口大小[1] = v窗口矩形.bottom - v窗口矩形.top;
		//创建窗口
		m窗口 = CreateWindowW(L"窗口类",	//窗口类名
				L"窗口标题",					//窗口标题
				WS_OVERLAPPEDWINDOW,			//窗口风格
				CW_USEDEFAULT, CW_USEDEFAULT,	//坐标
				m窗口大小[0], m窗口大小[1],		//窗口尺寸
				GetDesktopWindow(),				//窗口句柄参数
				nullptr,							//菜单句柄
				wc.hInstance,					//实例句柄
				nullptr);							//参数
		//显示窗口
		ShowWindow(m窗口, SW_SHOWDEFAULT);
		UpdateWindow(m窗口);
		//取窗口客户区大小
		GetClientRect(m窗口, &v窗口矩形);
		m窗口大小[0] = v窗口矩形.right - v窗口矩形.left;
		m窗口大小[1] = v窗口矩形.bottom - v窗口矩形.top;
	}
	void f初始化() {
		m二维.f初始化(m窗口, c缩放);
		m输入w.f初始化(m窗口, c缩放);
		//m音频.f初始化();
		//m播放控制.f初始化(m音频);
		m键盘 = m输入w.f创建键盘();
		m鼠标 = m输入w.f创建鼠标();
		m触摸 = m输入w.f创建触摸();
		m手柄 = m输入x.f创建手柄();
		m键盘接口.f初始化(*m键盘);
		m鼠标接口.f初始化(*m鼠标);
		m触摸接口.f初始化(*m触摸);
		m手柄接口.f初始化(*m手柄);
		//m音频接口.f初始化(m音频, m播放控制);
		//m音频接口.f添加声音(用户界面::E声音::e方向键切换按键焦点, L"选择.wav");
		m计时器.f重置(c帧秒);
		m计帧器.f重置();
		m文本工厂.f初始化();
		二维::S文本格式参数 v文本格式;
		v文本格式.fs字号(10);
		m文本格式 = m文本工厂.fc文本格式(v文本格式);
		m图形接口.f初始化(m二维);
		ma图片.f添加(L"设置", m图形接口.f创建图片(L"设置.png"));
		m用户界面.f初始化();
		m用户界面.fs图形(m图形接口);
		//m用户界面.fs音频(m音频接口);
		m用户界面.f输入_s键盘接口(m键盘接口);
		m用户界面.f输入_s鼠标接口(m鼠标接口);
		m用户界面.f输入_s触摸接口(m触摸接口);
		m用户界面.f输入_s手柄接口(m手柄接口);
		m用户界面.f新建窗口(*ma窗口[0]);
	}
	void f运行() {
		//消息循环
		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		while (msg.message != WM_QUIT) {	//消息循环
			if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {	//有消息时的处理,不要修改
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			} else {	//没有消息时的处理
				if (m计时器.f滴答()) {
					m帧速率 = m计帧器.f计算();
					f计算();
					f更新();
					f显示();
				}
			}
		}	//消息循环结束
	}
	void f销毁() {
		//v二维.f销毁();
		//v输入.f销毁();
	}
	void f计算() {
		m播放控制.f刷新();
		m输入w.f更新();
		m输入x.f更新();
		m键盘接口.f更新();
		m鼠标接口.f更新();
		m触摸接口.f更新();
		m手柄接口.f更新();
		m用户界面.f计算();
	}
	void f更新() {
		m用户界面.f更新();
	}
	void f显示() {
		auto &v渲染控制 = m二维.fg渲染控制();
		v渲染控制.f开始();
		v渲染控制.f清屏();
		auto v画图形 = m二维.fc画图形();
		auto v画文本 = m二维.fc画文本();
		v画图形->fs颜色(t颜色(1, 1, 1, 1));
		//鼠标十字
		const t向量2 v鼠标坐标 = {m鼠标->fg坐标().x, m鼠标->fg坐标().y};
		v画图形->f绘制线条({v鼠标坐标 + t向量2{16, 0}, v鼠标坐标 + t向量2{-16, 0}});
		v画图形->f绘制线条({v鼠标坐标 + t向量2{0, 16}, v鼠标坐标 + t向量2{0, -16}});
		//文本
		v画文本->fs格式(m文本格式.Get());
		std::wstring v文本 = L"x= ";
		v文本 += std::to_wstring(v鼠标坐标.x);
		v文本 += L"\ny= ";
		v文本 += std::to_wstring(v鼠标坐标.y);
		v画文本->fs区域(v鼠标坐标 + t向量2{8, 0});
		v画文本->f绘制文本(v文本);
		//帧速率
		v文本 = std::to_wstring(m帧速率);
		v画文本->fs区域(v鼠标坐标 + t向量2{0, -32});
		v画文本->f绘制文本(v文本);
		//界面
		m用户界面.f显示();
		//结束
		v渲染控制.f结束();
	}
};
//==============================================================================
// 程序
//==============================================================================
std::unique_ptr<C程序::C实现> C程序::m实现;
void C程序::f初始化(HINSTANCE p) {
	m实现 = std::make_unique<C实现>(p);
	m实现->f创建窗口();
	m实现->f初始化();
}
void C程序::f运行() {
	m实现->f运行();
}
void C程序::f销毁() {
	m实现.reset();
}
用户界面::W窗口 &C程序::fg窗口(int a) {
	return *m实现->ma窗口[a];
}
//==============================================================================
// 主函数
//==============================================================================
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int) {
	C程序::f初始化(hInst);
	C程序::f运行();
	C程序::f销毁();
}
