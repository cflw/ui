#pragma once
#include "用户界面_头.h"
namespace 用户界面 {
class C用户界面;
class C单向移动布局;
class I画界面;
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
	e键盘,
	e鼠标,
	e手柄,
	e触摸,
	e无,	//内部产生
};
enum class E按键 {
	e上,
	e下,
	e左,
	e右,
	e确定,
	e取消,
	e切换,
	e跳过,
	e无,
};
enum class E按键切换 {
	e序号,
	e坐标,
};
//==============================================================================
// 基础类/结构
//==============================================================================
struct S文本格式 {
	float m字号 = 10;
	E对齐 m水平对齐 = E对齐::e居中;
	bool operator ==(const S文本格式 &a) const {
		return m字号 == a.m字号 && m水平对齐 == a.m水平对齐;
	}
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
	float m目标 = 0;
	float m实际 = 0;	//-1→0出现,0→1消失
	void f重置(float 延时 = 0);
	void f计算(bool 结束, float 间隔);
	bool fi已消失() const;
	bool fi出现中() const;
	bool fi消失中() const;
	float fg透明度() const;
};
class C动画计算 {
public:
	typedef std::function<t向量2(const W窗口 &)> tf动画;
	tf动画 mf坐标 = nullptr;
	tf动画 mf尺寸 = nullptr;
	void f默认();
	//坐标
	static t向量2 f坐标_无(const W窗口 &);
	static t向量2 f坐标_从右到左(const W窗口 &);
	static t向量2 f坐标_下拉(const W窗口 &);
	static t向量2 f坐标_缩放(const W窗口 &);
	//范围
	static t向量2 f尺寸_无(const W窗口 &);
	static t向量2 f尺寸_缩放(const W窗口 &);
};
struct S渐变插值 {
	static constexpr float c速度 = 5;
	float m值 = 0;
	operator float() const;
	float f渐变(bool);	//只能在更新中调用
	float f插值(float, float) const;
};
//==============================================================================
// 事件/响应 参数
//==============================================================================
struct S显示参数 {
	I画界面 &m画界面;
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
};
struct S按键参数 {
	E按键来源 m来源;
	E按键 m按键;
	t向量2 m坐标 = t向量2::c零;
};
//==============================================================================
// 窗口
//==============================================================================
class W窗口 {
public:
	friend C用户界面;
	enum E标志 {
		e使用,
		e销毁,	//不参与计算,刷新窗口表时删除销毁的窗口
		e加载,
		e焦点,
		e禁用,	//不能做为焦点
		e鼠标按下,	//鼠标在窗口范围内按下,在响应中处理
		e按键按下,
		e选中,	//单选框/复选框的选中
		e鼠标,	//只能响应鼠标操作的窗口
		e鼠标范围,	//鼠标在窗口的范围内
		e显示,
		e显示背景,
		e显示边框,
		e容器,	//不会收到一些响应。如果有子窗口，默认为true
		e自定义
	};
	//构造/析构
	W窗口();
	W窗口(int 标识, int 值);
	~W窗口();
	//对象
	void f对象_使用();
	void f对象_销毁();
	bool f对象_i使用();
	//事件,由子窗口给父窗口发消息
	virtual void f事件_按键(W窗口&, const S按键参数 &);
	virtual void f事件_鼠标移上(W窗口&);	//鼠标在窗口上时
	virtual void f事件_窗口值变化(W窗口&, const int &变化前, int &变化后);
	virtual void f事件_窗口移动(W窗口&, const t向量2 &);
	//响应,由用户界面给窗口发消息
	virtual void f响应_初始化();
	virtual void f响应_销毁();
	virtual void f响应_计算();
	virtual void f响应_更新();
	virtual void f响应_显示(const S显示参数 &) const;
	virtual void f响应_按键(const S按键参数 &);	//键盘和手柄的按键
	virtual bool f响应_i范围内(const t向量2 &);	//对鼠标和触摸的坐标进行计算,确定是否在范围内
	virtual void f响应_鼠标按下(const S按键参数 &);	//在范围内按下触发,触摸点击也调用这个
	virtual void f响应_鼠标松开(const S按键参数 &);	//在范围内外单击都会触发,前提是先调用按下,触摸点击也调用这个
	virtual void f响应_字符(const std::vector<wchar_t> &);
	virtual void f响应_方向键(const S方向键参数 &);	//如果不处理，丢给父窗口处理
	//动作,由父窗口给子窗口发消息
	void f动作_添加窗口(W窗口&);	//类的成员子窗口
	void f动作_关闭();	//如果要切换窗口,先关闭窗口再新建窗口
	void f动作_禁用(bool = true);
	void f动作_显示(float 延时 = 0);
	void f动作_隐藏();
	void f动作_获得焦点();
	//其它方法
	C用户界面 &fg引擎() const;
	std::vector<W窗口*> fg子窗口();
	virtual void f属性_s布局(const t向量2 &坐标 = {}, const t向量2 &尺寸 = {});
	void f属性_s布局(const S布局参数 &);
	t向量2 f属性_g坐标() const;
	t向量2 fg动画坐标(const t向量2 &偏移 = t向量2::c零) const;
	t向量2 fg动画尺寸(const t向量2 &偏移 = t向量2::c零) const;
	t矩形 fg动画矩形(const t向量2 &坐标偏移 = t向量2::c零, const t向量2 &范围偏移 = t向量2::c零) const;
	void fs按键切换(E按键切换);
	//t颜色 fg主题颜色(float, float, float);
	bool fi焦点();	//窗口是否获得焦点
	bool fi活动();	//如果父窗口是活动的，子窗口也是活动的。
	bool fi活动窗口();
	bool fi按下();
	bool fi可获得按键焦点() const;
	void f标志_s默认();
	bool f标志_g继承(size_t) const;
	bool f标志_g继承_否优先(size_t) const;
	void f标志_s继承显示();
	bool f标志_i显示() const;
	bool f标志_i显示边框() const;
	bool f标志_i显示背景() const;
public:	//管理需要，由"C用户界面"控制
	W窗口 *m父窗口 = nullptr;
	int m序号 = -1;	//在窗口表的序号
	int m窗口层 = 0;
	std::vector<W窗口*> ma子窗口;
	W窗口 *m焦点窗口;	//指子窗口
	E按键 m鼠标按键 = E按键::e无;
	I按键切换 *m按键切换 = nullptr;
public:	//可变
	t向量2 m坐标 = t向量2::c零;
	t向量2 m尺寸 = t向量2(8, 8);
	C切换动画 m切换;
	C动画计算 m动画;
	S渐变插值 m焦点渐变;
	int m标识;
	int m值;
	t标志 m标志;
	t标志 m继承标志;
};
}	//namespace 用户界面
//=============================================================================
namespace std {
template<> struct hash<用户界面::S文本格式> {
	size_t operator()(const 用户界面::S文本格式 &) const;
};
}