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
enum class E时间点 {
	e一次,
	e开始,
	e进行中,
	e结束,
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
//==============================================================================
// 窗口
//==============================================================================
class W窗口 {
public:
	friend C用户界面;
	enum E标志 {
		e使用,	//管理对象生命周期
		e销毁,	//不参与计算,刷新窗口表时删除销毁的窗口
		e加载,
		e焦点,	//焦点指示
		e禁用,	//当前窗口不能做为任何焦点,默认为真
		e鼠标按下,	//鼠标在窗口范围内按下,在响应中处理
		e按键按下,
		e选中,	//单选框/复选框的选中
		//e纯鼠标,	//只能获得鼠标焦点,响应鼠标操作
		e鼠标范围,	//鼠标在窗口的范围内
		e显示,	//显示当前窗口和子窗口
		e显示背景,
		e显示边框,
		e容器,	//影响窗口的一些交互行为. 如果有子窗口,默认为真
		e消失,	//消失动画,消失之后是不显示
		e可获得鼠标焦点,
		e可获得按键焦点,
		e可获得平移焦点,
		//e水平平移,	//可通过拖动来移动
		//e垂直平移,
		e自定义
	};
	//构造/析构
	W窗口();
	W窗口(int 标识, int 值);
	~W窗口();
	//对象
	void f对象_使用();
	void f对象_销毁();
	bool f对象_i使用() const;
	//事件,由子窗口给父窗口发消息
	virtual void f事件_按键(W窗口&, const S按键参数 &);
	virtual void f事件_鼠标移上(W窗口&);	//鼠标在窗口上时
	virtual void f事件_窗口值变化(W窗口&, const int &变化前, int &变化后);
	virtual void f事件_窗口移动(W窗口&, const t向量2 &);
	virtual void f事件_焦点变化(W窗口&);
	//响应,由用户界面给窗口发消息
	virtual void f响应_初始化();
	virtual void f响应_销毁();
	virtual void f响应_计算();
	virtual void f响应_更新();
	virtual void f响应_显示(const S显示参数 &) const;
	virtual void f响应_按键(const S按键参数 &);	//键盘和手柄的按键
	virtual bool f响应_i范围内(const t向量2 &);	//对鼠标和触摸的坐标进行计算,确定是否在范围内
	virtual void f响应_鼠标按下(const S按键参数 &);	//在鼠标焦点范围内按下触发,触摸点击也调用这个
	virtual void f响应_鼠标松开(const S按键参数 &);	//在鼠标焦点范围内外单击都会触发,前提是先调用按下,触摸点击也调用这个
	virtual void f响应_字符(const std::vector<wchar_t> &);
	virtual void f响应_方向键(const S方向键参数 &);	//如果不处理，丢给父窗口处理
	virtual void f响应_焦点变化();	//获得焦点或失去焦点时调用,在函数内调用 f状态_i焦点 以检查自身是否有焦点,切换焦点时先响应失去焦点的窗口在响应获得焦点的窗口
	virtual void f响应_水平平移(const S平移参数 &);
	virtual void f响应_垂直平移(const S平移参数 &);
	//引擎内调用的计算&更新
	void f计算_切换();
	void f计算_显示();
	void f计算_平移();
	void f更新_切换();
	//动作,由父窗口给子窗口发消息
	void f动作_添加窗口(W窗口 &, bool 显示 = false);	//类的成员子窗口
	void f动作_关闭();	//如果要切换窗口,先关闭窗口再新建窗口
	void f动作_启用(bool 启用 = true);	//接收按键操作
	void f动作_禁用(bool 禁用 = true);	//启用的反操作
	void f动作_显示(float 延时 = 0);
	void f动作_隐藏(bool 消失动画 = true);
	void f动作_获得焦点();
	void f动作_获得弱焦点();
	void f动作_释放焦点();	//只有获得焦点的窗口才能调用,重新选择一个可获得焦点的窗口
	//其它方法
	static C用户界面 &fg引擎();
	std::vector<W窗口*> fg子窗口();
	virtual void f属性_s布局(const S布局参数 &);
	t向量2 f属性_g坐标() const;	//屏幕坐标
	t向量2 fg动画坐标(const t向量2 &偏移 = t向量2::c零) const;
	t向量2 fg动画尺寸(const t向量2 &偏移 = t向量2::c零) const;
	t矩形 fg动画矩形(const t向量2 &坐标偏移 = t向量2::c零, const t向量2 &范围偏移 = t向量2::c零) const;
	const C总切换 &fg总切换() const;	//结合父窗口,计算出总的切换
	void fs按键切换(E按键切换);
	C平移计算 &fg平移计算();
	void f按键切换计算(const S方向键参数 &);	//m按键切换 必需有值
	int fg组合标识值() const;
	//t颜色 fg主题颜色(float, float, float);
	//由引擎控制的标志状态.一直变化的值叫状态,很少变化或不变的值叫属性
	bool f状态_i焦点() const;	//窗口是否获得焦点
	bool f状态_i弱焦点() const;	//有按键焦点没有鼠标焦点
	bool f状态_i活动() const;	//如果父窗口是活动的，子窗口也是活动的。
	bool f状态_i活动窗口() const;
	bool f状态_i按下() const;
	bool f状态_i平移焦点() const;
	bool f状态_i显示完成() const;	//有显示出来且显示完成的窗口
	bool f状态_i可获得按键焦点() const;
	bool f状态_i可获得鼠标焦点() const;
	bool f状态_i可获得平移焦点() const;
	//标志取置
	bool f标志_i启用() const;
	void f标志_s默认();
	bool f标志_g继承(size_t) const;
	bool f标志_g继承_否优先(size_t) const;
	void f标志_s继承显示();
	bool f标志_i显示() const;
	bool f标志_i显示边框() const;
	bool f标志_i显示背景() const;
	void f标志_s平移(bool = true);
	bool f标志_i纯鼠标() const;
	void f标志_s纯鼠标();
public:	//管理需要，由 C用户界面 控制
	W窗口 *m父窗口 = nullptr;
	int m序号 = -1;	//在窗口表的序号
	int m窗口层 = 0;
	std::vector<W窗口*> ma子窗口;
	W窗口 *m焦点窗口 = nullptr;	//指子窗口
	E按键 m鼠标按键 = E按键::e无;
	I按键切换 *m按键切换 = nullptr;
	C平移计算 *m平移计算 = nullptr;
public:	//可变
	t向量2 m坐标 = t向量2::c零;	//相对于父窗口的坐标
	t向量2 m尺寸 = t向量2(8, 8);
	C切换动画 m切换;
	C总切换 m总切换;
	C动画计算 m动画;
	S渐变插值 m焦点渐变;
	int m标识;
	int m值;
	t标志 m标志;
	t标志 m继承标志;
};
constexpr int f组合标识值(int a标识, int a值) {
	return a标识 << 16 | a值;
}
}	//namespace 用户界面
//==============================================================================
namespace std {
template<> struct hash<用户界面::S文本格式> {
	size_t operator()(const 用户界面::S文本格式 &) const;
};
}	//namespace std