#include "用户界面_引擎.h"
#include "用户界面_控件.h"
#include "用户界面_布局.h"
namespace 用户界面 {
const std::wstring c向下实三角 = L"▼";
const std::wstring c向上实三角 = L"▲";
const std::wstring c向左实三角 = L"◀";
const std::wstring c向右实三角 = L"▶";
const std::wstring c向下空三角 = L"▽";
const std::wstring c向上空三角 = L"△";
const std::wstring c向左空三角 = L"◁";
const std::wstring c向右空三角 = L"▷";
const std::wstring c正确 = L"√";
const std::wstring c错误 = L"×";
//==============================================================================
// 控件文本
//==============================================================================
C控件文本::C控件文本(const std::wstring &a文本, float a字号, E对齐 a对齐):
	m文本(a文本), m字号(a字号), m对齐(a对齐) {
}
void C控件文本::f属性_s空文本() {
	m文本.clear();
}
void C控件文本::f属性_s文本(const std::wstring &a文本, float a字号, E对齐 a对齐) {
	assert(a字号 > 1);
	f属性_s文本内容(a文本);
	f属性_s文本字号(a字号);
	f属性_s文本对齐(a对齐);
}
void C控件文本::f属性_s文本内容(const std::wstring &a文本) {
	m文本 = a文本;
}
void C控件文本::f属性_s文本字号(float a字号) {
	//assert(C中文字号表::f范围内(a字号));
	m字号 = a字号;
}
void C控件文本::f属性_s文本对齐(E对齐 a对齐) {
	m对齐 = a对齐;
}
bool C控件文本::f属性_i有文本() const {
	return !m文本.empty();
}
//==============================================================================
// 标签
//==============================================================================
W标签::W标签(int n, int v): W窗口(n, v), C控件文本(L"标签") {
}
void W标签::f响应_显示(const S显示参数 &a) const {
	a.m画界面.f绘制文本(m文本, fg动画矩形(), a.m主题.fg颜色(1, 1, m切换.fg透明度() * m透明度), {m字号, m对齐});
}
void W标签::f属性_s透明度(float a) {
	m透明度 = a;
}
//==============================================================================
// 按钮
//==============================================================================
W按钮::W按钮(int n, int v): W窗口(n, v), C控件文本(L"按钮") {
	m标志[e禁用] = false;
}
void W按钮::f响应_显示(const S显示参数 &a) const {
	if (m尺寸.x == 0 || m尺寸.y == 0) {
		return;
	}
	const float v按下 = m标志[e鼠标按下] ? 0.2f : 0;
	const float v切换透明 = m切换.fg透明度();
	const t矩形 &v动画矩形 = fg动画矩形();
	//背景
	const t颜色 v背景色 = a.m主题.fg颜色(0, (m标志[e鼠标按下] ? 0.3f : 0.5f), m焦点渐变.f插值(0.2f, 0.5f) * v切换透明);
	if (f标志_i显示背景()) {
		a.m画界面.f填充矩形(v动画矩形, v背景色);
	}
	//前景
	const t颜色 v前景色 = a.m主题.fg颜色(1, 1, m焦点渐变.f插值(0.8f, 1) * v切换透明);
	if (f标志_i显示边框()) {
		a.m画界面.f绘制矩形(v动画矩形, v前景色);
	}
	//文本
	if (f属性_i有文本()) {
		a.m画界面.f绘制文本(m文本, v动画矩形, v前景色, {m字号, m对齐});
	}
}
void W按钮::f响应_鼠标按下(const S按键参数 &a) {
	if (m鼠标按键 != E按键::e无) {
		return;
	}
	if (m标志[e鼠标范围]) {
		m鼠标按键 = a.m按键;
		m标志[e鼠标按下] = true;
	}
}
void W按钮::f响应_鼠标松开(const S按键参数 &a) {
	if (m鼠标按键 != a.m按键) {
		return;
	}
	if (m标志[e鼠标按下] && m标志[e鼠标范围]) {
		m父窗口->f事件_按键(*this, a);
	}
	m标志[e鼠标按下] = false;
	m鼠标按键 = E按键::e无;
}
//==============================================================================
// 文本框
//==============================================================================
W文本框::W文本框(int n, int v) : W窗口(n, v) {
	m标志[e禁用] = false;
}
float W文本框::f按行计算高度(int a行数) {
	return a行数 * c行高度 + c边距 * 2;
}
void W文本框::f响应_显示(const S显示参数 &a) const {
	const float v切换透明 = m切换.fg透明度();
	const float v透明度 = m焦点渐变.f插值(0.5f, 1) * v切换透明;
	const t矩形 &v动画矩形 = fg动画矩形();
	const t矩形 &v文本矩形 = fg动画矩形(t向量2::c零, t向量2::fc相同(-c边距));
	//边框
	if (m标志[e显示边框]) {
		const t颜色 v边框颜色 = a.m主题.fg颜色(1, m焦点渐变.f插值(0.5f, 1), m焦点渐变.f插值(0.5f, 0.8f) * v切换透明);
		a.m画界面.f绘制矩形(v动画矩形, v边框颜色);
	}
	//文本
	if (!m文本.empty()) {
		const t颜色 v文本颜色 = a.m主题.fg颜色(1, 1, m焦点渐变.f插值(0.5f, 1) * v切换透明);
		a.m画界面.f绘制文本(m文本, v文本矩形, v文本颜色, {c字号, e居左});
	}
	const t颜色 v字数颜色 = a.m主题.fg颜色(1, 0.5f, m焦点渐变.f插值(0.0f, 0.8f) * v切换透明);
	a.m画界面.f绘制文本(std::to_wstring(m限制字数 - m文本.size()), v文本矩形, v字数颜色, {c字号, e居右});
}
void W文本框::f响应_字符(const std::vector<wchar_t> &aa字符) {
	for (const auto &v字符 : aa字符) {
		switch (v字符) {
		case '\b':
			if (!m文本.empty()) {
				m文本.pop_back();
			}
			break;
		case '\r':
			if (!m标志[e多行]) {
				break;
			}
		default:
			if (m文本.size() < m限制字数) {
				m文本.push_back(v字符);
			}
			break;
		}
	}
}
void W文本框::f属性_s布局(const t向量2 &a坐标, const t向量2 &a范围) {
	t向量2 v范围 = a范围;
	if (v范围.y < c最小高度) {
		v范围.y = c最小高度;
	}
	const float v行数 = floor(v范围.y / c行高度);
	if (v行数 > 1) {
		f属性_s多行(true);
	}
	W窗口::f属性_s布局(a坐标, v范围);
}
void W文本框::f属性_s多行(bool a) {
	m标志[e多行] = a;
}
void W文本框::f属性_s限制字数(size_t a) {
	m限制字数 = a;
}
//==============================================================================
// 虚拟键盘
//==============================================================================
W虚拟键盘::W虚拟键盘() {
	//数字

}
//==============================================================================
// 连击按钮
//==============================================================================
W连击按钮::W连击按钮(int n, int v) : W按钮(n, v) {
}
void W连击按钮::f属性_s连击间隔(float a首次, float a每次) {
	m首次 = a首次;
	if (a每次 <= 0) {
		m每次 = a首次;
	} else {
		m每次 = a每次;
	}
}
void W连击按钮::f响应_计算() {
	if (fi按下()) {
		C用户界面 &v用户界面 = fg引擎();
		const float v间隔 = v用户界面.fg计算秒();
		const float &v时间 = (m次数 == 0) ? m首次 : m每次;
		m计时 += v间隔;
		if (m计时 >= v时间) {
			f确定回调({E按键来源::e无, E按键::e确定});
			m计时 -= v时间;
			++m次数;
		}
	}
}
void W连击按钮::f响应_按键(const S按键参数 &a) {
	if (a.m按键 == E按键::e确定) {
		f动作_连击重置();
		f确定回调(a);
	}
}
void W连击按钮::f响应_鼠标按下(const S按键参数 &a) {
	if (m标志[e鼠标范围]) {
		f响应_按键(a);
		m标志[e鼠标按下] = true;
	}
}
void W连击按钮::f响应_鼠标松开(const S按键参数 &) {
	m标志[e鼠标按下] = false;
}
void W连击按钮::f动作_连击重置() {
	m计时 = 0;
	m次数 = 0;
}
void W连击按钮::f确定回调(const S按键参数 &a) {
	assert(a.m按键 == E按键::e确定);
	m父窗口->f事件_按键(*this, a);
}
//==============================================================================
// 滑动块
//==============================================================================
W滑动块::W滑动块(int n, int v): W按钮(n, v) {
	m标志[e鼠标] = true;
}
void W滑动块::f响应_初始化() {
	m被动坐标 = m坐标;
}
void W滑动块::f响应_计算() {
	if (!m标志[e鼠标按下]) {
		m坐标.fs倍数渐变(m被动坐标, 0.1f);
	}
}
bool W滑动块::f响应_i范围内(const t向量2 &a) {
	if (m标志[e鼠标按下]) {
		if (m鼠标坐标 != a) {
			const t向量2 v移动 = a - m鼠标坐标;
			m坐标 += v移动;
			m父窗口->f事件_窗口移动(*this, v移动);
			m被动坐标 = m坐标;
		}
	}
	return W窗口::f响应_i范围内(a);
}
void W滑动块::f响应_鼠标按下(const S按键参数 &a) {
	if (a.m按键 == E按键::e确定 && m标志[e鼠标范围]) {
		m鼠标坐标 = a.m坐标;
		m标志[e鼠标按下] = true;
	}
}
void W滑动块::f响应_鼠标松开(const S按键参数 &a) {
	if (m标志[e鼠标按下]) {
		m父窗口->f事件_按键(*this, a);
		m标志[e鼠标按下] = false;
	}
}
void W滑动块::f属性_s布局(const t向量2 &a坐标, const t向量2 &a范围) {
	m坐标 = a坐标;
	m被动坐标 = a坐标;
	m尺寸 = a范围;
}
//==============================================================================
// 复选框
//==============================================================================
W复选框::W复选框(int id, int v):
	W按钮(id, v) {
}
void W复选框::f响应_初始化() {
	f属性_s文本(f属性_g字符(), m尺寸.y, e居中);
}
void W复选框::f响应_按键(const S按键参数 &a) {
	switch (a.m按键) {
	case E按键::e确定:
		f属性_反选();
		m父窗口->f事件_按键(*this, a);
	default:
		W按钮::f响应_按键(a);
		break;

	}
}
void W复选框::f响应_鼠标按下(const S按键参数 &a) {
	switch (a.m按键) {
	case E按键::e确定:
		if (m标志[e鼠标范围]) {
			m标志[e鼠标按下] = true;
		}
		break;
	default:
		W按钮::f响应_鼠标按下(a);
		break;
	}
}
void W复选框::f响应_鼠标松开(const S按键参数 &a) {
	switch (a.m按键) {
	case E按键::e确定:
		if (m标志[e鼠标范围] && m标志[e鼠标按下]) {
			f属性_反选();
			m父窗口->f事件_按键(*this, a);
		}
		m标志[e鼠标按下] = false;
		break;
	default:
		W按钮::f响应_鼠标松开(a);
		break;
	}
}
void W复选框::f属性_反选() {
	const int v前 = m标志[e选中];
	int v后 = !v前;
	m父窗口->f事件_窗口值变化(*this, v前, v后);
	m标志[e选中] = v后;
	f属性_s文本内容(f属性_g字符());
}
bool W复选框::f属性_i选中() const {
	return m标志[e选中];
}
const std::wstring &W复选框::f属性_g字符() const {
	if (f属性_i选中()) {
		return c正确;
	} else {
		return c错误;
	}
}
//==============================================================================
// 滚动条
//==============================================================================
W垂直滚动条::W垂直滚动条(int n, int v): W窗口(n, v) {
	m标志[e鼠标] = true;
	w向上按钮.m标志[e鼠标] = true;
	w向上空白.m标志[e鼠标] = true;
	w向下按钮.m标志[e鼠标] = true;
	w向下空白.m标志[e鼠标] = true;
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
		a按钮.f属性_s文本(a文本, c字号, E对齐::e居中);
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
		auto f按键移动 = [&](int a百分比) {
			float v移动 = m最大位置 / 100;
			if (v移动 < 1) {
				v移动 = 1;
			}
			f属性_s当前位置(m当前位置 + v移动 * a百分比);
		};
		switch (a窗口.m标识) {
		case e向上:
			f按键移动(-a窗口.m值);
			break;
		case e向下:
			f按键移动(a窗口.m值);
			break;
		//case e滑块:
			//	m父窗口->f事件_按键确定(this);
			//	break;
		}
		if (f属性_g滑块位置() != m当前位置) {
			f属性_s滑块位置(m当前位置);
		}
	}
}
void W垂直滚动条::f响应_初始化() {
	f动作_添加窗口(w向上按钮);
	f动作_添加窗口(w向下按钮);
	f动作_添加窗口(w向上空白);
	f动作_添加窗口(w向下空白);
	f动作_添加窗口(w滑块);
}
void W垂直滚动条::f响应_计算() {
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
	w向上空白.f属性_s布局(t向量2(0, (v空白半范围 + v滑块上) / 2), t向量2(m尺寸.x, v空白半范围 - v滑块上));
	w向下空白.f属性_s布局(t向量2(0, (-v空白半范围 + v滑块下) / 2), t向量2(m尺寸.x, v空白半范围 + v滑块下));
}
void W垂直滚动条::f属性_s布局(const t向量2 &a坐标, const t向量2 &a范围) {
	//滚动条
	m坐标 = a坐标;
	m尺寸 = a范围;
	if (m尺寸.x < c边长) {
		m尺寸.x = c边长;
	}
	const float c双高 = c边长 * 2;
	if (m尺寸.y < c双高) {
		m尺寸.y = c双高;
		f属性_使用滚动条(false);
	} else {
		f属性_使用滚动条(true);
	}
	//子窗口
	const float v按钮坐标y = m尺寸.y / 2 - c边长 / 2;
	const t向量2 v按钮范围{m尺寸.x, c边长};
	w向上按钮.f属性_s布局(t向量2(0, v按钮坐标y), v按钮范围);
	w向下按钮.f属性_s布局(t向量2(0, -v按钮坐标y), v按钮范围);
	w滑块.f属性_s布局(w向上按钮.m坐标, v按钮范围);
}
void W垂直滚动条::f属性_s布局(W窗口 *a窗口, float a上偏移, float a下偏移) {
	t向量2 m坐标0{a窗口->m尺寸.x - c边长 / 2, a上偏移 + a下偏移};
	t向量2 m范围0{c边长, a窗口->m尺寸.y + a上偏移 - a下偏移};
	f属性_s布局(m坐标0, m范围0);
}
void W垂直滚动条::f属性_s滚动条(int a最大位置, int a显示范围) {
	m最大位置 = a最大位置;
	m显示范围 = a显示范围;
	if (a最大位置 <= a显示范围) {
		m标志[e显示] = false;
		m滑块移动范围 = 0;
	} else {
		m标志[e显示] = true;
		const float v滑块最大范围 = m尺寸.y - c边长 * 2;
		const float v滑块范围百分比 = (float)a显示范围 / (float)a最大位置;
		w滑块.m尺寸.y = v滑块最大范围 * v滑块范围百分比;
		m滑块移动范围 = v滑块最大范围 - w滑块.m尺寸.y;
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
void W垂直滚动条::f属性_s滑块位置(int a位置) {
	const float v百分比位置 = (float)a位置 / (float)(m最大位置 - 1);
	w滑块.m被动坐标.y = m滑块移动范围 / 2 - v百分比位置 * m滑块移动范围;
}
int W垂直滚动条::f属性_g滑块位置() {
	const float v百分比位置 = 0.5f - w滑块.m坐标.y / m滑块移动范围;
	return (int)(v百分比位置 * (float)(m最大位置 - 1) + 0.5f);
}
void W垂直滚动条::f属性_使用滚动条(bool a) {
	const bool v非 = !a;
	m标志[e使用滑块] = a;
	w向上按钮.f动作_禁用(v非);
	w向下按钮.f动作_禁用(v非);
	if (a) {
		w向上空白.f动作_显示();
		w向下空白.f动作_显示();
		w滑块.f动作_显示();
	} else {
		w向上空白.f动作_隐藏();
		w向下空白.f动作_隐藏();
		w滑块.f动作_隐藏();
	}
}
//==============================================================================
// 下拉列表
//==============================================================================
W下拉列表::W下拉列表(int n, int v): W窗口(n, v) {
	m标志[e禁用] = false;
	m标志[e鼠标] = true;
}
void W下拉列表::f事件_按键(W窗口 &a窗口, const S按键参数 &a按键) {
	switch (a按键.m按键) {
	case E按键::e确定: {
		auto v下拉 = f下拉状态();
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
		f结束下拉();
		break;
	}
}
void W下拉列表::f响应_初始化() {
	w中心按钮.f属性_s文本(f属性_g选中文本(), c字号, e居左);
	w中心按钮.f属性_s布局(t向量2::c零, m尺寸);
	w中心按钮.f标志_s继承显示();
	f动作_添加窗口(w中心按钮);
	w标签.f属性_s文本(c向下空三角, c字号, e居右);
	w标签.f属性_s布局(t向量2::c零, m尺寸 + t向量2(-4, 0));
	w标签.f属性_s透明度(0.5f);
	w标签.f标志_s继承显示();
	f动作_添加窗口(w标签);
}
bool W下拉列表::f响应_i范围内(const t向量2 &a坐标) {
	return false;
}
void W下拉列表::f响应_鼠标松开(const S按键参数 &a) {
	switch (a.m按键) {
	case E按键::e确定: {
		auto v下拉 = f下拉状态();
		if (v下拉) {
			if (!f下拉时范围内(a.m坐标)) {
				f事件_按键(*this, {a.m来源, E按键::e取消, a.m坐标});
			}
		}
		break;
	}
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
t标志::reference W下拉列表::f下拉状态() {
	return m标志[e下拉];
}
float W下拉列表::f下拉时底部范围() {
	return -f下拉时半高度() * 2 + m尺寸.y;
}
bool W下拉列表::f下拉时范围内(const t向量2 &a坐标) {
	if (m尺寸.x < abs(a坐标.x)) {
		return false;
	} else if (m尺寸.y < a坐标.y) {
		return false;
	} else if (f下拉时底部范围() > a坐标.y) {
		return false;
	} else {
		return true;
	}
}
float W下拉列表::f下拉时半高度() {
	return m尺寸.y * (ma文本.size() + 1);
}
void W下拉列表::f开始下拉() {
	auto v下拉 = f下拉状态();
	assert(v下拉 == false);
	//更新列表
	if (m标志[e更新列表] == false || ma文本.size() != ma下拉按钮.size()) {
		int v值 = 0;
		C单向移动布局 v布局;
		v布局.f属性_s布局({0, -m尺寸.y}, m尺寸);
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
	auto v下拉 = f下拉状态();
	assert(v下拉 == true);
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

}