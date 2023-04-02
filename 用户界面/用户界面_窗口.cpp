#include "用户界面_窗口.h"
#include "用户界面_引擎.h"
#include "用户界面_按键切换.h"
namespace 用户界面 {
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
void W窗口::f事件_按键(W窗口 &, const S按键参数 &) {
}
void W窗口::f事件_鼠标移上(W窗口 &) {
}
void W窗口::f事件_窗口值变化(W窗口 &, const int &, int &) {
}
void W窗口::f事件_窗口移动(W窗口 &, const t向量2 &) {
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
	if constexpr (c调试) {	//如果调试模式显示出圆形,检查焦点是否正确,然后重写显示
		const t颜色 v颜色 = a.m主题.fg颜色(1, 1, m焦点渐变.f插值(0, 1));
		a.m图形.f绘制圆形(fg动画矩形(), v颜色);
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
		if (f状态_i焦点()) {
			m父窗口->m焦点窗口 = this;
		} else {
			m父窗口->m焦点窗口 = nullptr;
		}
		m父窗口->f事件_焦点变化(*this);
	}
}
void W窗口::f响应_水平平移(const S平移参数 &) {
}
void W窗口::f响应_垂直平移(const S平移参数 &) {
}
void W窗口::f计算_切换() {
	const float v计算秒 = C用户界面::fg实例().fg计算秒();
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
void W窗口::f动作_添加窗口(W窗口 &a窗口, bool a显示) {
	C用户界面 &v用户界面 = C用户界面::fg实例();
	a窗口.m标志[e显示] = a显示;
	v用户界面.f新建窗口(*this, a窗口);
	m标志[e容器] = true;
}
void W窗口::f动作_关闭() {
	C用户界面 &v用户界面 = C用户界面::fg实例();
	f动作_隐藏();
	if (f状态_i活动窗口()) {
		v用户界面.f清除活动窗口();
	}
	v用户界面.f遍历子窗口(this, [](W窗口 &a窗口) {
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
	C用户界面::fg实例().f设置焦点窗口(*this);
}
void W窗口::f动作_获得弱焦点() {
	C用户界面::fg实例().f设置弱按键焦点窗口(*this);
}
void W窗口::f动作_释放焦点() {
	assert(f状态_i焦点());
	W窗口 *vp窗口 = m父窗口;
	while (vp窗口) {
		if (vp窗口->f状态_i可获得按键焦点()) {
			f动作_获得焦点();
			return;
		} else {
			vp窗口 = vp窗口->m父窗口;
		}
	}
	//如果没有合适的窗口可以获得焦点,强行让父窗口获得焦点
	m父窗口->f动作_获得焦点();
}
//方法
void W窗口::f属性_s布局(const S布局参数 &a参数) {
	assert(a参数.m尺寸.x >= 0 && a参数.m尺寸.y >= 0);
	m坐标 = a参数.m坐标;
	m尺寸 = a参数.m尺寸;
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
	auto f切换 = [&](W窗口 *(I按键切换:: *af切换)(bool), bool (S方向键参数:: *af方向)() const, bool (S方向键参数:: *af单向)() const)->bool {
		if ((a方向键.*af方向)()) {
			const bool v前进 = (a方向键.*af单向)();
			if (W窗口 *v窗口 = (m按键切换->*af切换)(v前进)) {
				C用户界面::fg实例().f设置按键焦点窗口(*v窗口);
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
int W窗口::fg组合标识值() const {
	return f组合标识值(m标识, m值);
}
void W窗口::fs按键切换(E按键切换 a) {
	if (m按键切换) {
		delete m按键切换;
	}
	switch (a) {
	case E按键切换::e序号:
		m按键切换 = new C按键切换_序号(C用户界面::fg实例(), *this);
		break;
	case E按键切换::e坐标:
	default:
		m按键切换 = new C按键切换_坐标(C用户界面::fg实例(), *this);
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
	return this == C用户界面::fg实例().m按键焦点;
}
bool W窗口::f状态_i活动() const {
	C用户界面 &v用户界面 = C用户界面::fg实例();
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
	C用户界面 &v用户界面 = C用户界面::fg实例();
	return v用户界面.m活动窗口 == this;
}
bool W窗口::f状态_i按下() const {
	return (m标志[e鼠标按下] && m标志[e鼠标范围]) || m标志[e按键按下];
}
bool W窗口::f标志_i启用() const {
	return !m标志[e禁用];
}
bool W窗口::f状态_i平移焦点() const {
	C用户界面 &v用户界面 = C用户界面::fg实例();
	return v用户界面.m平移焦点 == this;
}
bool W窗口::f状态_i显示完成() const {
	return m总切换.fg透明度() >= 0.9f;
}
bool W窗口::f状态_i可获得按键焦点() const {
	return f对象_i使用() &&
		f标志_i启用() &&
		m标志[W窗口::e可获得按键焦点] &&
		f状态_i活动();
}
bool W窗口::f状态_i可获得鼠标焦点() const {
	return f对象_i使用() &&
		f标志_i启用() &&
		m标志[W窗口::e可获得鼠标焦点] &&
		f状态_i活动() &&
		f状态_i显示完成();
}
bool W窗口::f状态_i可获得平移焦点() const {
	return f对象_i使用() &&
		f标志_i启用() &&
		m标志[W窗口::e可获得平移焦点] &&
		f状态_i活动() &&
		f状态_i显示完成();
}
std::vector<W窗口 *> W窗口::fg子窗口() {
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