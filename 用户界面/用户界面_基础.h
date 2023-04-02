#pragma once
#include "用户界面_头.h"
namespace 用户界面 {
class C用户界面;
class C单向移动布局;
class I图形设备;
class I输入设备;
class I按键切换;
//==============================================================================
// 枚举/常量
//==============================================================================
enum E对齐 {
	e居左,
	e居右,
	e居中,
	e居上,
	e居下,
};
enum class E按键来源 {
	e无,	//内部产生
	e键盘,
	e鼠标,
	e手柄,
	e触摸,
	c数量,
};
enum class E按键 {
	e无,
	e上,
	e下,
	e左,
	e右,
	e确定,
	e取消,
	e切换,
	e跳过,
	c数量,
};
enum class E按键切换 {
	e序号,
	e坐标,
};
enum class E时间点 {	//一个过程的时间阶段
	e一次,	//一帧内就能处理完毕
	e开始,	//持续过程的开始
	e进行中,	//持续过程的中间
	e结束,	//持续过程的结束
};
//==============================================================================
// 基础类/结构
//==============================================================================
struct S文本样式 {
	static const S文本样式 c默认样式;
	static constexpr float c字号 = 10;	//默认字号
	static constexpr E对齐 c对齐 = E对齐::e居中;	//默认对齐
	float m字号 = c字号;
	E对齐 m水平对齐 = c对齐;
	bool m粗体 = false;
	bool m斜体 = false;
	bool m下划线 = false;
	bool m删除线 = false;
	auto operator <=>(const S文本样式 &a) const = default;
};
struct S主题 {
	static const S主题 c白;
	S主题(const t颜色 &, const t颜色 &);
	t颜色 m前景色;
	t颜色 m背景色;
	t颜色 fg颜色(float 插值, float 亮度, float 透明度) const;
};
class C切换动画 {
public:
	static constexpr float c渐入开始 = -1;
	static constexpr float c渐入结束 = 0;
	static constexpr float c渐出开始 = 0;
	static constexpr float c渐出结束 = 1;
	void f重置(float 延时 = 0);
	void f计算(bool 结束, float 间隔);
	bool fi已消失() const;
	bool fi出现中() const;
	bool fi消失中() const;
	float fg目标() const;
	float fg实际() const;
	float fg透明度() const;
	float m目标 = 0;
	float m实际 = -1;	//-1→0出现,0→1消失
};
class C总切换 {
public:
	void f更新(W窗口&);
	float fg目标() const;
	float fg实际() const;
	float fg透明度() const;
	float m最小目标, m最大目标, m最小实际, m最大实际;
};
class C动画计算 {
public:
	typedef std::function<t向量2(const W窗口 &)> tf动画;
	void f默认();
	//坐标
	static t向量2 f坐标_无(const W窗口 &);
	static t向量2 f坐标_从右到左(const W窗口 &);
	static t向量2 f坐标_下拉(const W窗口 &);
	static t向量2 f坐标_缩放(const W窗口 &);
	//范围
	static t向量2 f尺寸_无(const W窗口 &);
	static t向量2 f尺寸_缩放(const W窗口 &);
public:
	tf动画 mf坐标 = nullptr;
	tf动画 mf尺寸 = nullptr;
};
struct S渐变插值 {
	static constexpr float c速度 = 5;
	float m值 = 0;
	operator float() const;
	float f渐变(bool);	//只能在更新中调用
	float f插值(float, float) const;
};
class C平移计算 {
public:
	static constexpr float c停止加速度 = -100;
	C平移计算(W窗口 &);
	bool fi来源(E按键来源) const;
	void f重置(E按键来源, const t向量2 &);
	void f拖动计算(const t向量2 &);
	void f滚轮计算(const t向量2 &);
	void f停止计算();
	void f调用响应();
	W窗口 *m窗口 = nullptr;
	E按键来源 m来源;
	E时间点 m时间点;
	t向量2 m开始位置;
	t向量2 m当前位置;
	t向量2 m速度;
	t向量2 m平滑速度;
};
//==============================================================================
// 事件/响应 参数
//==============================================================================
struct S显示参数 {
	I图形设备 &m图形;
	S主题 &m主题;
};
struct S方向键参数 {
	int x = 0;
	int y = 0;
	bool fi上() const;
	bool fi下() const;
	bool fi左() const;
	bool fi右() const;
	bool fi上下() const;
	bool fi左右() const;
};
struct S布局参数 {
	t向量2 m坐标;
	t向量2 m尺寸;
	S布局参数(const t向量2 & = t向量2::c零, const t向量2 & = t向量2::c零);
	S布局参数(const t矩形 &);
};
struct S按键参数 {
	E按键来源 m来源;
	E按键 m按键;
	E时间点 m时间点;
	t向量2 m坐标 = t向量2::c零;
};
struct S平移参数 {
	E按键来源 m来源;
	E时间点 m时间点;
	float m开始位置;
	float m当前位置;
	float m速度;
};
constexpr int f组合标识值(int a标识, int a值) {
	return a标识 << 16 | a值;
}
}	//namespace 用户界面
//==============================================================================
namespace std {
template<> struct hash<用户界面::S文本样式> {
	size_t operator()(const 用户界面::S文本样式 &) const;
};
}	//namespace std