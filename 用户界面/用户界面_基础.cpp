#include "用户界面_头.h"
#include "用户界面_基础.h"
#include "用户界面_引擎.h"
#include "用户界面_按键切换.h"
namespace 用户界面 {
//==============================================================================
// 主题
//==============================================================================
const S主题 S主题::c白(t颜色(1, 1, 1, 1), t颜色(1, 1, 1, 1));
S主题::S主题(const t颜色 &a前景色, const t颜色 &a背景色):
	m前景色(a前景色),
	m背景色(a背景色) {
}
t颜色 S主题::fg颜色(float a插值, float a亮度, float a透明度) const {
	t颜色 v = 数学::f插值<t颜色>(m背景色, m前景色, a插值);
	v = v.f颜色分量乘(a亮度);
	v.a *= a透明度;
	return v;
}
//==============================================================================
// 切换动画变量
//==============================================================================
void C切换动画::f重置(float a延时) {
	m目标 = 0;
	m实际 = -1 - a延时;
}
void C切换动画::f计算(bool a结束, float a间隔) {
	m目标 += a间隔 * c切换速度;
	if (a结束) {
		if (m目标 < 1) {
			m目标 = 1;
		}
	} else {
		if (m目标 > 0) {
			m目标 = 0;
		}
	}
	const float v计算秒 = C用户界面::g这->fg计算秒();
	m实际 = 数学::f倍数渐变<float>(m实际, m目标, 10 * v计算秒, v计算秒);
}
bool C切换动画::fi已消失() const {
	return m实际 >= 1;
}
bool C切换动画::fi出现中() const {
	return m实际 < 0;
}
bool C切换动画::fi消失中() const {
	return m实际 > 0;
}
float C切换动画::fg目标() const {
	return m目标;
}
float C切换动画::fg实际() const {
	return m实际;
}
float C切换动画::fg透明度() const {
	return 1 - abs(m实际);
}
void C总切换::f更新(W窗口 &a窗口) {
	m最小目标 = m最大目标 = a窗口.m切换.m目标;
	m最小实际 = m最大实际 = a窗口.m切换.m实际;
	const W窗口 *v父 = a窗口.m父窗口;
	while (v父) {
		const auto &v切换 = v父->m切换;
		m最小目标 = std::min(m最小目标, v切换.m目标);
		m最大目标 = std::max(m最大目标, v切换.m目标);
		m最小实际 = std::min(m最小实际, v切换.m实际);
		m最大实际 = std::max(m最大实际, v切换.m实际);
		v父 = v父->m父窗口;
	}
}
float C总切换::fg目标() const {
	return (m最小目标 + m最大目标) * 0.5f;
}
float C总切换::fg实际() const {
	return (m最小实际 + m最大实际) * 0.5f;
}
float C总切换::fg透明度() const {
	return 1 - std::max(std::abs(m最小实际), std::abs(m最大实际));
}
//==============================================================================
// 参数
//==============================================================================
bool S方向键参数::fi上() const {
	return y > 0;
}
bool S方向键参数::fi下() const {
	return y < 0;
}
bool S方向键参数::fi左() const {
	return x < 0;
}
bool S方向键参数::fi右() const {
	return x > 0;
}
bool S方向键参数::fi上下() const {
	return y != 0;
}
bool S方向键参数::fi左右() const {
	return x != 0;
}
//==============================================================================
// 切换动画计算
//==============================================================================
void C动画计算::f默认() {
	if (mf坐标 == nullptr) {
		mf坐标 = f坐标_从右到左;
	}
	if (mf尺寸 == nullptr) {
		mf尺寸 = f尺寸_无;
	}
}
//坐标
t向量2 C动画计算::f坐标_无(const W窗口 &a窗口) {
	const W窗口 *v窗口 = &a窗口;
	t向量2 v;
	while (v窗口) {
		v += v窗口->m坐标;
		v窗口 = v窗口->m父窗口;
	}
	return v;
}
t向量2 C动画计算::f坐标_从右到左(const W窗口 &a窗口) {
	t向量2 v = f坐标_无(a窗口);
	v.x += a窗口.fg总切换().fg实际() * -60;
	return v;
}
t向量2 C动画计算::f坐标_下拉(const W窗口 &a窗口) {
	t向量2 v = f坐标_无(a窗口);
	v.y += abs(a窗口.fg总切换().fg实际()) * 30;
	return v;
}
t向量2 C动画计算::f坐标_缩放(const W窗口 &a窗口) {
	const float v倍数 = 1 - abs(a窗口.fg总切换().fg实际());
	t向量2 v = a窗口.m坐标 * v倍数;
	v += f坐标_无(*a窗口.m父窗口);
	return v;
}
//范围
t向量2 C动画计算::f尺寸_无(const W窗口 &a窗口) {
	return a窗口.m尺寸;
}
t向量2 C动画计算::f尺寸_缩放(const W窗口 &a窗口) {
	const float v倍数 = 1 - abs(a窗口.fg总切换().fg实际());
	return a窗口.m尺寸 * v倍数;
}
//==============================================================================
// 渐变插值
//==============================================================================
S渐变插值::operator float() const {
	return m值;
}
float S渐变插值::f渐变(bool a) {
	const float v目标 = a ? 1 : 0;
	m值 = 数学::f线性渐变<float>(m值, v目标, c速度 * C用户界面::g这->fg渲染秒());
	return m值;
}
float S渐变插值::f插值(float a小, float a大) const {
	return 数学::f插值<float>(a小, a大, m值);
}
//==============================================================================
// 平移计算
//==============================================================================
C平移计算::C平移计算(W窗口 &a窗口):
	m窗口(&a窗口), m来源(E按键来源::e无), m开始位置(), m当前位置(), m速度() {
}
bool C平移计算::fi来源(E按键来源 a来源) const {
	return m来源 == a来源;
}
void C平移计算::f重置(E按键来源 a来源, const t向量2 &a位置) {
	m来源 = a来源;
	m开始位置 = a位置;
	m当前位置 = a位置;
	m速度 = t向量2::c零;
	m时间点 = E时间点::e开始;
}
void C平移计算::f拖动计算(const t向量2 &a位置) {
	const float v过秒 = m窗口->fg引擎().fg计算秒();
	const t向量2 v速度 = a位置 - m当前位置;
	m平滑速度 = (v速度 + m平滑速度) * 0.5f;
	m速度 = v速度;
	m当前位置 = a位置;
	m时间点 = E时间点::e进行中;
}
void C平移计算::f滚轮计算(const t向量2 &a位置) {
	f拖动计算(a位置);
}
void C平移计算::f停止计算() {
	const float v过秒 = m窗口->fg引擎().fg计算秒();
	const float v减后速度 = m平滑速度.fg大小() + c停止加速度 * v过秒;
	if (v减后速度 < 1) {
		m平滑速度 = t向量2::c零;
	} else {
		m平滑速度.fs大小(v减后速度);
		m当前位置 += m平滑速度 * v过秒;
	}
	m时间点 = E时间点::e结束;
}
void C平移计算::f调用响应() {
	const auto f调用 = [this, &v目标速度 = (m时间点 == E时间点::e结束 ? m平滑速度 : m速度)]
	(void (W窗口::*af平移)(const S平移参数 &), const float(t向量2::*ap方向)) {
		const float v速度 = v目标速度.*ap方向;
		if (v速度 == 0) {
			return;
		}
		const S平移参数 v参数 = {m来源, m时间点, m开始位置.*ap方向, m当前位置.*ap方向, v速度};
		(m窗口->*af平移)(v参数);
	};
	f调用(&W窗口::f响应_水平平移, &t向量2::x);
	f调用(&W窗口::f响应_垂直平移, &t向量2::y);
}
//==============================================================================
// 窗口
//==============================================================================
W窗口::W窗口() {
	f标志_s默认();
	f标志_s继承显示();
}
W窗口::W窗口(int a标识, int a值) : m标识(a标识), m值(a值) {
	f标志_s默认();
	f标志_s继承显示();
}
W窗口::~W窗口() {
	if (m按键切换) {
		delete m按键切换;
	}
	if (m平移计算) {
		delete m平移计算;
	}
}
void W窗口::f对象_使用() {
	m标志[e使用] = true;
	m标志[e销毁] = false;
}
void W窗口::f对象_销毁() {
	m标志[e使用] = false;
	m标志[e销毁] = true;
}
bool W窗口::f对象_i使用() const {
	return m标志[e使用] && !m标志[e销毁];
}
//事件
void W窗口::f事件_按键(W窗口&, const S按键参数 &) {
}
void W窗口::f事件_鼠标移上(W窗口&) {
}
void W窗口::f事件_窗口值变化(W窗口&, const int &, int &) {
}
void W窗口::f事件_窗口移动(W窗口&, const t向量2 &) {
}
void W窗口::f事件_焦点变化(W窗口 &a窗口) {
	if (a窗口.f状态_i焦点()) {
		m焦点窗口 = &a窗口;
	} else {
		m焦点窗口 = nullptr;
	}
}
//响应
void W窗口::f响应_初始化() {
}
void W窗口::f响应_销毁() {
}
void W窗口::f响应_计算() {
}
void W窗口::f响应_更新() {
	m焦点渐变.f渐变(f状态_i焦点());
}
void W窗口::f响应_显示(const S显示参数 &a) const {
	if constexpr (c调试) {	//如果调试模式显示圆形,检查焦点是否正确,且重写显示
		const t颜色 v颜色 = a.m主题.fg颜色(1, 1, m焦点渐变.f插值(0, 1));
		a.m画界面.f绘制圆形(fg动画矩形(), v颜色);
	}
}
void W窗口::f响应_按键(const S按键参数 &a参数) {
	if (m父窗口) {
		m父窗口->f事件_按键(*this, a参数);
	}
}
bool W窗口::f响应_i范围内(const t向量2 &a) {
	return (m尺寸.x / 2 >= abs(a.x)) && (m尺寸.y / 2 >= abs(a.y));
}
void W窗口::f响应_鼠标按下(const S按键参数 &) {
}
void W窗口::f响应_鼠标松开(const S按键参数 &) {
}
void W窗口::f响应_字符(const std::vector<wchar_t> &) {
}
void W窗口::f响应_方向键(const S方向键参数 &a方向键) {
	if (m按键切换) {
		f按键切换计算(a方向键);
	}
	if (m父窗口) {
		m父窗口->f响应_方向键(a方向键);
	}
}
void W窗口::f响应_焦点变化() {
	if (m父窗口) {
		m父窗口->f事件_焦点变化(*this);
	}
}
void W窗口::f响应_水平平移(const S平移参数 &) {
}
void W窗口::f响应_垂直平移(const S平移参数 &) {
}
void W窗口::f计算_切换() {
	const float v计算秒 = fg引擎().fg计算秒();
	m切换.f计算(!m标志[e使用] || m标志[e消失], v计算秒);
}
void W窗口::f计算_显示() {
	if (m标志[e消失] && m切换.fg实际() >= 1) {
		m标志[e显示] = false;
	}
}
void W窗口::f计算_平移() {
	if (m平移计算) {
		if (!f状态_i平移焦点()) {
			m平移计算->f停止计算();
		}
		m平移计算->f调用响应();
	}
}
void W窗口::f更新_切换() {
	m总切换.f更新(*this);
}
//动作
void W窗口::f动作_添加窗口(W窗口 &a窗口) {
	C用户界面 *v用户界面 = C用户界面::g这;
	v用户界面->f新建窗口(*this, a窗口);
	m标志[e容器] = true;
}
void W窗口::f动作_关闭() {
	C用户界面 *v用户界面 = C用户界面::g这;
	f动作_隐藏();
	if (f状态_i活动窗口()) {
		v用户界面->f清除活动窗口();
	}
	v用户界面->f遍历子窗口(this, [&](W窗口 &a窗口) {
		a窗口.f动作_关闭();
	});
	m标志[e使用] = false;
}
void W窗口::f动作_启用(bool a启用) {
	m标志[e禁用] = !a启用;
}
void W窗口::f动作_禁用(bool a禁用) {
	m标志[e禁用] = a禁用;
}
void W窗口::f动作_显示(float a延时) {
	if (m标志[e显示] == false || m标志[e消失]) {
		m标志[e显示] = true;
		m标志[e消失] = false;
		m切换.f重置(a延时);
	}
}
void W窗口::f动作_隐藏(bool a消失) {
	if (!m标志[e使用]) {	//未使用时直接不显示
		m标志[e显示] = false;
	} else if (a消失) {
		m标志[e消失] = true;
	} else {
		m标志[e消失] = true;
		m标志[e显示] = false;
	}
}
void W窗口::f动作_获得焦点() {
	C用户界面 &v用户界面 = fg引擎();
	v用户界面.f设置焦点窗口(*this);
}
void W窗口::f动作_获得弱焦点() {
	fg引擎().f设置弱按键焦点窗口(*this);
}
//方法
C用户界面 &W窗口::fg引擎() {
	return *C用户界面::g这;
}
void W窗口::f属性_s布局(const t向量2 &a坐标, const t向量2 &a尺寸) {
	assert(a尺寸.x >= 0 && a尺寸.y >= 0);
	m坐标 = a坐标;
	m尺寸 = a尺寸;
}
void W窗口::f属性_s布局(const S布局参数 &a) {
	this->f属性_s布局(a.m坐标, a.m尺寸);
}
void W窗口::f属性_s布局(float a左, float a上, float a右, float a下) {
	f属性_s布局(t向量2::fc矩形中心(a左, a上, a右, a下), t向量2::fc矩形尺寸(a左, a上, a右, a下));
}
t向量2 W窗口::f属性_g坐标() const {
	return C动画计算::f坐标_无(*this);
}
t向量2 W窗口::fg动画坐标(const t向量2 &a坐标偏移) const {
	return m动画.mf坐标(*this) + a坐标偏移;
}
t向量2 W窗口::fg动画尺寸(const t向量2 &a尺寸偏移) const {
	return m动画.mf尺寸(*this) + a尺寸偏移;
}
t矩形 W窗口::fg动画矩形(const t向量2 &a坐标偏移, const t向量2 &a尺寸偏移) const {
	return t矩形::fc坐标尺寸(fg动画坐标(a坐标偏移), fg动画尺寸(a尺寸偏移));
}
const C总切换 &W窗口::fg总切换() const {
	return m总切换;
}
C平移计算 &W窗口::fg平移计算() {
	if (m平移计算 == nullptr) {
		m平移计算 = new C平移计算(*this);
	}
	return *m平移计算;
}
void W窗口::f按键切换计算(const S方向键参数 &a方向键) {
	auto f切换 = [&](W窗口 * (I按键切换:: * af切换)(bool), bool (S方向键参数:: * af方向)() const, bool (S方向键参数:: * af单向)() const)->bool {
		if ((a方向键.*af方向)()) {
			const bool v前进 = (a方向键.*af单向)();
			if (W窗口 * v窗口 = (m按键切换->*af切换)(v前进)) {
				fg引擎().f设置按键焦点窗口(*v窗口);
				return true;
			}
		}
		return false;
	};
	if (f切换(&I按键切换::f上下切换, &S方向键参数::fi上下, &S方向键参数::fi下) ||
		f切换(&I按键切换::f左右切换, &S方向键参数::fi左右, &S方向键参数::fi右)) {
		return;
	}
}
void W窗口::fs按键切换(E按键切换 a) {
	if (m按键切换) {
		delete m按键切换;
	}
	switch (a) {
	case E按键切换::e序号:
		m按键切换 = new C按键切换_序号(fg引擎(), *this);
		break;
	case E按键切换::e坐标:
	default:
		m按键切换 = new C按键切换_坐标(fg引擎(), *this);
		break;
	}
}
//t颜色 C窗口::fg主题颜色(float p插值, float p亮度, float p透明度) {
//	return S主题::c白.fg颜色(p插值, p亮度, p透明度);
//}
bool W窗口::f状态_i焦点() const {
	return m标志[e焦点];
}
bool W窗口::f状态_i弱焦点() const {
	return this == fg引擎().m按键焦点;
}
bool W窗口::f状态_i活动() const {
	C用户界面 &v用户界面 = fg引擎();
	const W窗口 *const v活动窗口 = v用户界面.m活动窗口;
	const W窗口 *v窗口 = this;
	while (v窗口) {
		if (v活动窗口 == v窗口) {
			return true;
		}
		v窗口 = v窗口->m父窗口;
	}
	return false;
}
bool W窗口::f状态_i活动窗口() const {
	C用户界面 &v用户界面 = fg引擎();
	return v用户界面.m活动窗口 == this;
}
bool W窗口::f状态_i按下() const {
	return (m标志[e鼠标按下] && m标志[e鼠标范围]) || m标志[e按键按下];
}
bool W窗口::f标志_i启用() const {
	return !m标志[e禁用];
}
bool W窗口::f标志_i可获得按键焦点() const {
	return f对象_i使用() && f标志_i启用() && m标志[W窗口::e可获得按键焦点];
}
bool W窗口::f状态_i平移焦点() const {
	C用户界面 &v用户界面 = fg引擎();
	return v用户界面.m平移焦点 == this;
}
std::vector<W窗口*> W窗口::fg子窗口() {
	return ma子窗口;
}
void W窗口::f标志_s默认() {
	m标志[e禁用] = true;
	//m标志[e显示] = true;
	m标志[e显示背景] = true;
	m标志[e显示边框] = true;
	m标志[e可获得鼠标焦点] = true;
	m标志[e可获得按键焦点] = true;
}
void W窗口::f标志_s继承显示() {
	m继承标志[e显示] = true;
	m继承标志[e显示背景] = true;
	m继承标志[e显示边框] = true;
}
bool W窗口::f标志_g继承(size_t a) const {
	if (m继承标志[a] && m父窗口) {
		return m父窗口->f标志_g继承(a);
	} else {
		return m标志[a];
	}
}
bool W窗口::f标志_g继承_否优先(size_t a) const {
	if (m标志[a] == false) {
		return false;
	}
	if (m继承标志[a] && m父窗口) {
		return m父窗口->f标志_g继承_否优先(a);
	} else {
		return m标志[a];
	}
}
bool W窗口::f标志_i显示边框() const {
	return f标志_g继承_否优先(e显示边框);
}
bool W窗口::f标志_i显示背景() const {
	return f标志_g继承_否优先(e显示背景);
}
bool W窗口::f标志_i显示() const {
	return f标志_g继承_否优先(e显示);
}
bool W窗口::f标志_i可获得平移焦点() const {
	return m标志[W窗口::e可获得平移焦点];
}
void W窗口::f标志_s平移(bool a) {
	m标志[W窗口::e可获得平移焦点] = a;
}
bool W窗口::f标志_i纯鼠标() const {
	return m标志[W窗口::e可获得鼠标焦点] && !m标志[W窗口::e可获得按键焦点];
}
void W窗口::f标志_s纯鼠标() {
	m标志[W窗口::e可获得鼠标焦点] = true;
	m标志[W窗口::e可获得按键焦点] = false;
}
}	//namespace 用户界面
//==============================================================================
namespace std {
size_t hash<用户界面::S文本格式>::operator()(const 用户界面::S文本格式 &a) const {
	const size_t h1 = std::hash<float>()(a.m字号);
	const size_t h2 = std::hash<int>()(a.m水平对齐);
	return h1 ^ (h2 << 1);
}

}	//namespace std