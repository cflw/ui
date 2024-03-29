﻿module;
#include "用户界面_控件.h"
#include "用户界面_接口.h"
#include "用户界面_布局.h"
export module 用户界面.控件.选项卡;
export namespace 用户界面 {
//==============================================================================
// 声明
//==============================================================================
class W选项卡组 : public W窗口 {
public:
	static constexpr float c页按钮宽 = 50;
	static constexpr float c页按钮高 = 20;
	static constexpr float c文本大小 = 16;
	static const S文本样式 c文本样式;
	enum E标识 {
		e页按钮
	};
	enum E标志 {
		e活动 = W窗口::e自定义,
	};
	class W页按钮 : public W按钮 {
	public:
		W页按钮(int 值);
		void f响应_更新() override;
		void f响应_显示(const S显示参数 &) const override;
		S渐变插值 m活动渐变;
	};
	struct S页 {
		W窗口 *m窗口 = nullptr;
		std::unique_ptr<W页按钮> m按钮;
	};
	W选项卡组(int = -1, int = 0);
	void f事件_按键(W窗口 &, const S按键参数 &);
	void f响应_初始化();
	void f动作_添加页(W窗口 &页, const std::wstring_view &标签);
	void f动作_方向切换(bool 方向);
	void f动作_切换(int 序号);
	void f属性_s页按钮尺寸(const t向量2 &);
	void f属性_s页按钮宽(float);
	void f属性_s页按钮高(float);
	S布局参数 f属性_g页按钮布局(int 序号) const;
	void f重置页按钮布局();
	void f隐藏页(int 序号);
	void f显示页(int 序号);
	std::vector<S页> ma页;
	int m页序号 = 0;
	t向量2 m页按钮尺寸{c页按钮宽, c页按钮高};
};
}	//namespace 用户界面
module : private;
namespace 用户界面 {
//==============================================================================
// 选项卡页按钮
//==============================================================================
W选项卡组::W页按钮::W页按钮(int a值):
	W按钮(e页按钮, a值) {
}
void W选项卡组::W页按钮::f响应_更新() {
	W按钮::f响应_更新();
	m活动渐变.f渐变(m标志[e活动]);
}
void W选项卡组::W页按钮::f响应_显示(const S显示参数 &a) const {
	if (m尺寸.x == 0 || m尺寸.y == 0) {
		return;
	}
	const float v按下 = m标志[e鼠标按下] ? 0.2f : 0;
	const float v切换透明 = fg总切换().fg透明度();
	const t矩形 &v动画矩形 = fg动画矩形();
	//前景边框
	const t颜色 v活动色 = a.m主题.fg颜色(1, 1, (m活动渐变.f插值(0, 0.6f) + m焦点渐变.f插值(0, 0.4f)) * v切换透明);
	if (f标志_i显示边框()) {
		a.m图形.f绘制矩形(v动画矩形, v活动色);
	}
	//文本
	const t颜色 v前景色 = a.m主题.fg颜色(1, 1, m焦点渐变.f插值(0.5f, 1) * v切换透明);
	if (f属性_i有文本()) {
		a.m图形.f绘制文本(m文本, v动画矩形, v前景色, m样式);
	}
}
//==============================================================================
// 选项卡组
//==============================================================================
const S文本样式 W选项卡组::c文本样式 = {c文本大小, E对齐::e居中};
W选项卡组::W选项卡组(int a标识, int a值):
	W窗口(a标识, a值) {
}
void W选项卡组::f事件_按键(W窗口 &a窗口, const S按键参数 &a参数) {
	switch (a窗口.m标识) {
	case e页按钮:
		if (a参数.m按键 == E按键::e确定) {
			f动作_切换(a窗口.m值);
		}
		break;
	}
}
void W选项卡组::f响应_初始化() {
	for (auto &[v窗口, v按钮] : ma页) {
		f动作_添加窗口(*v窗口);
		f动作_添加窗口(*v按钮);
		v按钮->f动作_显示();
	}
	f显示页(m页序号);
}
void W选项卡组::f动作_添加页(W窗口 &a页, const std::wstring_view &a标签) {
	S页 v页;
	v页.m窗口 = &a页;
	a页.f属性_s布局({t向量2::c零, m尺寸});
	const int v位置 = (int)ma页.size();
	v页.m按钮 = std::make_unique<W页按钮>(v位置);
	v页.m按钮->f属性_s文本(a标签, c文本样式);
	v页.m按钮->f属性_s布局(f属性_g页按钮布局(v位置));
	ma页.push_back(std::move(v页));
}
void W选项卡组::f动作_方向切换(bool a方向) {
	int v序号 = m页序号;
	v序号 += a方向 ? 1 : -1;
	const int v位置 = (int)ma页.size();
	v序号 = 数学::f环绕<int>(v序号, 0, v位置);
	f动作_切换(v序号);
}
void W选项卡组::f动作_切换(int a序号) {
	if (a序号 == m页序号) {
		return;
	}
	f隐藏页(m页序号);
	f显示页(a序号);
	m页序号 = a序号;
}
void W选项卡组::f属性_s页按钮尺寸(const t向量2 &a) {
	m页按钮尺寸 = a;
}
void W选项卡组::f属性_s页按钮宽(float a) {
	m页按钮尺寸.x = a;
}
void W选项卡组::f属性_s页按钮高(float a) {
	m页按钮尺寸.y = a;
}
S布局参数 W选项卡组::f属性_g页按钮布局(int a序号) const {
	const float v下 = m尺寸.y * 0.5f;
	const float v上 = v下 + m页按钮尺寸.y;
	const float v左 = -m尺寸.x * 0.5f + m页按钮尺寸.x * a序号;
	const float v右 = v左 + m页按钮尺寸.x;
	const t矩形 v矩形 = t矩形::fc左上右下(v左, v上, v右, v下);
	S布局参数 v;
	v.m坐标 = v矩形.fg中心();
	v.m尺寸 = v矩形.fg尺寸();
	return v;
}
void W选项卡组::f重置页按钮布局() {
	const float v下 = m尺寸.y * 0.5f;
	const float v上 = v下 + m页按钮尺寸.y;
	int i = 0;
	for (const auto &[v窗口, v按钮] : ma页) {
		const float v左 = -m尺寸.x * 0.5f + m页按钮尺寸.x * i;
		const float v右 = v左 + m页按钮尺寸.x;
		const t矩形 v矩形 = t矩形::fc左上右下(v左, v上, v右, v下);
		v按钮->f属性_s布局(v矩形);
		++i;
	}
}
void W选项卡组::f隐藏页(int a序号) {
	S页 &v页 = ma页[a序号];
	v页.m窗口->f动作_隐藏();
	v页.m按钮->m标志[e活动] = false;

}
void W选项卡组::f显示页(int a序号) {
	S页 &v页 = ma页[a序号];
	v页.m窗口->f动作_显示();
	v页.m按钮->m标志[e活动] = true;
}
}	//namespace 用户界面