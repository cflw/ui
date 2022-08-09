module;
#include "用户界面_控件.h"
#include "用户界面_布局.h"
#include "用户界面_引擎.h"
export module 用户界面.控件.下拉列表;
import 用户界面.控件常量;
export namespace 用户界面 {
//==============================================================================
// 声明
//==============================================================================
class W下拉列表 : public W窗口框架 {
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
	void f响应_方向键(const S方向键参数 &) override;
	void f属性_s列表(const std::vector<std::wstring> &);
	std::vector<std::wstring> &f属性_g列表();
	const std::vector<std::wstring> &f属性_g列表() const;
	t标志::reference fi下拉();
	float f下拉时_g底部范围();	//是负数
	bool f下拉时_i范围内(const t向量2 &);
	float f下拉时_g半高度();
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
}	//namespace 用户界面
module : private;
namespace 用户界面 {
//==============================================================================
// 下拉列表
//==============================================================================
W下拉列表::W下拉列表(int n, int v): W窗口框架(n, v) {
	fs按键切换(E按键切换::e序号);
}
void W下拉列表::f事件_按键(W窗口 &a窗口, const S按键参数 &a按键) {
	auto v下拉 = fi下拉();
	switch (a按键.m按键) {
	case E按键::e确定: {
		if (v下拉) {
			if (a窗口.m标识 == e下拉按钮) {
				m焦点项 = a窗口.m值;
			}
			f结束下拉();
		} else {
			f开始下拉();
		}
		break;
	}
	case E按键::e取消:
		if (v下拉) {
			f结束下拉();
		} else {
			m父窗口->f事件_按键(*this, a按键);
		}
		break;
	}
}
void W下拉列表::f响应_初始化() {
	w中心按钮.f属性_s文本(f属性_g选中文本(), c字号, e居左);
	w中心按钮.f属性_s布局({t向量2::c零, m尺寸});
	w中心按钮.f标志_s继承显示();
	w中心按钮.f动作_显示();
	f动作_添加窗口(w中心按钮);
	w标签.f属性_s文本(c向下空三角, c字号, e居右);
	w标签.f属性_s布局({t向量2::c零, m尺寸 + t向量2(-4, 0)});
	w标签.f属性_s透明度(0.5f);
	w标签.f标志_s继承显示();
	w标签.f动作_显示();
	f动作_添加窗口(w标签);
}
bool W下拉列表::f响应_i范围内(const t向量2 &a坐标) {
	return m标志[e下拉];
}
void W下拉列表::f响应_方向键(const S方向键参数 &a方向键) {
	if (auto v下拉 = fi下拉()) {
		f按键切换计算(a方向键);
	} else {
		m父窗口->f响应_方向键(a方向键);
	}
}
void W下拉列表::f属性_s列表(const std::vector<std::wstring> &a列表) {
	ma文本 = a列表;
	m标志[e更新列表] = false;
}
std::vector<std::wstring> &W下拉列表::f属性_g列表() {
	m标志[e更新列表] = false;
	return ma文本;
}
const std::vector<std::wstring> &W下拉列表::f属性_g列表() const {
	return ma文本;
}
t标志::reference W下拉列表::fi下拉() {
	return m标志[e下拉];
}
float W下拉列表::f下拉时_g底部范围() {
	return -f下拉时_g半高度() * 2 + m尺寸.y;
}
bool W下拉列表::f下拉时_i范围内(const t向量2 &a坐标) {
	if (m尺寸.x < abs(a坐标.x)) {
		return false;
	} else if (m尺寸.y < a坐标.y) {
		return false;
	} else if (f下拉时_g底部范围() > a坐标.y) {
		return false;
	} else {
		return true;
	}
}
float W下拉列表::f下拉时_g半高度() {
	return m尺寸.y * (ma文本.size() + 1);
}
void W下拉列表::f开始下拉() {
	auto v下拉 = fi下拉();
	assert(!v下拉);
	//更新列表
	if (m标志[e更新列表] == false || ma文本.size() != ma下拉按钮.size()) {
		int v值 = 0;
		C单向移动布局 v布局;
		v布局.f属性_s单格布局({0, -m尺寸.y}, m尺寸);
		v布局.f属性_s倍数移动(0, -1);
		ma下拉按钮.clear();
		for (auto &v文本 : ma文本) {
			W按钮 &v按钮 = ma下拉按钮.emplace_back(e下拉按钮, v值);
			v按钮.f属性_s布局(v布局.f移动生成矩形());
			v按钮.f属性_s文本内容(v文本);
			v按钮.m动画.mf坐标 = C动画计算::f坐标_缩放;
			v按钮.f标志_s继承显示();
			++v值;
		}
		m标志[e更新列表] = true;
	}
	//添加
	float v延迟 = 0;
	for (auto &v按钮 : ma下拉按钮) {
		v按钮.f动作_显示(v延迟);
		f动作_添加窗口(v按钮);
		v延迟 += 0.25f;
	}
	//进入
	C用户界面 &v用户界面 = fg引擎();
	v用户界面.f设置活动窗口(*this);
	m焦点项 = m选择项;
	w标签.f属性_s文本内容(c向上空三角);
	v下拉 = true;
}
void W下拉列表::f结束下拉() {
	auto v下拉 = fi下拉();
	assert(v下拉);
	if (m焦点项 != m选择项) {
		m父窗口->f事件_窗口值变化(*this, m选择项, m焦点项);
		m选择项 = m焦点项;
		w中心按钮.f属性_s文本内容(f属性_g选中文本());
	}
	for (auto &v按钮 : ma下拉按钮) {
		v按钮.f动作_关闭();
	}
	C用户界面 &v用户界面 = fg引擎();
	v用户界面.f清除活动窗口();
	w标签.f属性_s文本内容(c向下空三角);
	v下拉 = false;
}
std::wstring &W下拉列表::f属性_g选中文本() {
	return ma文本[m选择项];
}
}	//namespace 用户界面