#pragma once
#include "用户界面_头.h"
#include "用户界面_基础.h"
#include "用户界面_窗口.h"
namespace 用户界面 {
//==============================================================================
// 控件基类
//==============================================================================
class C控件文本 {
public:
	static const std::wstring c默认文本;
	C控件文本();
	C控件文本(const std::wstring &);
	C控件文本(const std::wstring &, const S文本样式 &);
	void f属性_s空文本();
	void f属性_s文本(const std::wstring_view &文本, const S文本样式 &);
	void f属性_s文本内容(const std::wstring_view &);
	void f属性_s文本样式(const S文本样式 &);
	bool f属性_i有文本() const;
	const std::wstring &fg文本() const;
	const S文本样式 &fg文本样式() const;
public:
	std::wstring m文本;	//本地存储的文本
	S文本样式 m样式 = {};
};
//专门的窗口容器类,会响应所有鼠标消息(窗口基类只响应部分消息)
class W窗口框架 : public W窗口 {
public:
	W窗口框架(int = -1, int = 0);
	void f响应_鼠标按下(const S按键参数 &) override;
	void f响应_鼠标松开(const S按键参数 &) override;
	bool f响应_i范围内(const t向量2 &) override;
};
//不显示,只响应的按钮
class W空白按钮 : public W窗口 {
public:
	W空白按钮(int = -1, int = 0);
	void f响应_鼠标按下(const S按键参数 &) override;
	void f响应_鼠标松开(const S按键参数 &) override;
	void f动作_按键(const S按键参数 &);
	void f动作_按键(E按键 = E按键::e确定);
};
//==============================================================================
// 基础控件
//==============================================================================
//标签
class W标签 : public W窗口, public C控件文本 {
public:
	static const std::wstring c默认文本;
	W标签(int = -1, int = 0);
	void f响应_显示(const S显示参数 &) const override;
	void f属性_s透明度(float);
	float m透明度 = 1;
};
//按钮
class W按钮 : public W空白按钮, public C控件文本 {
public:
	static const std::wstring c默认文本;
	static constexpr float c建议高度 = 24;
	W按钮(int = -1, int = 0);
	void f响应_显示(const S显示参数 &) const override;
};
//文本框
class W文本框 : public W窗口 {
public:
	enum E标志 {
		e多行 = W窗口::e自定义,
	};
	static constexpr float c行高度 = 14;
	static constexpr float c边距 = 2;
	static constexpr float c最小高度 = c行高度 + c边距 * 2;
	static constexpr float c字号 = 14;
	W文本框(int = -1, int = 0);
	static float f按行计算高度(int);
	void f响应_显示(const S显示参数 &) const override;
	void f响应_字符(const std::vector<wchar_t> &) override;
	void f属性_s布局(const S布局参数 &) override;
	void f属性_s多行(bool);
	void f属性_s限制字数(size_t);
	std::wstring m文本;
	size_t m限制字数 = 10;
};
//输入法
class W虚拟键盘 : public W窗口 {
public:
	enum E按键分布 {
		e数字 = 0,
		e字母 = 10,
		e功能 = 36
	};
	W虚拟键盘();
	W按钮 v按键[38];	//数字10+字母26+上档+退格
};
//连击按钮,按住会不断往父窗口发送按键确定事件
class W连击按钮 : public W按钮 {
public:
	W连击按钮(int = -1, int = 0);
	void f响应_计算() override;
	void f响应_按键(const S按键参数 &) override;
	void f响应_鼠标按下(const S按键参数 &) override;
	void f响应_鼠标松开(const S按键参数 &) override;
	void f属性_s连击间隔(float 首次, float 每次 = 0);
	void f动作_连击重置();
	void f确定回调(const S按键参数 &);
	float m首次;
	float m每次;
	float m计时;
	int m次数;
};
//滑动块,可以用鼠标按住拖动
class W滑动块 : public W按钮 {
public:
	W滑动块(int = -1, int = 0);
	void f响应_初始化() override;
	void f响应_计算() override;
	bool f响应_i范围内(const t向量2 &) override;
	void f响应_鼠标按下(const S按键参数 &) override;
	void f响应_鼠标松开(const S按键参数 &) override;
	void f属性_s布局(const S布局参数 &) override;
	t向量2 m鼠标坐标;
	t向量2 m被动坐标;	//被其它窗口改变的坐标,有平滑移动
};
//滑动块2,响应平移消息
class W滑动块2 : public W按钮 {
public:
	W滑动块2(int = -1, int = 0);
	void f响应_初始化() override;
	void f响应_计算() override;
	bool f响应_i范围内(const t向量2 &) override;
	void f响应_垂直平移(const S平移参数 &) override;
	void f响应_水平平移(const S平移参数 &) override;
	void f属性_s布局(const S布局参数 &) override;
	void f响应平移(const S平移参数 &, float (t向量2::*));
	t向量2 m被动坐标;
};
//复选框
class W复选框 : public W按钮 {
public:
	enum E标志 {
		e选中 = W窗口::e自定义,
		e自定义,
	};
	W复选框(int = -1, int = 0);
	void f响应_初始化() override;
	void f响应_按键(const S按键参数 &) override;
	void f响应_鼠标按下(const S按键参数 &) override;
	void f响应_鼠标松开(const S按键参数 &) override;
	void f属性_反选();
	bool f属性_i选中() const;
	const std::wstring &f属性_g字符() const;
};
}	//namespace 用户界面