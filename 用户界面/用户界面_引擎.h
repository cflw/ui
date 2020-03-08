#pragma once
#include <unordered_map>
#include "用户界面_头.h"
#include "用户界面_基础.h"
#include "用户界面_接口.h"
namespace 用户界面 {
//==============================================================================
// 用户界面
//==============================================================================
class C用户界面 {
public:
	static C用户界面 *g这;
	struct S活动信息 {
		W窗口 *m焦点;	//该活动窗口下的焦点窗口
	};
	struct S方向键变量 {
		输入::C按住重复 m重复;
		输入::C互斥键 m上下, m左右, m四向;
	};
	static constexpr float c帧秒 = 1.f / 60.f;
public:
	C用户界面();
	~C用户界面();
	void f初始化();
	void fs图形(I图形设备 &);
	void fs时钟频率(float 计算秒, float 渲染秒);	//影响时间的计算
	void fs主题(const S主题 &);
	void fs音频(I音频设备 &);
	void f输入_s键盘接口(I输入设备 &);
	void f输入_s鼠标接口(I输入设备 &);
	void f输入_s手柄接口(I输入设备 &);
	void f输入_s触摸接口(I输入设备 &);
	void f输入_接收字符(wchar_t);//在窗口过程WM_CHAR消息中调用
	void f计算();
	void f更新();
	void f显示();
	void f跟踪处理(W窗口 &);
	void f新建窗口_(W窗口 &);
	void f新建窗口(W窗口 &);
	void f新建窗口(W窗口 &父, W窗口 &子);
	void f删除窗口(W窗口 &);
	void f删除所有子窗口(W窗口 &父);
	void f切换窗口(W窗口 &);
	void f遍历所有窗口(const std::function<void(W窗口&)> &);
	void f遍历子窗口(W窗口 *, const std::function<void(W窗口&)> &);	//如果窗口为空,则遍历顶层窗口
	void f设置焦点窗口(W窗口 &);
	void f设置按键焦点窗口(W窗口 &);
	void f设置鼠标焦点窗口(W窗口 &);
	void f设置弱按键焦点窗口(W窗口 &);	//不会改变鼠标焦点
	void f设置活动窗口(W窗口 &);	//要切换窗口、进入子窗口，调用这个
	void f清除活动窗口();
	void f保存活动窗口信息();
	void f设置平移焦点窗口(W窗口 &);
	void f清除平移焦点窗口();
	void f窗口表排序();	//处理刚新建的窗口和要删除的窗口
	float fg计算秒() const;
	float fg渲染秒() const;
	t向量2 fg指针相对坐标(const W窗口 &) const;
	bool fi鼠标焦点按下() const;
	void f播放音效(E声音);
public:
	std::vector<W窗口*> ma窗口表;
	std::vector<W窗口*> ma新建窗口;	//新建的窗口先放这,下次计算再放到窗口表
	std::stack<W窗口*> m调用栈;
	std::map<W窗口*, S活动信息> ma活动窗口;
	std::vector<wchar_t> ma字符;
	W窗口 *m处理窗口 = nullptr;
	W窗口 *m按键焦点 = nullptr;
	W窗口 *m鼠标焦点 = nullptr;
	W窗口 *m平移焦点 = nullptr;
	W窗口 *m活动窗口 = nullptr;
	float m计算秒 = c帧秒, m渲染秒 = c帧秒;
	S方向键变量 m键盘方向键变量, m手柄方向键变量;
	I图形设备 *m图形 = nullptr;
	S主题 m主题 = S主题::c白;
	I音频设备 *m音频 = nullptr;
	I输入设备 *m键盘 = nullptr;
	I输入设备 *m鼠标 = nullptr;
	I输入设备 *m手柄 = nullptr;
	I输入设备 *m触摸 = nullptr;
	t向量2 m鼠标坐标, m触摸坐标;
	E按键 m鼠标按键 = E按键::e无;
	bool m窗口表变化 = false;
	bool m触摸按下 = false;
	int m总编号 = 0;
};
}	//namespace 用户界面