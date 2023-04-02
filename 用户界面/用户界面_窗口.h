#pragma once
#include "用户界面_基础.h"
namespace 用户界面 {
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
	virtual void f事件_按键(W窗口 &, const S按键参数 &);
	virtual void f事件_鼠标移上(W窗口 &);	//鼠标在窗口上时
	virtual void f事件_窗口值变化(W窗口 &, const int &变化前, int &变化后);
	virtual void f事件_窗口移动(W窗口 &, const t向量2 &);
	virtual void f事件_焦点变化(W窗口 &);
	//响应,由用户界面给窗口发消息
	virtual void f响应_初始化();	//在添加窗口,与父窗口绑定时调用
	virtual void f响应_销毁();	//窗口对象即将被销毁时调用
	virtual void f响应_计算();	//每计算帧调用
	virtual void f响应_更新();	//每渲染帧调用
	virtual void f响应_显示(const S显示参数 &) const;	//每帧显示时调用
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
	void f动作_显示(float 延时 = 0);	//必须在 f动作_添加窗口 后面调用
	void f动作_隐藏(bool 消失动画 = true);
	void f动作_获得焦点();
	void f动作_获得弱焦点();
	void f动作_释放焦点();	//只有获得焦点的窗口才能调用,重新选择一个可获得焦点的窗口
	//其它方法
	std::vector<W窗口 *> fg子窗口();
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
	int m窗口层 = 0;	//窗口层级,从0开始,更深一层+1
	std::vector<W窗口 *> ma子窗口;
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
}	//namespace 用户界面