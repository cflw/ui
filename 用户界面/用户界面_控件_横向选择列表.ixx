﻿module;
#include <cflw工具_运算.h>
#include "用户界面_控件.h"
#include "用户界面_布局.h"
#include "用户界面_引擎.h"
export module 用户界面.控件.横向选择列表;
namespace 工具 = cflw::工具;
export namespace 用户界面 {
//==============================================================================
// 声明
//==============================================================================
class W横向选择列表 : public W窗口 {	//◀选项▶
public:
	static const S文本样式 c按钮文本样式;
	static const S文本样式 c选项文本样式;
	enum E标识 {
		e标签框,
		e左按钮,
		e右按钮,
	};
	class W显示框 : public W窗口, public C控件文本 {
	public:
		W显示框(int = -1, int = 0);
		void f响应_显示(const S显示参数 &) const override;
		void f响应_方向键(const S方向键参数 &) override;
	};
	static constexpr float c边长 = 16;
	W横向选择列表(int = -1, int = 0);
	void f事件_按键(W窗口 &, const S按键参数 &) override;
	void f响应_初始化() override;
	void f属性_s布局(const S布局参数 &) override;
	void f左();
	void f右();
	void f切换项(int &(*变化)(int &));
	std::vector<std::wstring> ma文本;
	W按钮 w左, w右;
	W显示框 w中;
	int m选择项 = 0;
};
}	//namespace 用户界面
module : private;
namespace 用户界面 {
//==============================================================================
// 显示框
//==============================================================================
W横向选择列表::W显示框::W显示框(int a标识, int a值):
	W窗口(a标识, a值) {
	m标志[e禁用] = false;
}
void W横向选择列表::W显示框::f响应_显示(const S显示参数 &a参数) const {
	const float v切换透明 = fg总切换().fg透明度();
	const t矩形 &v动画矩形 = fg动画矩形();
	//背景
	const t颜色 v背景色 = a参数.m主题.fg颜色(0, 0.5f, m焦点渐变.f插值(0.1f, 0.2f) * v切换透明);
	if (f标志_i显示背景()) {
		a参数.m图形.f填充矩形(v动画矩形, v背景色);
	}
	//前景
	if (f标志_i显示边框()) {
		a参数.m图形.f绘制矩形(v动画矩形, v背景色);
	}
	//文本
	const t颜色 v前景色 = a参数.m主题.fg颜色(1, 1, m焦点渐变.f插值(0.5f, 1) * v切换透明);
	if (f属性_i有文本()) {
		a参数.m图形.f绘制文本(fg文本(), v动画矩形, v前景色, fg文本样式());
	}
}
void W横向选择列表::W显示框::f响应_方向键(const S方向键参数 &a参数) {
	if (a参数.fi左右()) {
		S按键参数 v参数;
		v参数.m来源 = E按键来源::e无;
		v参数.m按键 = a参数.fi左() ? E按键::e左 : E按键::e右;
		v参数.m时间点 = E时间点::e一次;
		m父窗口->f事件_按键(*this, v参数);
	} else {
		m父窗口->f响应_方向键(a参数);
	}
}
//==============================================================================
// 列表
//==============================================================================
const S文本样式 W横向选择列表::c按钮文本样式 = {10, E对齐::e居中};
const S文本样式 W横向选择列表::c选项文本样式 = {14, E对齐::e居中};
W横向选择列表::W横向选择列表(int a标识, int a值):
	W窗口(a标识, a值),
	w左(e左按钮), w中(e标签框), w右(e右按钮) {
	w左.m标志[e可获得按键焦点] = false;
	w左.f属性_s文本(L"◀", c按钮文本样式);
	w右.m标志[e可获得按键焦点] = false;
	w右.f属性_s文本(L"▶", c按钮文本样式);
	w中.f属性_s文本样式(c选项文本样式);
}
void W横向选择列表::f事件_按键(W窗口 &a窗口, const S按键参数 &a参数) {
	switch (a窗口.m标识) {
	case e标签框:
		switch (a参数.m按键) {
		case E按键::e左:
			f左();
			break;
		case E按键::e右:
			f右();
			break;
		}
		break;
	case e左按钮:
		f左();
		break;
	case e右按钮:
		f右();
		break;
	}
}
void W横向选择列表::f响应_初始化() {
	assert(!ma文本.empty());
	f动作_添加窗口(w左);
	f动作_添加窗口(w右);
	f动作_添加窗口(w中);
	w左.f动作_显示();
	w右.f动作_显示();
	w中.f动作_显示();
	f动作_显示();
	w中.f属性_s文本内容(ma文本[m选择项]);
}
void W横向选择列表::f属性_s布局(const S布局参数 &a参数) {
	m坐标 = a参数.m坐标;
	m尺寸 = a参数.m尺寸;
	const float v边长 = m尺寸.y;
	const t矩形 v矩形 = t矩形::fc坐标尺寸(t向量2::c零, m尺寸);
	const float v左 = v矩形.fg左();
	const float v右 = v矩形.fg右();
	const float v上 = v矩形.fg上();
	const float v下 = v矩形.fg下();
	const float v标签左 = v左 + v边长;
	const float v标签右 = v右 - v边长;
	const t矩形 v左按钮 = t矩形::fc左上右下(v左, v上, v标签左, v下);
	w左.f属性_s布局(v左按钮);
	const t矩形 v右按钮 = t矩形::fc左上右下(v标签右, v上, v右, v下);
	w右.f属性_s布局(v右按钮);
	const t矩形 v中标签 = t矩形::fc左上右下(v标签左, v上, v标签右, v下);
	w中.f属性_s布局(v中标签);
}
void W横向选择列表::f左() {
	f切换项(工具::f自减<int>);
}
void W横向选择列表::f右() {
	f切换项(工具::f自增<int>);
}
void W横向选择列表::f切换项(int &(*af变化)(int &)) {
	int v选择项 = m选择项;
	af变化(v选择项);
	v选择项 = 数学::f环绕<int>(v选择项, 0, (int)ma文本.size());
	if (v选择项 == m选择项) {
		return;
	}
	m父窗口->f事件_窗口值变化(*this, m选择项, v选择项);
	if (v选择项 == m选择项) {
		return;
	}
	m选择项 = v选择项;
	w中.f属性_s文本内容(ma文本[v选择项]);
}
}	//namespace 用户界面