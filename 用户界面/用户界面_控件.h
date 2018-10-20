#pragma once
#include "用户界面_头.h"
#include "用户界面_基础.h"
namespace 用户界面 {
//==============================================================================
// 控件基类
//==============================================================================
class C控件文本 {
public:
	static constexpr float c字号 = 10;
	C控件文本() = default;
	C控件文本(const std::wstring &, float 字号 = c字号, E对齐 对齐 = e居中);
	void f属性_s空文本();
	void f属性_s文本(const std::wstring &文本, float 字号, E对齐 对齐 = e居中);
	void f属性_s文本内容(const std::wstring &);
	void f属性_s文本字号(float);
	void f属性_s文本对齐(E对齐);
	bool f属性_i有文本() const;
protected:
	std::wstring m文本 = L"未命名控件";
	float m字号 = c字号;
	E对齐 m对齐 = e居左;
};
//==============================================================================
// 各种控件
//==============================================================================
//标签
class W标签 : public W窗口, public C控件文本 {
public:
	W标签(int = -1, int = 0);
	void f响应_显示(const S显示参数 &) const override;
	void f属性_s透明度(float);
	float m透明度 = 1;
};
//按钮
class W按钮 : public W窗口, public C控件文本 {
public:
	static constexpr float c建议高度 = 24;
	W按钮(int = -1, int = 0);
	void f响应_显示(const S显示参数 &) const override;
	void f响应_鼠标按下(const S按键参数 &) override;
	void f响应_鼠标松开(const S按键参数 &) override;
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
	void f属性_s布局(const t向量2 &, const t向量2 &) override;
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
	void f属性_s布局(const t向量2 &, const t向量2 &) override;
	t向量2 m鼠标坐标;
	t向量2 m被动坐标;	//被其它窗口改变的坐标,有平滑移动
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
//滚动条
class W垂直滚动条 : public W窗口 {
public:
	enum E标志 {
		e使用滑块 = e自定义
	};
	enum E控件编号 {
		e向上,
		e向下,
		e滑块
	};
	static constexpr float c字号 = 10;
	static constexpr int c按钮滚动百分比 = 5;
	static constexpr int c空白滚动百分比 = 20;
	static constexpr float c边长 = 16;
	W垂直滚动条(int = -1, int = 0);
	void f事件_窗口移动(W窗口 &, const t向量2 &) override;
	void f事件_按键(W窗口 &, const S按键参数 &) override;
	void f响应_初始化() override;
	void f响应_计算() override;
	void f属性_s布局(const t向量2 &, const t向量2 &) override;
	void f属性_s布局(W窗口*, float, float);	//垂直滚动条附着在窗口右边
	void f属性_s滚动条(int 最大位置, int 显示范围);
	void f属性_s当前位置(int);
	void f属性_s滑块位置(int);
	int f属性_g滑块位置();
	void f属性_使用滚动条(bool);
	W连击按钮 w向上按钮{e向上, c按钮滚动百分比};
	W连击按钮 w向下按钮{e向下, c按钮滚动百分比};
	W连击按钮 w向上空白{e向上, c空白滚动百分比};
	W连击按钮 w向下空白{e向下, c空白滚动百分比};
	W滑动块 w滑块{e滑块};
	int m最大位置;
	int m当前位置;	//值范围[0, 最大)
	int m显示范围;
	float m滑块移动范围;
};
//下拉列表
class W下拉列表 : public W窗口 {
public:
	enum E标志 {
		e下拉 = W窗口::e自定义,
		e更新列表,
	};
	enum E控件编号 {
		e中心按钮,
		e下拉按钮
	};
	static constexpr float c字号 = 14;
	W下拉列表(int = -1, int = 0);
	void f事件_按键(W窗口 &, const S按键参数 &) override;
	void f响应_初始化() override;
	bool f响应_i范围内(const t向量2 &) override;
	void f响应_鼠标松开(const S按键参数 &) override;
	void f属性_s列表(const std::vector<std::wstring> &);
	std::vector<std::wstring> &f属性_g列表();
	const std::vector<std::wstring> &f属性_g列表() const;
	t标志::reference f下拉状态();
	float f下拉时底部范围();	//是负数
	bool f下拉时范围内(const t向量2 &);
	float f下拉时半高度();
	void f开始下拉();
	void f结束下拉();
	std::wstring &f属性_g选中文本();
	std::vector<std::wstring> ma文本;
	std::vector<W按钮> ma下拉按钮;
	W按钮 w中心按钮{e中心按钮};
	W标签 w标签;
	int m选择项 = 0;
	int m焦点项 = -1;
};
}