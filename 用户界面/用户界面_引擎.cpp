#include <optional>
#include "用户界面_引擎.h"
#include "用户界面_基础.h"
#include "用户界面_按键切换.h"
namespace 用户界面 {
E按键 f刚按下按键(const I输入设备 &a按键) {
	for (输入::t索引 i = 0; i != (输入::t索引)E按键::e无; ++i) {
		const auto &v按键 = a按键.f按键((E按键)i);
		if (v按键.f刚按下()) {
			return (E按键)i;
		}
	}
	return E按键::e无;
}
//=============================================================================
// 用户界面
//=============================================================================
C用户界面 *C用户界面::g这 = nullptr;
C用户界面::C用户界面() {
	if (g这 != nullptr) {
		throw;
	}
	g这 = this;
}
C用户界面::~C用户界面() {
}
void C用户界面::f初始化() {
	ma窗口表.clear();
	m处理窗口 = nullptr;
	m按键焦点 = nullptr;
	m鼠标焦点 = nullptr;
}
void C用户界面::fs画界面(I画界面 &a) {
	m画界面 = &a;
}
void C用户界面::fs时钟频率(float a计算, float a渲染) {
	m计算秒 = 1 / a计算;
	m渲染秒 = 1 / a渲染;
}
void C用户界面::fs主题(const S主题 &a) {
	m主题 = a;
}
void C用户界面::f输入_s键盘接口(I输入设备 &a键盘) {
	m键盘 = &a键盘;
}
void C用户界面::f输入_s鼠标接口(I输入设备 &a鼠标) {
	m鼠标 = &a鼠标;
}
void C用户界面::f输入_s手柄接口(I输入设备 &a手柄) {
	m手柄 = &a手柄;
}
void C用户界面::f输入_s触摸接口(I输入设备 &a触摸) {
	m触摸 = &a触摸;
}
void C用户界面::f输入_接收字符(wchar_t a字符) {
	ma字符.push_back(a字符);
}
void C用户界面::f计算() {
	f窗口表排序();
	if (ma窗口表.empty()) {
		return;	//没窗口,不计算
	}
	const float v计算秒 = fg计算秒();
	//计算切换
	for (auto &vp窗口 : ma窗口表) {
		if (vp窗口->m标志[W窗口::e销毁]) {
			continue;
		}
		auto v使用标志 = vp窗口->m标志[W窗口::e使用];
		auto v显示标志 = vp窗口->m标志[W窗口::e显示];
		const bool v不使用 = !v使用标志;
		const bool v不显示 = !v显示标志;
		vp窗口->m切换.f计算(v不使用 || v不显示, v计算秒);
		if (vp窗口->m切换.fi已消失() && v不使用) {
			f删除窗口(*vp窗口);
		}
	}
	//准备键盘/手柄输入
	const auto f计算方向键 = [this](I输入设备 &a设备, S方向键变量 &a方向键变量) {
		const auto f计算单向 = [&](输入::C互斥键 &a互斥, E按键 a正, E按键 a反) {
			const auto &v正向键 = a设备.f按键(a正);
			const auto &v反向键 = a设备.f按键(a反);
			return a互斥.f计算(v正向键, v反向键);
		};
		const auto &[vi上, v上下键] = f计算单向(a方向键变量.m上下, E按键::e上, E按键::e下);
		const auto &[vi右, v左右键] = f计算单向(a方向键变量.m左右, E按键::e右, E按键::e左);
		const auto &[vi上下, v方向键] = a方向键变量.m四向.f计算(v上下键, v左右键);
		if (a方向键变量.m重复.f滴答(v方向键, m计算秒)) {
			S方向键参数 v参数;
			if (vi上下) {
				v参数.y = 数学::f取符号<bool>(vi上);
			} else {
				v参数.x = 数学::f取符号<bool>(vi右);
			}
			m按键焦点->f响应_方向键(v参数);
		}
	};
	const auto f计算功能键 = [this](I输入设备 &a设备, E按键来源 a来源) {
		const E按键 v按键 = f刚按下按键(a设备);
		if (v按键 != E按键::e无) {
			m按键焦点->f响应_按键({a来源, v按键});
		}
	};
	//处理手柄输入
	if (m手柄) {
		f计算方向键(*m手柄, m手柄方向键变量);
		f计算功能键(*m手柄, E按键来源::e手柄);
	}
	//处理键盘输入
	if (m键盘) {
		f计算方向键(*m键盘, m键盘方向键变量);
		f计算功能键(*m键盘, E按键来源::e键盘);
	}
	//准备鼠标/触摸输入
	auto f更新鼠标焦点 = [this](const t向量2 &a坐标) {
		for (auto &vp窗口 : ma窗口表) {
			if (!vp窗口->f对象_i使用()) {
				continue;
			}
			if (vp窗口->m标志[W窗口::e禁用]) {
				continue;
			}
			if (!vp窗口->fi活动()) {
				continue;
			}
			f跟踪处理(*vp窗口);
			const t向量2 v相对坐标 = a坐标 - vp窗口->f属性_g坐标();
			auto v按下标志 = vp窗口->m标志[W窗口::e鼠标按下];
			auto v鼠标范围标志 = vp窗口->m标志[W窗口::e鼠标范围];
			v鼠标范围标志 = vp窗口->f响应_i范围内(v相对坐标);
			if (v鼠标范围标志) {
				f设置鼠标焦点窗口(*vp窗口);
				return;
			} else {
				if (vp窗口 == m鼠标焦点 && vp窗口 != m按键焦点) {
					f设置鼠标焦点窗口(*m按键焦点);
					return;
				}
			}
		}
	};
	//处理触摸输入
	if (m触摸) {
		const auto &v触摸坐标0 = m触摸->f坐标();
		const t向量2 v触摸坐标 = {v触摸坐标0.x, v触摸坐标0.y};
		const auto &v按键 = m触摸->f按键(E按键::e确定);
		auto fc按键参数 = [&]()->S按键参数 {
			return {E按键来源::e触摸, E按键::e确定, v触摸坐标 - m鼠标焦点->f属性_g坐标()};
		};
		m触摸按下 = v按键.f按下();
		//按键松开
		if (fi鼠标焦点按下()) {
			if (v按键.f刚松开()) {
				m鼠标焦点->f响应_鼠标松开(fc按键参数());
			}
		}
		//移动处理
		if (m触摸坐标 != v触摸坐标) {
			m触摸坐标 = v触摸坐标;
			f更新鼠标焦点(v触摸坐标);
		}
		//按键按下
		if (v按键.f刚按下()) {
			m鼠标焦点->f响应_鼠标按下(fc按键参数());
		}
	}
	//处理鼠标输入
	if (m鼠标) {
		const auto &v鼠标坐标0 = m鼠标->f坐标();
		const t向量2 v鼠标坐标 = {v鼠标坐标0.x, v鼠标坐标0.y};
		//按键松开
		if (fi鼠标焦点按下()) {
			const auto &v按键 = m鼠标->f按键(m鼠标按键);
			if (v按键.f刚松开()) {
				m鼠标焦点->f响应_鼠标松开({E按键来源::e鼠标, m鼠标按键, v鼠标坐标 - m鼠标焦点->f属性_g坐标()});
				m鼠标按键 = E按键::e无;
			}
		}
		//移动处理
		const E按键 v鼠标按键 = f刚按下按键(*m鼠标);
		const bool vi鼠标按键 = v鼠标按键 != E按键::e无;
		const bool vi更新鼠标坐标 = (m鼠标坐标 != v鼠标坐标) || vi鼠标按键;
		if (vi更新鼠标坐标) {
			m鼠标坐标 = v鼠标坐标;
			f更新鼠标焦点(v鼠标坐标);
		}
		//按键按下
		if (vi鼠标按键) {
			const S按键参数 v按键参数 = {E按键来源::e鼠标, v鼠标按键, v鼠标坐标 - m鼠标焦点->f属性_g坐标()};
			m鼠标焦点->f响应_鼠标按下(v按键参数);
			if (m鼠标焦点->m标志[W窗口::e鼠标按下]) {
				m鼠标按键 = v鼠标按键;
			}
		}
	}
	//处理字符
	if (!ma字符.empty()) {
		m按键焦点->f响应_字符(ma字符);
		ma字符.clear();
	}
	//计算
	for (auto &vp窗口 : ma窗口表) {
		if (!vp窗口->f对象_i使用()) {
			continue;
		}
		vp窗口->f响应_计算();
	}
}
void C用户界面::f更新() {
	for (auto &vp窗口 : ma窗口表) {
		if (vp窗口->f标志_i显示()) {
			f跟踪处理(*vp窗口);
			vp窗口->f响应_更新();
		}
	}
}
void C用户界面::f显示() {
	S显示参数 v参数 = {*m画界面, m主题};
	for (auto &v窗口 : ma窗口表) {
		if (v窗口->f标志_i显示()) {
			f跟踪处理(*v窗口);
			v窗口->f响应_显示(v参数);
		}
	}
}
void C用户界面::f跟踪处理(W窗口 &a) {
	m处理窗口 = &a;
}
void C用户界面::f新建窗口_(W窗口 &a窗口) {
	f跟踪处理(a窗口);
	ma新建窗口.push_back(&a窗口);
	a窗口.m序号 = -1;
	a窗口.f对象_使用();
	a窗口.f响应_初始化();
	a窗口.m动画.f默认();
}
void C用户界面::f新建窗口(W窗口 &a窗口) {
	a窗口.m标识 = m总编号;
	f新建窗口_(a窗口);
	++m总编号;
	m窗口表变化 = true;
	if (m活动窗口 == nullptr) {	//没有活动窗口则自动把新建的窗口设为活动窗口
		f设置活动窗口(a窗口);
		//f设置焦点窗口(m窗口表[m活动窗口->m序号 + 1]);	//忘了为什么这么写
		f设置焦点窗口(a窗口);
	}
}
void C用户界面::f新建窗口(W窗口 &a父窗口, W窗口 &a子窗口) {
	a子窗口.m父窗口 = &a父窗口;
	a子窗口.f动作_显示();
	a子窗口.m窗口层 = a父窗口.m窗口层 + 1;
	f新建窗口_(a子窗口);
	a父窗口.ma子窗口.push_back(&a子窗口);
	m窗口表变化 = true;
}
void C用户界面::f删除窗口(W窗口 &a) {
	f删除所有子窗口(a);
	if (a.m父窗口) {
		auto &va子窗口 = a.m父窗口->ma子窗口;
		const auto v开始 = va子窗口.begin();
		const auto v结束 = va子窗口.end();
		const auto v新结束 = std::remove(v开始, v结束, &a);
		va子窗口.erase(v新结束, v结束);
	}
	a.f对象_销毁();
	m窗口表变化 = true;
}
void C用户界面::f删除所有子窗口(W窗口 &a父窗口) {
	for (auto &vp子窗口 : a父窗口.ma子窗口) {
		f删除所有子窗口(*vp子窗口);
		vp子窗口->f对象_销毁();
	}
	a父窗口.ma子窗口.clear();
}
void C用户界面::f切换窗口(W窗口 &a窗口) {
	if (m活动窗口) {
		m活动窗口->f动作_关闭();
	}
	f新建窗口(a窗口);
}
void C用户界面::f遍历所有窗口(const std::function<void(W窗口&)> &af) {
	auto v复制窗口表 = ma窗口表;
	for (auto &vp窗口 : v复制窗口表) {
		if (!vp窗口->f对象_i使用()) {
			continue;
		} else {
			af(*vp窗口);
		}
	}
}
void C用户界面::f遍历子窗口(W窗口 *a窗口, const std::function<void(W窗口&)> &af) {
	if (a窗口 != nullptr && a窗口->ma子窗口.size() == 0) {
		return;
	}
	auto v复制窗口表 = ma窗口表;
	for (auto &vp窗口 : v复制窗口表) {
		if (vp窗口->m标志[W窗口::e销毁]) {
			continue;
		} else if (vp窗口->m父窗口 == a窗口) {
			af(*vp窗口);
		}
	}
}
void C用户界面::f设置焦点窗口(W窗口 &a窗口) {
	if (!a窗口.m标志[W窗口::e鼠标] && m按键焦点 != &a窗口) {	//按键
		if (m按键焦点 != nullptr) {
			m按键焦点->m标志[W窗口::e焦点] = false;
			m按键焦点->m标志[W窗口::e按键按下] = false;
		}
		m按键焦点 = &a窗口;
	}
	if (m鼠标焦点 != &a窗口) {
		if (m鼠标焦点 != nullptr) {
			m鼠标焦点->m标志[W窗口::e焦点] = false;
		}
		m鼠标焦点 = &a窗口;
	}
	m按键焦点->m标志[W窗口::e焦点] = true;
	m鼠标焦点->m标志[W窗口::e焦点] = true;
}
void C用户界面::f设置按键焦点窗口(W窗口 &a窗口) {
	if (fi鼠标焦点按下()) {
		m鼠标焦点->f响应_鼠标松开({E按键来源::e无, m鼠标按键, m鼠标坐标});
	}
	f设置焦点窗口(a窗口);
}
void C用户界面::f设置鼠标焦点窗口(W窗口 &a窗口) {
	if (fi鼠标焦点按下()) {
		return;	//鼠标按下时不切换窗口
	}
	f设置焦点窗口(a窗口);
}
void C用户界面::f设置活动窗口(W窗口 &a窗口) {
	//不能在关闭活动窗口同时调用这个函数
	S调用信息 v信息;
	v信息.m焦点 = m按键焦点;
	v信息.m活动 = m活动窗口;
	m调用栈.push(v信息);
	if (a窗口.m按键切换 == nullptr) {	//如果没设置切换方式,自动设一个
		a窗口.fs按键切换(E按键切换::e序号);
	}
	m活动窗口 = &a窗口;
}
void C用户界面::f清除活动窗口() {
	S调用信息 v信息 = m调用栈.top();
	m活动窗口 = v信息.m活动;
	if (v信息.m焦点) {
		f设置焦点窗口(*v信息.m焦点);
	}
	m调用栈.pop();
}
void C用户界面::f窗口表排序() {
	//按树的顺序排
	if (m窗口表变化 == false) {
		return;
	}
	//新建的窗口
	if (!ma新建窗口.empty()) {
		for (auto &v窗口 : ma新建窗口) {
			ma窗口表.push_back(v窗口);
		}
		ma新建窗口.clear();
	}
	//更新按键切换
	if (m活动窗口) {
		m活动窗口->m按键切换->f更新();
	}
	//结束
	m窗口表变化 = false;
}
float C用户界面::fg计算秒() const {
	return m计算秒;
}
float C用户界面::fg渲染秒() const {
	return m渲染秒;
}
t向量2 C用户界面::fg指针相对坐标(const W窗口 &a窗口) const {
	return m鼠标坐标 - a窗口.f属性_g坐标();
}
bool C用户界面::fi鼠标焦点按下() const {
	return m鼠标焦点 && m鼠标焦点->m标志[W窗口::e鼠标按下];
}
}