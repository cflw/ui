#include "用户界面_控件.h"
#include "用户界面_布局.h"
#include "用户界面_引擎.h"
namespace 用户界面 {
//==============================================================================
// 行
//==============================================================================
W表格::W行::W行(W表格 &a表格, int a标识, int a值):
	W空白按钮(a标识, a值),
	mp表格(&a表格),
	ma标签(std::make_unique<W标签[]>(a表格.m列数)) {
	m标志[e禁用] = false;
	m动画.mf坐标 = C动画计算::f坐标_无;
}
void W表格::W行::f响应_初始化() {
	C表格排列布局 v布局;
	v布局.f属性_s列布局(t向量2::c零, m尺寸);
	for (int i = 0; i != mp表格->m列数; ++i) {
		W标签 &v标签 = ma标签[i];
		const S列属性 &v列属性 = mp表格->ma列属性[i];
		//属性
		v标签.f属性_s布局(v布局.f移动生成(v列属性.m计算列宽));
		v标签.m动画.mf坐标 = C动画计算::f坐标_无;
		//添加窗口
		f动作_添加窗口(v标签);
	}
	if (std::abs(m坐标.y) >= mp表格->m尺寸.y / 2) {
		f动作_隐藏();
	}
}
void W表格::W行::f响应_计算() {
	//根据行号和滚动条值计算位置
	const float &v行高 = mp表格->m行属性.m行高;
	const float v表格上 = mp表格->m尺寸.y * 0.5f;
	const float v上 = v表格上 - v行高 * m行号;
	const float v下 = v上 - v行高;
	const float v滚动偏移 = (mp表格->m标志[e标题行] && m行号 == 0) ? 0 : mp表格->w垂直滚动条.f属性_g当前位置() * v行高;
	const float v目标y = (v上 + v下) * 0.5f + v滚动偏移;
	const float v过秒 = fg引擎().fg计算秒();
	m坐标.y = 数学::f倍数渐变<float>(m坐标.y, v目标y, 10 * v过秒);
	const bool v越界 = std::abs(m坐标.y) >= v表格上;
	f动作_禁用(v越界);
	if (v越界) {
		f动作_隐藏();
		const float v切换值 = (std::abs(m坐标.y) - v表格上) / v行高;	//在表外是正数
		m切换.m实际 = std::max<float>(m切换.m实际, v切换值);
		if (f状态_i焦点()) {	//被动切换按键焦点
			f焦点转移(m坐标.y < v目标y, false);
		}
	} else {
		f动作_显示();
		const float v切换值 = (v表格上 - v行高 - std::abs(m坐标.y)) / v行高;	//在表内是正数
		m切换.m实际 = std::max<float>(m切换.m实际, std::min<float>(v切换值, 0));
	}
}
void W表格::W行::f响应_显示(const S显示参数 &) const {
	//不显示
}
void W表格::W行::f响应_方向键(const S方向键参数 &a) {
	if (a.fi上下()) {
		if (!f焦点转移(a.fi下(), true)) {
			m父窗口->f响应_方向键(a);
		}
	} else {
		m父窗口->f响应_方向键(a);
	}
}
void W表格::W行::f属性_s布局() {
	const float &v行高 = mp表格->m行属性.m行高;
	const float v上 = mp表格->m尺寸.y * 0.5f - v行高 * m行号;
	const float v下 = v上 - v行高;
	const float v左 = -mp表格->m尺寸.x * 0.5f;
	const float v右 = mp表格->m尺寸.x * 0.5f - W垂直滚动条::c边长;
	W窗口::f属性_s布局(t矩形::fc左上右下(v左, v上, v右, v下));
}
std::wstring &W表格::W行::fg列(int a列) {
	return ma标签[a列].m文本;
}
int W表格::W行::fg行号() const {
	return m行号;
}
W表格::C行流 W表格::W行::f流() {
	return C行流(*this);
}
bool W表格::W行::f焦点转移(bool a前进, bool a强切换) {
	assert(f状态_i焦点());
	const int v前进 = a前进 ? 1 : -1;
	const int v目标行号 = m行号 + v前进;
	if (v目标行号 < 0 || v目标行号 >= mp表格->f属性_g行数()) {
		return false;
	}
	void (W窗口::*const vf获得焦点)() = a强切换 ? &W窗口::f动作_获得焦点 : &W窗口::f动作_获得弱焦点;
	W行 &v目标行 = *mp表格->ma行[v目标行号];
	if (a强切换 && v目标行.m标志[e消失]) {
		mp表格->w垂直滚动条.f动作_百分比滚动(v前进);
	}
	(v目标行.*vf获得焦点)();
	return true;
}
//==============================================================================
// 行流
//==============================================================================
W表格::C行流::C行流(W表格::W行 &a行):
	m行(&a行) {
}
W表格::C行流 &W表格::C行流::operator <<(const std::wstring_view &a) {
	m行->fg列(i++) = a;
	return *this;
}
W表格::C行流 &W表格::C行流::operator >>(std::wstring &a) {
	a = m行->fg列(i++);
	return *this;
}
//==============================================================================
// 表格
//==============================================================================
W表格::W表格(int a标识, int a值):
	W窗口(a标识, a值),
	w垂直滚动条(a标识, -1) {
	m标志[e禁用] = false;
}
void W表格::f初始化_列数(int a列数) {
	m列数 = a列数;
	ma列属性.resize(a列数);
}
void W表格::f初始化_行数(int a行数) {
	m行上限 = a行数;
}
void W表格::f事件_按键(W窗口 &a窗口, const S按键参数 &a参数) {
	if (a窗口.m值 >= 0) {
		m父窗口->f事件_按键(a窗口, a参数);
	}
}
void W表格::f事件_窗口值变化(W窗口 &a窗口, const int &a前, int &a后) {

}
void W表格::f事件_焦点变化(W窗口 &a窗口) {
	if (W行 *vp行 = dynamic_cast<W行*>(&a窗口)) {
		if (a窗口.f状态_i焦点()) {
			m焦点窗口 = &a窗口;
			int v新值 = a窗口.m值;
			m父窗口->f事件_窗口值变化(*this, m焦点行号, v新值);
		} else {
			m焦点窗口 = nullptr;
		}
	}
}
void W表格::f响应_初始化() {
	//计算总列宽
	float v总列宽 = 0;
	for (const S列属性 &v列属性 : ma列属性) {
		v总列宽 += v列属性.m列宽;
	}
	//计算单列宽
	const float v左 = -m尺寸.x * 0.5f;
	const float v右 = m尺寸.x * 0.5f - W垂直滚动条::c边长;
	const float v内容宽 = v右 - v左;
	const float v缩放 = v内容宽 / v总列宽;
	for (S列属性 &v列属性 : ma列属性) {
		v列属性.m计算列宽 = v列属性.m列宽 * v缩放;
	}
	//添加行
	C表格排行布局 v布局;
	v布局.f属性_s行布局(t向量2::fc矩形中心(v左, 0, v右, 0), {v内容宽, m尺寸.y}, c行高);
	for (auto &vp行 : ma行) {
		vp行->W窗口::f属性_s布局(v布局.f移动生成());
		f动作_添加窗口(*vp行);
	}
	if (!ma行.empty()) {	//禁用标题行
		ma行.front()->m标志[e禁用] = m标志[e标题行];
	}
	//滚动条
	f重置滚动条布局();
	f重置滚动条值();
	f动作_添加窗口(w垂直滚动条);
}
void W表格::f响应_计算() {
	//清理行
	if (!ma删除行.empty()) {
		ma删除行.erase(std::remove_if(ma删除行.begin(), ma删除行.end(),
			[](const std::unique_ptr<W行> &ap窗口)->bool {
				return ap窗口->m标志[W窗口::e销毁];
			}), ma删除行.end());
	}
	//重置行号
	if (m重置行号) {
		m重置行号 = false;
		int i = 0;
		for (auto &vp行 : ma行) {
			vp行->m行号 = i++;
		}
	}
}
void W表格::f响应_更新() {
	if (m焦点窗口) {
		if (m焦点渐变.m值 == 0) {
			m焦点动画矩形 = m焦点窗口->fg动画矩形();
		} else {
			const t向量2 v坐标 = m焦点窗口->fg动画坐标();
			const float v过秒 = fg引擎().fg渲染秒();
			m焦点动画矩形.m坐标 = m焦点动画矩形.m坐标.f倍数渐变(v坐标, 20 * v过秒);
		}
	}
	m焦点渐变.f渐变(m焦点窗口);
}
void W表格::f响应_显示(const S显示参数 &a) const {
	const float v切换透明 = m切换.fg透明度();
	const t颜色 v前景色 = a.m主题.fg颜色(1, 1, m焦点渐变.f插值(0, 0.5f) * v切换透明);
	if (f标志_i显示边框()) {
		a.m图形.f绘制矩形(m焦点动画矩形, v前景色);
	}
}
void W表格::f响应_垂直平移(const S平移参数 &a) {
	//控制滚动条滑块位置
	w垂直滚动条.f动作_坐标滚动(-a.m速度);
}
W表格::S列属性 &W表格::f属性_g列属性(int a索引) {
	return ma列属性[a索引];
}
W表格::S行属性 W表格::f属性_g行属性() {
	return m行属性;
}
int W表格::f属性_g列数() const {
	return m列数;
}
int W表格::f属性_g行上限() const {
	return m行上限;
}
int W表格::f属性_g行数() const {
	return ma行.size();
}
void W表格::f属性_s标题行(bool a) {
	m标志[e标题行] = a;
	if (!ma行.empty()) {
		ma行.front()->m标志[e禁用] = a;
	}
}
bool W表格::f属性_i标题行() const {
	return m标志[e标题行];
}
bool W表格::f属性_i滚动条() const {
	return m标志[e滚动条];
}
W表格::W行 &W表格::f新行() {
	//if (m行上限 != c无限行 && f属性_g行数() >= m行上限) {
	//	return;
	//}
	auto &vp行 = ma行.emplace_back(std::make_unique<W行>(*this, m标识, ++m行值));
	if (m标志[e使用]) {
		vp行->m行号 = f属性_g行数() - 1;
		vp行->f属性_s布局();
		f动作_添加窗口(*vp行);
		f重置滚动条值();
	}
	return *vp行;
}
void W表格::f删除行(int a行号) {
	if (ma行.empty()) {
		return;	//不删除空表格
	}
	if (m标志[e标题行] && a行号 == 0) {
		return;	//不删除标题
	}
	const int v行数 = f属性_g行数();
	decltype(ma行)::iterator vp行;
	if (a行号 >= 0) {
		assert(a行号 < v行数);
		vp行 = ma行.begin() + a行号;
	} else {
		assert(-v行数 <= a行号);
		vp行 = ma行.end() + a行号;
	}
	auto &v行 = **vp行;
	v行.f动作_关闭();
	ma删除行.push_back(std::move(*vp行));
	ma行.erase(vp行);
	m重置行号 = true;
	if (m标志[e使用]) {
		f重置滚动条值();
	}
}
void W表格::f删除行(W行 &a行) {
	ma行.erase(ma行.begin() + a行.fg行号());
}
W表格::W行 &W表格::fg行(int a索引) {
	return *ma行[a索引];
}
void W表格::f重置滚动条布局() {
	w垂直滚动条.f属性_s布局(*this, m标志[e标题行] ? -m行属性.m行高 : 0, 0);
}
void W表格::f重置滚动条值() {
	const int v减标题行 = m标志[e标题行] ? -1 : 0;
	const int v行数 = ma行.size() + v减标题行;
	const int v显示容量 = (m尺寸.y / m行属性.m行高) + v减标题行;
	w垂直滚动条.f属性_s容纳值(v行数, v显示容量);	//由滚动条计算出是否显示,再确定是否可以平移
	const bool vi垂直平移 = w垂直滚动条.f属性_i使用全部();
	f标志_s平移(vi垂直平移);
}
}	//namespace 用户界面