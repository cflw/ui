module;
#include "用户界面_控件.h"
#include "用户界面_布局.h"
#include "用户界面_引擎.h"
export module 用户界面.控件.垂直滚动条;
import 用户界面.控件常量;
export namespace 用户界面 {
//==============================================================================
// 复杂控件-滚动条
//==============================================================================
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
	static constexpr int c最大位置 = 1;
	static const S文本样式 c按钮文本样式;
	W垂直滚动条(int = -1, int = 0);
	void f事件_窗口移动(W窗口 &, const t向量2 &) override;
	void f事件_按键(W窗口 &, const S按键参数 &) override;
	void f响应_初始化() override;
	void f响应_计算() override;
	//属性
	void f属性_s布局(const S布局参数 &) override;
	void f属性_s布局(W窗口 &, float 上偏移, float 下偏移);	//垂直滚动条附着在窗口右边
	void f属性_s滚动值(int 最大位置, int 显示范围);	//滑块位置=[0,最大位置), 滚到底时最后一行在顶部
	void f属性_s容纳值(int 最大位置, int 显示范围);	//滑块位置=[0,最大位置-显示范围], 滚到底时最后一行在底部
	void f属性_s滚动值_(int 实际最大位置, int 显示最大位置, int 显示范围);
	void f属性_s当前位置(int);
	void f属性_s滑块位置(int, bool 平滑 = true);
	int f属性_g当前位置() const;	//实时位置
	int f属性_g滑块位置() const;	//动画位置,[0, 最大位置)
	void f属性_使用中间(bool);	//是否使用空白和滑块
	void f属性_使用全部(bool);	//是否使用全部
	bool f属性_i使用中间() const;
	bool f属性_i使用全部() const;
	//状态
	bool f状态_i滚动() const;	//是否发生滚动
	//动作
	void f动作_百分比滚动(int 百分比);
	void f动作_坐标滚动(float);
	void f更新滑块位置();
	W连击按钮 w向上按钮{e向上, c按钮滚动百分比};
	W连击按钮 w向下按钮{e向下, c按钮滚动百分比};
	W连击按钮 w向上空白{e向上, c空白滚动百分比};
	W连击按钮 w向下空白{e向下, c空白滚动百分比};
	W滑动块 w滑块{e滑块};
	int m最大位置 = 0;
	int m当前位置 = 0;	//值范围[0, 最大)
	int m上次位置 = 0;
	int m显示范围 = 0;
	float m滑块移动范围 = 0;
};
}	//namespace 用户界面
module : private;
namespace 用户界面 {
//==============================================================================
// 滚动条
//==============================================================================
const S文本样式 W垂直滚动条::c按钮文本样式 = {c字号, E对齐::e居中};
W垂直滚动条::W垂直滚动条(int n, int v): W窗口(n, v) {
	f标志_s纯鼠标();
	w向上按钮.f标志_s纯鼠标();
	w向上空白.f标志_s纯鼠标();
	w向下按钮.f标志_s纯鼠标();
	w向下空白.f标志_s纯鼠标();
	w向上空白.m标志[e显示边框] = false;
	w向下空白.m标志[e显示边框] = false;
	//动画函数默认值
	auto f设置动画 = [](W窗口 &a窗口) {
		C动画计算 &v动画计算 = a窗口.m动画;
		v动画计算.mf坐标 = C动画计算::f坐标_缩放;
		v动画计算.mf尺寸 = C动画计算::f尺寸_缩放;
	};
	f设置动画(w向上按钮);
	f设置动画(w向上空白);
	f设置动画(w向下按钮);
	f设置动画(w向下空白);
	f设置动画(w滑块);
	//向上向下按钮的文本
	auto f设置按钮 = [](W连击按钮 &a按钮, const std::wstring &a文本) {
		a按钮.f属性_s文本(a文本, c按钮文本样式);
		a按钮.f属性_s连击间隔(0.5f, 0.1f);
	};
	f设置按钮(w向上按钮, c向上实三角);
	f设置按钮(w向下按钮, c向下实三角);
	f设置按钮(w向上空白, L"");
	f设置按钮(w向下空白, L"");
	w滑块.f属性_s空文本();
}
void W垂直滚动条::f事件_窗口移动(W窗口 &a窗口, const t向量2 &) {
	f属性_s当前位置(f属性_g滑块位置());
}
void W垂直滚动条::f事件_按键(W窗口 &a窗口, const S按键参数 &a按键) {
	if (a按键.m按键 == E按键::e确定) {
		switch (a窗口.m标识) {
		case e向上:
			f动作_百分比滚动(-a窗口.m值);
			break;
		case e向下:
			f动作_百分比滚动(a窗口.m值);
			break;
			//case e滑块:
				//	m父窗口->f事件_按键确定(this);
				//	break;
		}
	}
}
void W垂直滚动条::f响应_初始化() {
	f动作_添加窗口(w向上按钮, true);
	f动作_添加窗口(w向下按钮, true);
	f动作_添加窗口(w向上空白, true);
	f动作_添加窗口(w向下空白, true);
	f动作_添加窗口(w滑块, true);
}
void W垂直滚动条::f响应_计算() {
	m上次位置 = m当前位置;
	//矫正滑块坐标
	t向量2 &v滑块坐标0 = w滑块.m坐标;
	t向量2 &v滑块坐标1 = w滑块.m被动坐标;
	v滑块坐标0.x = 0;
	v滑块坐标1.x = 0;
	const float v滑块半移动范围 = m滑块移动范围 / 2;
	if (v滑块坐标0.y > v滑块半移动范围) {
		v滑块坐标0.y = v滑块坐标1.y = v滑块半移动范围;
	} else if (v滑块坐标0.y < -v滑块半移动范围) {
		v滑块坐标0.y = v滑块坐标1.y = -v滑块半移动范围;
	}
	//空白
	const float v空白范围 = m尺寸.y - c边长 * 2;
	const float v空白半范围 = v空白范围 / 2;
	const float v滑块半高 = w滑块.m尺寸.y / 2;
	const float v滑块上 = v滑块坐标0.y + v滑块半高;	//y坐标
	const float v滑块下 = v滑块坐标0.y - v滑块半高;	//y坐标
	w向上空白.f属性_s布局({t向量2(0, (v空白半范围 + v滑块上) / 2), t向量2(m尺寸.x, v空白半范围 - v滑块上)});
	w向下空白.f属性_s布局({t向量2(0, (-v空白半范围 + v滑块下) / 2), t向量2(m尺寸.x, v空白半范围 + v滑块下)});
}
void W垂直滚动条::f属性_s布局(const S布局参数 &a参数) {
	//滚动条
	m坐标 = a参数.m坐标;
	m尺寸 = a参数.m尺寸;
	if (m尺寸.x < c边长) {
		m尺寸.x = c边长;
	}
	const float c双高 = c边长 * 2;
	if (m尺寸.y < c双高) {
		m尺寸.y = c双高;
		f属性_使用中间(false);
	} else {
		f属性_使用中间(true);
	}
	//子窗口
	const float v按钮坐标y = m尺寸.y / 2 - c边长 / 2;
	const t向量2 v按钮尺寸{m尺寸.x, c边长};
	w向上按钮.f属性_s布局({t向量2(0, v按钮坐标y), v按钮尺寸});
	w向下按钮.f属性_s布局({t向量2(0, -v按钮坐标y), v按钮尺寸});
	w滑块.f属性_s布局({w向上按钮.m坐标, v按钮尺寸});
}
void W垂直滚动条::f属性_s布局(W窗口 &a窗口, float a上偏移, float a下偏移) {
	const t向量2 v坐标{(a窗口.m尺寸.x - c边长) * 0.5f, (a上偏移 + a下偏移) * 0.5f};
	const t向量2 v尺寸{c边长, a窗口.m尺寸.y + a上偏移 - a下偏移};
	this->f属性_s布局({v坐标, v尺寸});
}
void W垂直滚动条::f属性_s滚动值(int a最大位置, int a显示范围) {
	f属性_s滚动值_(a最大位置, a最大位置, a显示范围);
}
void W垂直滚动条::f属性_s容纳值(int a最大位置, int a显示范围) {
	f属性_s滚动值_(a最大位置 - a显示范围 + 1, a最大位置, a显示范围);
}
void W垂直滚动条::f属性_s滚动值_(int a实际最大位置, int a最大位置, int a显示范围) {
	const int v滑块位置 = f属性_g滑块位置();
	m最大位置 = std::max<int>(a实际最大位置, c最大位置);
	m显示范围 = a显示范围;
	if (a最大位置 <= a显示范围) {
		f属性_使用全部(false);
		f属性_s当前位置(0);
		m滑块移动范围 = 0;
	} else {
		f属性_使用全部(true);
		const float v滑块最大范围 = m尺寸.y - c边长 * 2;
		const float v滑块范围百分比 = (float)a显示范围 / (float)a最大位置;
		w滑块.m尺寸.y = v滑块最大范围 * v滑块范围百分比;
		m滑块移动范围 = v滑块最大范围 - w滑块.m尺寸.y;
		f属性_s当前位置(v滑块位置);
		f属性_s滑块位置(v滑块位置, false);
	}
}
void W垂直滚动条::f属性_s当前位置(int a位置) {
	int v目标 = a位置;
	if (v目标 < 0) {
		v目标 = 0;
	} else if (v目标 >= m最大位置) {
		v目标 = m最大位置 - 1;
	}
	if (m当前位置 != v目标) {
		m父窗口->f事件_窗口值变化(*this, m当前位置, v目标);
		m当前位置 = v目标;
	}
}
void W垂直滚动条::f属性_s滑块位置(int a位置, bool a平滑) {
	const float v百分比位置 = (float)a位置 / (float)(m最大位置 - 1);
	w滑块.m被动坐标.y = m滑块移动范围 / 2 - v百分比位置 * m滑块移动范围;
	if (!a平滑) {
		w滑块.m坐标.y = w滑块.m被动坐标.y;
	}
}
int W垂直滚动条::f属性_g当前位置() const {
	return m当前位置;
}
int W垂直滚动条::f属性_g滑块位置() const {
	if (m滑块移动范围 == 0) {
		return 0;
	}
	const float v百分比位置 = 0.5f - w滑块.m坐标.y / m滑块移动范围;
	const int v最大值 = m最大位置 - 1;
	const int v滑块位置 = (int)(v百分比位置 * (float)v最大值 + 0.5f);
	return 数学::f夹取<int>(v滑块位置, 0, v最大值);
}
void W垂直滚动条::f属性_使用中间(bool a) {
	const bool v非 = !a;
	m标志[e使用滑块] = a;
	w向上按钮.f动作_禁用(v非);
	w向下按钮.f动作_禁用(v非);
	if (a) {
		w向上空白.f动作_显示();
		w向下空白.f动作_显示();
		w滑块.f动作_显示();
	} else {
		w向上空白.f动作_隐藏(false);
		w向下空白.f动作_隐藏(false);
		w滑块.f动作_隐藏(false);
	}
}
void W垂直滚动条::f属性_使用全部(bool a) {
	const bool v非 = !a;
	w向上按钮.f动作_禁用(v非);
	w向下按钮.f动作_禁用(v非);
	w向上空白.f动作_禁用(v非);
	w向下空白.f动作_禁用(v非);
	w滑块.f动作_禁用(v非);
	if (a) {
		f动作_显示();
		w向上按钮.f动作_显示();
		w向下按钮.f动作_显示();
		w向上空白.f动作_显示();
		w向下空白.f动作_显示();
		w滑块.f动作_显示();
	} else {
		f动作_隐藏();
		w向上按钮.f动作_隐藏();
		w向下按钮.f动作_隐藏();
		w向上空白.f动作_隐藏();
		w向下空白.f动作_隐藏();
		w滑块.f动作_隐藏();
	}
}
bool W垂直滚动条::f属性_i使用中间() const {
	return !w滑块.m标志[W窗口::e消失];
}
bool W垂直滚动条::f属性_i使用全部() const {
	return !w向上按钮.m标志[W窗口::e消失];
}
bool W垂直滚动条::f状态_i滚动() const {
	return m上次位置 != m当前位置;
}
void W垂直滚动条::f动作_百分比滚动(int a百分比) {
	int v移动 = m最大位置 * a百分比 / 100;
	if (a百分比 > 0 && v移动 < 1) {
		v移动 = 1;
	} else if (a百分比 < 0 && v移动 > -1) {
		v移动 = -1;
	}
	f属性_s当前位置(m当前位置 + v移动);
	f更新滑块位置();
}
void W垂直滚动条::f动作_坐标滚动(float a坐标) {
	const float v总高 = (float)m最大位置 / (float)m显示范围 * m尺寸.y;	//总高/布局高=最大位置/显示范围
	const float v移动 = a坐标 / v总高 * m滑块移动范围;	//滑块移动坐标/滑块移动范围=a移动坐标/总高
	w滑块.m被动坐标.y += v移动;
	f事件_窗口移动(w滑块, {0, v移动});
}
void W垂直滚动条::f更新滑块位置() {
	if (f属性_g滑块位置() != m当前位置) {
		f属性_s滑块位置(m当前位置);
	}
}
}	//namespace 用户界面