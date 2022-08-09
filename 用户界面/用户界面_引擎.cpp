#include "用户界面_引擎.h"
#include "用户界面_基础.h"
#include "用户界面_按键切换.h"
namespace 用户界面 {
E按键 fg刚按下按键(const I输入设备 &a按键) {
	for (输入::t索引 i = 0; i != (输入::t索引)E按键::c数量; ++i) {
		const auto &v按键 = a按键.f按键((E按键)i);
		if (v按键.fi刚按下()) {
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
void C用户界面::fs图形(I图形设备 &a) {
	m图形 = &a;
}
void C用户界面::fs时钟频率(float a计算, float a渲染) {
	m计算秒 = 1 / a计算;
	m渲染秒 = 1 / a渲染;
}
void C用户界面::fs主题(const S主题 &a) {
	m主题 = a;
}
void C用户界面::fs音频(I音频设备 &a) {
	m音频 = &a;
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
	const float v过秒 = fg计算秒();
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
			f播放音效(E声音::e方向键切换按键焦点);
		}
	};
	const auto f计算功能键 = [this](I输入设备 &a设备, E按键来源 a来源) {
		const E按键 v按键 = fg刚按下按键(a设备);
		if (v按键 != E按键::e无) {
			m按键焦点->f响应_按键({a来源, v按键});
		}
		const S按键 v确定键 = a设备.f按键(E按键::e确定);
		if (v确定键.fi刚按下()) {
			m按键焦点->m标志[W窗口::e按键按下] = true;
		} else if (v确定键.fi刚松开()) {
			m按键焦点->m标志[W窗口::e按键按下] = false;
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
	const auto f更新鼠标焦点 = [this](const t向量2 &a坐标) {
		//鼠标按下时，不能更新鼠标焦点
		W窗口 *v目标窗口 = nullptr;
		for (auto &vp窗口 : ma窗口表) {
			if (!vp窗口->f状态_i可获得鼠标焦点()) {
				continue;
			}
			f跟踪处理(*vp窗口);
			const t向量2 v相对坐标 = a坐标 - vp窗口->f属性_g坐标();
			auto v鼠标范围标志 = vp窗口->m标志[W窗口::e鼠标范围];
			v鼠标范围标志 = vp窗口->f响应_i范围内(v相对坐标);
			if (v鼠标范围标志) {
				v目标窗口 = vp窗口;
			} else {	//如果鼠标离开窗口范围,且存在其它按键焦点,则切换到按键焦点
				if (vp窗口 == m鼠标焦点 && vp窗口 != m按键焦点) {
					v目标窗口 = m按键焦点;
				}
			}
		}
		if (v目标窗口) {
			f设置鼠标焦点窗口(*v目标窗口);
		}
	};
	const auto f更新平移焦点 = [this](const t向量2 &a坐标) {
		W窗口 *v目标窗口 = nullptr;
		for (auto &vp窗口 : ma窗口表) {
			if (!vp窗口->f状态_i可获得平移焦点()) {
				continue;
			}
			f跟踪处理(*vp窗口);
			const t向量2 v相对坐标 = a坐标 - vp窗口->f属性_g坐标();
			const bool vi范围 = vp窗口->f响应_i范围内(v相对坐标);
			if (vi范围) {
				v目标窗口 = vp窗口;
			}
		}
		if (v目标窗口) {
			f设置平移焦点窗口(*v目标窗口);
		}
	};
	const auto f平移开始 = [this, f更新平移焦点](E按键来源 a来源, const t向量2 &a坐标) {
		f更新平移焦点(a坐标);
		if (m平移焦点) {
			C平移计算 &v平移计算 = m平移焦点->fg平移计算();
			v平移计算.f重置(a来源, a坐标);
		}
	};
	const auto f平移中 = [this](const t向量2 & a坐标) {
		if (m平移焦点) {
			C平移计算 &v平移计算 = m平移焦点->fg平移计算();
			v平移计算.f拖动计算(a坐标);
		}
	};
	const auto f平移结束 = [this]() {
		f清除平移焦点窗口();
	};
	//处理触摸输入
	if (m触摸) {
		const t向量2 v触摸坐标 = m触摸->f坐标();
		const auto &v按键 = m触摸->f按键(E按键::e确定);
		auto fc按键参数 = [&]()->S按键参数 {
			return {E按键来源::e触摸, E按键::e确定, E时间点::e一次, v触摸坐标 - m鼠标焦点->f属性_g坐标()};
		};
		m触摸按下 = v按键.fi按下();
		//按键松开
		if (fi鼠标焦点按下()) {
			if (v按键.fi刚松开()) {
				m鼠标焦点->f响应_鼠标松开(fc按键参数());
				//平移
				//f平移结束();
			}
		}
		//移动处理
		if (m触摸坐标 != v触摸坐标) {
			m触摸坐标 = v触摸坐标;
			f更新鼠标焦点(v触摸坐标);
		}
		//f平移中(v触摸坐标);
		//按键按下
		if (v按键.fi刚按下()) {
			//计算平移
			//f平移开始(E按键来源::e触摸, v触摸坐标);
			//触摸
			m鼠标焦点->f响应_鼠标按下(fc按键参数());
		}
	}
	//处理鼠标输入
	if (m鼠标) {
		const t向量2 v鼠标坐标 = m鼠标->f坐标();
		const t向量2 v相对坐标 = v鼠标坐标 - m鼠标焦点->f属性_g坐标();
		//按键松开
		if (fi鼠标焦点按下()) {
			const auto &v按键 = m鼠标->f按键(m鼠标按键);
			if (v按键.fi刚松开()) {
				//按键
				m鼠标焦点->f响应_鼠标松开({E按键来源::e鼠标, m鼠标按键, E时间点::e结束, v相对坐标});
				m鼠标按键 = E按键::e无;
				//平移
				f平移结束();
			}
		}
		//移动处理
		const E按键 v鼠标按键 = fg刚按下按键(*m鼠标);
		const bool vi鼠标按键 = v鼠标按键 != E按键::e无;
		const bool vi更新鼠标坐标 = (m鼠标坐标 != v鼠标坐标) || vi鼠标按键;
		if (vi更新鼠标坐标) {
			m鼠标坐标 = v鼠标坐标;
			f更新鼠标焦点(v鼠标坐标);
		}
		f平移中(v鼠标坐标);
		//按键按下
		if (vi鼠标按键) {
			//计算平移
			f平移开始(E按键来源::e鼠标, v鼠标坐标);
			//计算按键
			const S按键参数 v按键参数 = {E按键来源::e鼠标, v鼠标按键, E时间点::e开始, v相对坐标};
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
		if (vp窗口->f对象_i使用()) {
			vp窗口->f响应_计算();
		}
		vp窗口->f计算_切换();
		vp窗口->f计算_显示();
		vp窗口->f计算_平移();
	}
}
void C用户界面::f更新() {
	for (auto &vp窗口 : ma窗口表) {
		if (vp窗口->f标志_i显示()) {
			f跟踪处理(*vp窗口);
			vp窗口->f响应_更新();
			vp窗口->f更新_切换();
		}
	}
}
void C用户界面::f显示() {
	S显示参数 v参数 = {*m图形, m主题};
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
	a窗口.f响应_初始化();
	a窗口.f对象_使用();
	a窗口.m动画.f默认();
}
void C用户界面::f新建窗口(W窗口 &a窗口) {
	f新建窗口_(a窗口);
	m窗口表变化 = true;
	if (m活动窗口 == nullptr) {	//没有活动窗口则自动把新建的窗口设为活动窗口
		f设置活动窗口(a窗口);
	}
	//设置焦点窗口.如果窗口原来当过活动窗口,则使用原来的焦点
	if (auto v找 = ma活动窗口.find(&a窗口); v找 != ma活动窗口.end()) {
		f设置焦点窗口(*v找->second.m焦点);
	} else {	//如果没有,随便找一个可按键的窗口作为焦点
		if (!a窗口.f状态_i可获得按键焦点()) {
			for (const auto &vp子窗口 : a窗口.ma子窗口) {
				if (vp子窗口->f状态_i可获得按键焦点()) {
					f设置焦点窗口(*vp子窗口);
					return;
				}
			}
		}
		f设置焦点窗口(a窗口);	//没有一个窗口可以做为按键焦点,拿当前窗口作为焦点(可能有问题)
	}
}
void C用户界面::f新建窗口(W窗口 &a父窗口, W窗口 &a子窗口) {
	a子窗口.m父窗口 = &a父窗口;
	a子窗口.m窗口层 = a父窗口.m窗口层 + 1;
	f新建窗口_(a子窗口);
	a父窗口.ma子窗口.push_back(&a子窗口);
	a父窗口.m标志[W窗口::e容器] = true;
	m窗口表变化 = true;
}
void C用户界面::f删除窗口(W窗口 &a) {
	f删除所有子窗口(a);
	if (a.m父窗口) {
		auto &va兄窗口 = a.m父窗口->ma子窗口;
		const auto v开始 = va兄窗口.begin();
		const auto v结束 = va兄窗口.end();
		const auto v新结束 = std::remove(v开始, v结束, &a);
		va兄窗口.erase(v新结束, v结束);
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
	a父窗口.m标志[W窗口::e容器] = false;
}
void C用户界面::f切换窗口(W窗口 &a窗口) {
	if (m活动窗口) {
		f保存活动窗口信息();
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
	const auto f窗口失去焦点 = [&](W窗口 *a窗口1)->bool {
		if (!a窗口1) {
			return true;
		} else if (a窗口1 != &a窗口) {
			a窗口1->m标志[W窗口::e焦点] = false;
			a窗口1->f响应_焦点变化();
			return true;
		}
		return false;
	};
	if (m按键焦点 == m鼠标焦点) {	//按键焦点和鼠标焦点相同时的处理
		if (a窗口.f标志_i纯鼠标()) {	//只切换鼠标焦点
			m鼠标焦点 = &a窗口;
		} else {	//都切换
			if (f窗口失去焦点(m按键焦点)) {
				m按键焦点 = m鼠标焦点 = &a窗口;
			}
		}
	} else {	//按键焦点和鼠标焦点不同时的处理
		if (a窗口.f标志_i纯鼠标()) {
			if (f窗口失去焦点(m鼠标焦点)) {
				m鼠标焦点 = &a窗口;
			}
		} else {
			if (f窗口失去焦点(m鼠标焦点)) {
				m鼠标焦点 = &a窗口;
			}
			if (f窗口失去焦点(m按键焦点)) {
				m按键焦点 = &a窗口;
			}
		}
	}
	//窗口获得焦点,前面因为判断各种切换状态,可能没切换.
	auto vi焦点 = a窗口.m标志[W窗口::e焦点];
	if (!vi焦点) {
		vi焦点 = true;
		a窗口.f响应_焦点变化();
	}
}
void C用户界面::f设置按键焦点窗口(W窗口 &a窗口) {
	if (fi鼠标焦点按下()) {
		m鼠标焦点->f响应_鼠标松开({E按键来源::e无, m鼠标按键, E时间点::e一次, m鼠标坐标});
	}
	f设置焦点窗口(a窗口);
}
void C用户界面::f设置鼠标焦点窗口(W窗口 &a窗口) {
	if (fi鼠标焦点按下()) {
		return;	//鼠标按下时不切换窗口
	}
	f设置焦点窗口(a窗口);
}
void C用户界面::f设置弱按键焦点窗口(W窗口 &a窗口) {
	assert(!a窗口.f标志_i纯鼠标());
	const auto f窗口失去焦点 = [&](W窗口 *a窗口1)->bool {
		if (!a窗口1) {
			return true;
		} else if (a窗口1 != &a窗口) {
			a窗口1->m标志[W窗口::e焦点] = false;
			a窗口1->f响应_焦点变化();
			return true;
		}
		return false;
	};
	if (m按键焦点 == m鼠标焦点) {
		if (f窗口失去焦点(m按键焦点)) {
			m按键焦点 = m鼠标焦点 = &a窗口;
		}
	} else {
		if (f窗口失去焦点(m按键焦点)) {
			m按键焦点 = &a窗口;
		}
	}
	auto vi焦点 = a窗口.m标志[W窗口::e焦点];
	if (!vi焦点) {
		vi焦点 = true;
		a窗口.f响应_焦点变化();
	}
}
void C用户界面::f设置活动窗口(W窗口 &a窗口) {
	//不能在关闭活动窗口同时调用这个函数
	f保存活动窗口信息();
	m调用栈.push(m活动窗口);
	//新窗口
	if (a窗口.m按键切换 == nullptr) {	//如果没设置切换方式,自动设一个
		a窗口.fs按键切换(E按键切换::e坐标);
	}
	m活动窗口 = &a窗口;
}
void C用户界面::f清除活动窗口() {
	m活动窗口 = m调用栈.top();
	const S活动信息 &v信息 = ma活动窗口[m活动窗口];
	if (v信息.m焦点) {
		f设置焦点窗口(*v信息.m焦点);
	}
	m调用栈.pop();
}
void C用户界面::f保存活动窗口信息() {
	if (auto v找 = ma活动窗口.find(m活动窗口); v找 != ma活动窗口.end()) {
		S活动信息 &v信息 = v找->second;
		v信息.m焦点 = m按键焦点;
	} else {
		S活动信息 v信息;
		v信息.m焦点 = m按键焦点;
		ma活动窗口.emplace(m活动窗口, v信息);
	}
}
void C用户界面::f设置平移焦点窗口(W窗口 &a窗口) {
	m平移焦点 = &a窗口;
}
void C用户界面::f清除平移焦点窗口() {
	m平移焦点 = nullptr;
}
void C用户界面::f窗口表排序() {
	//删除已消失窗口
	for (auto &vp窗口 : ma窗口表) {
		if (vp窗口->m标志[W窗口::e销毁]) {
			continue;
		}
		auto v使用标志 = vp窗口->m标志[W窗口::e使用];
		auto v消失标志 = vp窗口->m标志[W窗口::e消失];
		const bool v不使用 = !v使用标志;
		if (vp窗口->m切换.fi已消失() && v不使用) {
			f删除窗口(*vp窗口);
		}
	}
	//检测变化
	if (!m窗口表变化) {
		return;
	}
	//删除销毁窗口
	ma窗口表.erase(std::remove_if(ma窗口表.begin(), ma窗口表.end(), 
		[](W窗口 *ap窗口)->bool {
			return ap窗口->m标志[W窗口::e销毁];
		}), ma窗口表.end());
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
void C用户界面::f播放音效(E声音 a声音) {
	if (m音频) {
		m音频->f播放音效({a声音});
	}
}
}	//namespace 用户界面