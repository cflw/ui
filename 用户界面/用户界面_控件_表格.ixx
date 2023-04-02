module;
#include "用户界面_控件.h"
#include "用户界面_布局.h"
#include "用户界面_引擎.h"
export module 用户界面.控件.表格;
export import 用户界面.控件.垂直滚动条;
export namespace 用户界面 {
//==============================================================================
// 声明
//==============================================================================
class W表格 : public W窗口 {
public:
	static constexpr float c字号 = 16;
	static constexpr E对齐 c对齐 = e居中;
	static constexpr float c行高 = 20;
	static constexpr float c列宽 = 30;
	static constexpr int c无限行 = 0;
	enum E标志 {
		e标题行 = W窗口::e自定义,
		e滚动条,
	};
	struct S列属性 {
		float m列宽 = c列宽;	//在表格中的宽度占比！
		float m字号 = c字号;
		E对齐 m对齐 = c对齐;
		float m计算列宽 = -1;	//按比例计算得到的实际宽度
	};
	struct S行属性 {
		float m行高 = c行高;
		bool m标题行加粗 = true;	//未实现
		bool m偶数行高亮 = false;	//未实现
	};
	class C行流;
	class W行 : public W空白按钮 {
	public:
		W行(W表格 &, int = -1, int = 0);	//标识等于表格标识,值随意
		void f响应_初始化() override;
		void f响应_计算() override;
		void f响应_显示(const S显示参数 &) const override;
		void f响应_方向键(const S方向键参数 &) override;
		void f属性_s布局();	//根据表格自动计算布局
		bool f状态_i标题行() const;	//当前行是否标题行
		std::wstring &fg列(int);
		int fg行号() const;
		int fg列数() const;
		C行流 f流();
		bool f焦点转移(bool 前进, bool 强切换);	//当该行是焦点时把焦点转移到其它行
		std::unique_ptr<W标签[]> ma标签;
		W表格 *mp表格 = nullptr;
		int m行号 = 0;	//从0开始
	};
	class C行流 {
	public:
		C行流(W行 &);
		template<typename t> C行流 &operator <<(const t &a) {
			std::wostringstream s;
			s << a;
			f输出(s.view());
			return *this;
		}
		template<typename t> C行流 &operator >>(t &a) {
			std::wistringstream s{f输入()};
			s >> a;
			return *this;
		}
		void f输出(const std::wstring_view &);	//<<
		std::wstring_view f输入(); //>>
		W行 *mp行 = nullptr;
		int i = 0;
	};
	W表格(int = -1, int = 0);
	void f初始化_列(const S列属性 *, size_t 列数);
	void f初始化_行(const S行属性 &, size_t 最大行数);
	void f初始化_列数(int);	//必需
	void f初始化_行数(int);	//可选
	void f事件_按键(W窗口 &, const S按键参数 &) override;
	void f事件_窗口值变化(W窗口 &, const int &, int &) override;
	void f事件_焦点变化(W窗口 &) override;
	void f响应_初始化() override;
	void f响应_计算() override;
	void f响应_更新() override;
	void f响应_显示(const S显示参数 &) const override;
	void f响应_垂直平移(const S平移参数 &) override;
	S列属性 &f属性_g列属性(int 索引);
	S行属性 &f属性_g行属性();
	int f属性_g列数() const;	//列数
	int f属性_g行上限() const;	//行上限
	int f属性_g行数() const;	//当前行数
	void f属性_s标题行(bool);	//把首行当做标题行,需要手动创建首行
	bool f属性_i标题行() const;	//表格是否设置了标题标志
	bool f属性_i滚动条() const;	//当行数大于表格高度会显示滚动条
	W行 &f新行();
	W行 &f新行(int 标识, int 值);
	W行 &fg标题行();	//总是返回首行,没有则自动创建
	void f删除行(int = -1);
	void f删除行(W行 &);
	void f清空行();	//清空除标题行以外的所有行
	W行 &fg行(int 索引);	//如果设置了标题行,0行就是标题行
	void f重置滚动条布局();
	void f重置滚动条值();
	void f计算滚动();
	int m列数 = 0;
	int m行上限 = c无限行;
	std::vector<std::unique_ptr<W行>> ma行, ma删除行;
	std::vector<S列属性> ma列属性;
	S行属性 m行属性;
	W垂直滚动条 w垂直滚动条;
	W行 *m焦点行 = nullptr;
	t矩形 m焦点动画矩形;
	int m焦点行号 = -1;
	int m行值 = 0;	//自动给 W行::m值 赋值,自动递增
	bool m重置行号 = true;
};
}	//namespace 用户界面
module : private;
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
		f动作_添加窗口(v标签, true);
	}
	if (std::abs(m坐标.y) >= mp表格->m尺寸.y / 2) {
		f动作_隐藏();
	}
}
void W表格::W行::f响应_计算() {
	//在表格中计算
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
bool W表格::W行::f状态_i标题行() const {
	return mp表格->m标志[e标题行] && m行号 == 0;
}
std::wstring &W表格::W行::fg列(int a列) {
	return ma标签[a列].m文本;
}
int W表格::W行::fg行号() const {
	return m行号;
}
int W表格::W行::fg列数() const {
	return mp表格->m列数;
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
	void (W窗口:: *const vf获得焦点)() = a强切换 ? &W窗口::f动作_获得焦点 : &W窗口::f动作_获得弱焦点;
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
	mp行(&a行) {
}
void W表格::C行流::f输出(const std::wstring_view &a) {
	assert(i < mp行->fg列数());
	mp行->fg列(i++) = a;
}
std::wstring_view W表格::C行流::f输入() {
	assert(i < mp行->fg列数());
	return mp行->fg列(i++);
}
//==============================================================================
// 表格
//==============================================================================
W表格::W表格(int a标识, int a值):
	W窗口(a标识, a值),
	w垂直滚动条(a标识, -1) {
	m标志[e禁用] = true;
}
void W表格::f初始化_列(const S列属性 *p, size_t n) {
	f初始化_列数((int)n);
	std::copy_n(p, n, ma列属性.begin());
}
void W表格::f初始化_行(const S行属性 &p, size_t n) {
	f初始化_行数((int)n);
	m行属性 = p;
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
	if (W行 *vp行 = dynamic_cast<W行 *>(&a窗口)) {
		if (a窗口.f状态_i焦点()) {
			int v新值 = a窗口.m值;
			m父窗口->f事件_窗口值变化(*this, m焦点行号, v新值);
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
		f动作_添加窗口(*vp行, true);
	}
	if (!ma行.empty()) {	//禁用标题行
		ma行.front()->m标志[e禁用] = m标志[e标题行];
	}
	//滚动条
	f重置滚动条布局();
	f重置滚动条值();
	f动作_添加窗口(w垂直滚动条, true);
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
	//计算行滚动
	f计算滚动();
}
void W表格::f响应_更新() {
	if (m焦点窗口) {
		if (m焦点渐变.m值 == 0) {
			m焦点动画矩形 = m焦点窗口->fg动画矩形();
		} else {
			const t向量2 v坐标 = m焦点窗口->fg动画坐标();
			const float v过秒 = C用户界面::fg实例().fg渲染秒();
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
W表格::S行属性 &W表格::f属性_g行属性() {
	return m行属性;
}
int W表格::f属性_g列数() const {
	return m列数;
}
int W表格::f属性_g行上限() const {
	return m行上限;
}
int W表格::f属性_g行数() const {
	return (int)ma行.size();
}
void W表格::f属性_s标题行(bool a) {
	m标志[e标题行] = a;
	if (!ma行.empty()) {
		ma行.front()->m标志[e禁用] = a;	//首行是禁用的
	}
}
bool W表格::f属性_i标题行() const {
	return m标志[e标题行];
}
bool W表格::f属性_i滚动条() const {
	return m标志[e滚动条];
}
W表格::W行 &W表格::f新行() {
	return f新行(m标识, m行值++);
}
W表格::W行 &W表格::f新行(int a标识, int a值) {
	//if (m行上限 != c无限行 && f属性_g行数() >= m行上限) {
	//	return;
	//}
	auto &vp行 = ma行.emplace_back(std::make_unique<W行>(*this, a标识, a值));
	if (m标志[e使用]) {
		vp行->m行号 = f属性_g行数() - 1;
		vp行->f属性_s布局();
		f动作_添加窗口(*vp行, true);
		if (m标志[e标题行] && vp行->m行号 == 0) {
			vp行->f动作_禁用();	//标题行是禁用的
		}
		f重置滚动条值();
	}
	return *vp行;
}
W表格::W行 &W表格::fg标题行() {
	if (f属性_g行数() > 0) {	//有行,用首行
		return *ma行[0];
	} else {	//没有行,新建行
		return f新行();
	}
}
void W表格::f删除行(int a行号) {
	if (ma行.empty()) {
		return;	//不删除空表格
	}
	if (m标志[e标题行] && a行号 == 0) {
		return;	//不删除标题行
	}
	//确定对象
	const int v行数 = f属性_g行数();
	decltype(ma行)::iterator vp行;
	if (a行号 >= 0) {
		assert(a行号 < v行数);
		vp行 = ma行.begin() + a行号;
	} else {
		assert(-v行数 <= a行号);
		vp行 = ma行.end() + a行号;
	}
	W行 &v行 = **vp行;
	//删除
	v行.f动作_关闭();
	if (v行数 >= 2) {	//有剩余行,转移焦点
		if (auto vp下一行 = vp行 + 1; vp下一行 != ma行.end()) {	//删除行的下一行获得焦点
			W行 &v下一行 = **vp下一行;
			v下一行.f动作_获得焦点();
		} else {	//如果删除了最后一行,则上一行获得焦点
			W行 &v上一行 = **(vp行 - 1);
			if (!v上一行.f状态_i标题行()) {	//非标题行不能获得焦点
				v上一行.f动作_获得焦点();
			} else {
				v行.f动作_释放焦点();
			}
		}
	}
	ma删除行.push_back(std::move(*vp行));
	ma行.erase(vp行);
	//重新计算状态
	m重置行号 = true;
	if (m标志[e使用]) {
		f重置滚动条值();
	}
}
void W表格::f删除行(W行 &a行) {
	f删除行(a行.fg行号());
}
void W表格::f清空行() {
	const int v行数 = f属性_g行数();
	const int v开始行 = f属性_i标题行() ? 1 : 0;
	for (int i = v开始行; i < v行数; ++i) {
		auto vp行 = ma行.begin() + i;
		W行 &v行 = **vp行;
		v行.f动作_关闭();
		ma删除行.push_back(std::move(*vp行));
	}
	if (v行数 < v开始行) {	//发生删除,重新计算状态
		ma行.resize(v开始行);
		m重置行号 = true;
		if (m标志[e使用]) {
			f重置滚动条值();
		}
	}
}
W表格::W行 &W表格::fg行(int a索引) {
	return *ma行[a索引];
}
void W表格::f重置滚动条布局() {
	w垂直滚动条.f属性_s布局(*this, m标志[e标题行] ? -m行属性.m行高 : 0, 0);
}
void W表格::f重置滚动条值() {
	const int v减标题行 = m标志[e标题行] ? -1 : 0;
	const int v行数 = (int)ma行.size() + v减标题行;
	const int v显示容量 = (int)(m尺寸.y / m行属性.m行高) + v减标题行;
	w垂直滚动条.f属性_s容纳值(v行数, v显示容量);	//由滚动条计算出是否显示,再确定是否可以平移
	const bool vi垂直平移 = w垂直滚动条.f属性_i使用全部();
	f标志_s平移(vi垂直平移);
}
void W表格::f计算滚动() {
	//if (!w垂直滚动条.f状态_i滚动()) {
	//	return;	//无滚动
	//}
	const float &v行高 = m行属性.m行高;
	const bool vi标题行 = f属性_i标题行();
	const float v半尺寸y = m尺寸.y * 0.5f;
	const int v滚动位置 = w垂直滚动条.f属性_g当前位置();
	const float v过秒 = C用户界面::fg实例().fg计算秒();
	for (auto &vp行 : ma行) {
		const float v上 = v半尺寸y - v行高 * vp行->m行号;	//相对表格位置
		const float v下 = v上 - v行高;
		const float v滚动偏移 = (vi标题行 ? (vp行->m行号 != 0 ? 1 : 0) : 1) * v滚动位置 * v行高;	//标题行固定位置
		const float v目标y = (v上 + v下) * 0.5f + v滚动偏移;
		vp行->m坐标.y = 数学::f倍数渐变<float>(vp行->m坐标.y, v目标y, 10 * v过秒);
		const float v表格范围上 = v半尺寸y - (vi标题行 ? (vp行->m行号 != 0 ? 1 : 0) : 0) * v行高;	//当前行可以出现在表格中的坐标范围
		const float v表格范围下 = -v半尺寸y;
		const bool v上越界 = vp行->m坐标.y > v表格范围上;
		const bool v下越界 = vp行->m坐标.y < v表格范围下;
		const bool v越界 = v上越界 || v下越界;
		auto f赋切换 = [&vp行](float a切换值) {
			vp行->m切换.m目标 = std::max<float>(vp行->m切换.m目标, a切换值);
			vp行->m切换.m实际 = std::max<float>(vp行->m切换.m实际, a切换值);
		};
		if (v越界) {
			vp行->f动作_禁用();
			vp行->f动作_隐藏();
			const float t = ((vp行->m坐标.y >= 0) ? (vp行->m坐标.y - v表格范围上) : (-vp行->m坐标.y + v表格范围下)) / v行高;	//表格边缘0 -> 表格外1+
			const float v切换值 = 数学::f插值<float>(C切换动画::c渐出开始, C切换动画::c渐出结束, t);
			f赋切换(v切换值);
			if (vp行->f状态_i焦点()) {	//被动切换按键焦点
				vp行->f焦点转移(vp行->m坐标.y < v目标y, false);
			}
		} else {
			if (!vp行->f状态_i标题行()) {
				vp行->f动作_启用();
			}
			vp行->f动作_显示();
			const float t = ((vp行->m坐标.y >= 0) ? (-vp行->m坐标.y + v表格范围上) : (vp行->m坐标.y - v表格范围下)) / v行高;	//表格边缘0 -> 表格内1+
			const float v切换值0 = 数学::f插值<float>(C切换动画::c渐入开始, C切换动画::c渐入结束, t);
			const float v切换值 = std::min<float>(v切换值0, C切换动画::c渐入结束);	//渐入有上限
			f赋切换(v切换值);
		}
	}
}
}	//namespace 用户界面