#include "用户界面_按键切换.h"
#include <cflw工具_运算.h>
#include "用户界面_基础.h"
namespace 用户界面 {
I按键切换::I按键切换(C用户界面 &a引擎, W窗口 &a窗口):
	m引擎(&a引擎), m窗口(&a窗口) {
}
//==============================================================================
// 按序号切换焦点
//==============================================================================
void C按键切换_序号::f更新() {
	//创建树
	typedef 工具::C树<W窗口*> t窗口树;
	typedef t窗口树::C节点 t窗口树节点;
	typedef t窗口树::t叶 t窗口树叶;
	t窗口树 v窗口树;
	std::function<void(t窗口树叶 &, W窗口 *)> f创建树 = [&](t窗口树叶 &a树, W窗口 *a窗口) {
		//添加叶子,并剔除空窗口销毁的窗口
		m引擎->f遍历子窗口(a窗口, [&](W窗口 &a) {
			a树.push_back(&a);
		});
		//排序
		std::sort(a树.begin(), a树.end(),
			[](const t窗口树节点 &a0, const t窗口树节点 &a1) {
			W窗口 *v0 = a0.m值;
			W窗口 *v1 = a1.m值;
			if (v0->m标识 != v1->m标识) {
				return v0->m标识 < v1->m标识;
			} else {
				return v0->m值 < v1->m值;
			}
		});
		//处理叶子
		for (auto &v子 : a树) {
			if (v子.m值->ma子窗口.size() != 0) {
				v子.m叶 = std::make_unique<std::vector<t窗口树节点>>();
				f创建树(*v子.m叶, v子.m值);
			}
		}
	};
	f创建树(v窗口树.m叶, m窗口);
	//排序
	int v序号 = 0;
	ma窗口.clear();
	std::function<void(t窗口树叶 &)> f插入树 = [&](t窗口树叶 &a树) {
		for (auto &v子 : a树) {
			ma窗口.push_back(v子.m值);
			v子.m值->m序号 = v序号;
			++v序号;
			if (v子.m叶) {
				f插入树(*v子.m叶);
			}
		}
	};
	f插入树(v窗口树.m叶);
}
W窗口 *C按键切换_序号::f上下切换(bool a前进) {
	return f切换(a前进);
}
W窗口 *C按键切换_序号::f左右切换(bool a前进) {
	return f切换(a前进);
}
W窗口 *C按键切换_序号::f切换(bool a前进) {
	if (ma窗口.empty()) {
		return nullptr;
	}
	using t迭代器 = std::vector<W窗口*>::iterator;
	const t迭代器 v开始 = ma窗口.begin();
	const t迭代器 v结束 = ma窗口.end();
	const t迭代器 v当前 = std::find(v开始, v结束, m引擎->m按键焦点);
	t迭代器 v下个 = v当前;
	const auto f变化0 = a前进 ? &工具::f环绕自增<t迭代器> : &工具::f环绕自减<t迭代器>;
	const auto f变化 = std::bind(f变化0, v开始, v结束, std::placeholders::_1);
	do {
		v下个 = f变化(v下个);
		W窗口 *v窗口 = *v下个;
		if (!v窗口->f状态_i可获得按键焦点()) {
			continue;
		}
		return v窗口;
	} while (v下个 != v当前);
	return nullptr;
}
//==============================================================================
// 按坐标切换焦点
//==============================================================================
void C按键切换_坐标::f更新() {
	ma窗口.clear();
	const std::function<void(W窗口&)> f添加 = [&](W窗口 &a) {
		for (W窗口 *vp窗口 : a.ma子窗口) {
			f添加(*vp窗口);
		}
		ma窗口.push_back(&a);
	};
	f添加(*m窗口);
}
W窗口 *C按键切换_坐标::f上下切换(bool a前进) {
	return f切换(&t向量2::y, &t向量2::x, a前进 ? 工具::f小于<float> : 工具::f大于<float>);
}
W窗口 *C按键切换_坐标::f左右切换(bool a前进) {
	return f切换(&t向量2::x, &t向量2::y, a前进 ? 工具::f大于<float> : 工具::f小于<float>);
}
W窗口 *C按键切换_坐标::f切换(const float t向量2::*ap主顺序, const float t向量2::*ap次顺序, const std::function<bool(const float &, const float &)> &af主比较) {
	struct S选择 {
		W窗口 *m窗口 = nullptr;
		float m主距离 = 0, m次距离 = 0, m直线距离 = 0;
	} v近, v远;
	const float &v焦点坐标0 = m引擎->m按键焦点->f属性_g坐标().*ap主顺序;
	const float &v焦点坐标1 = m引擎->m按键焦点->f属性_g坐标().*ap次顺序;
	const auto &vf主正比较 = af主比较;
	const auto &vf主反比较 = std::bind(工具::f非, std::bind(af主比较, std::placeholders::_1, std::placeholders::_2));
	for (W窗口 *vp窗口 : ma窗口) {	//遍历选择前进方向最近的窗口
		if (!vp窗口->f状态_i可获得按键焦点()) {
			continue;
		}
		const float &v当前坐标0 = vp窗口->f属性_g坐标().*ap主顺序;
		if (v焦点坐标0 == v当前坐标0) {
			continue;
		}
		const float &v当前坐标1 = vp窗口->f属性_g坐标().*ap次顺序;
		const float v主距离1 = std::abs(v焦点坐标0 - v当前坐标0);
		const float v次距离1 = std::abs(v焦点坐标1 - v当前坐标1);
		const float v直线距离 = std::hypot(v主距离1, v次距离1);
		const auto f选择 = [&](S选择 &a选择, const std::function<bool(const float &, const float &)> &af主比较1, const std::function<bool(const float &, const float &)> &af距离比较) {
			const auto f更新选择 = [&]() {
				a选择.m窗口 = vp窗口;
				a选择.m主距离 = v主距离1;
				a选择.m次距离 = v次距离1;
				a选择.m直线距离 = v直线距离;
			};
			if (af主比较1(v当前坐标0, v焦点坐标0)) {
				if (a选择.m窗口) {
					if ((v直线距离 <= a选择.m直线距离) && af距离比较(v主距离1, a选择.m主距离)) {
						f更新选择();
					} else if (v主距离1 == a选择.m主距离 && v次距离1 < a选择.m次距离) {
						f更新选择();
					}
				} else {
					f更新选择();
				}
			}
		};
		f选择(v近, vf主正比较, 工具::f小于<float>);
		f选择(v远, vf主反比较, 工具::f大于<float>);
	}
	return v近.m窗口 ? v近.m窗口 : v远.m窗口;
}
}