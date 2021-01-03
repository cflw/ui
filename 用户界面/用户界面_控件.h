#pragma once
#include "用户界面_头.h"
#include "用户界面_基础.h"
namespace 用户界面 {
//==============================================================================
// 控件基类
//==============================================================================
class C控件文本 {
public:
	static const std::wstring c默认文本;
	static constexpr float c字号 = 10;
	C控件文本() = default;
	C控件文本(const std::wstring &, float 字号 = c字号, E对齐 对齐 = e居中);
	void f属性_s空文本();
	void f属性_s文本(const std::wstring_view &文本, float 字号 = c字号, E对齐 对齐 = e居中);
	void f属性_s文本内容(const std::wstring_view &);
	void f属性_s文本字号(float);
	void f属性_s文本对齐(E对齐);
	bool f属性_i有文本() const;
public:
	std::wstring m文本 = c默认文本;
	float m字号 = c字号;
	E对齐 m对齐 = e居左;
};
//专门的窗口容器类,会响应所有鼠标消息(窗口基类只响应部分消息)
class W窗口框架 : public W窗口 {
public:
	W窗口框架(int = -1, int = 0);
	void f响应_鼠标按下(const S按键参数 &) override;
	void f响应_鼠标松开(const S按键参数 &) override;
	bool f响应_i范围内(const t向量2 &) override;
};
//不显示,只响应的按钮
class W空白按钮 : public W窗口 {
public:
	W空白按钮(int = -1, int = 0);
	void f响应_鼠标按下(const S按键参数 &) override;
	void f响应_鼠标松开(const S按键参数 &) override;
	void f动作_按键(const S按键参数 &);
	void f动作_按键(E按键 = E按键::e确定);
};
//==============================================================================
// 基础控件
//==============================================================================
//标签
class W标签 : public W窗口, public C控件文本 {
public:
	static const std::wstring c默认文本;
	W标签(int = -1, int = 0);
	void f响应_显示(const S显示参数 &) const override;
	void f属性_s透明度(float);
	float m透明度 = 1;
};
//图片
class I图片源;
class W图片 : public W窗口 {
public:
	W图片(int = -1, int = 0);
	void f响应_显示(const S显示参数 &) const override;
	void f属性_s图片源(const I图片源 &);
	void f属性_s透明度(float);
	float m透明度 = 1;
	const I图片源 *m图片源 = nullptr;
};
//按钮
class W按钮 : public W空白按钮, public C控件文本 {
public:
	static const std::wstring c默认文本;
	static constexpr float c建议高度 = 24;
	W按钮(int = -1, int = 0);
	void f响应_显示(const S显示参数 &) const override;
};
//文本框
class W文本框 : public W窗口 {
public:
	enum E标志 {
		e多行 = W窗口::e自定义,
	};
	static constexpr float c行高度 = 14;
	static constexpr float c边距 = 2;
	static constexpr float c最小高度 = c行高度 + c边距 * 2;
	static constexpr float c字号 = 14;
	W文本框(int = -1, int = 0);
	static float f按行计算高度(int);
	void f响应_显示(const S显示参数 &) const override;
	void f响应_字符(const std::vector<wchar_t> &) override;
	void f属性_s布局(const S布局参数 &) override;
	void f属性_s多行(bool);
	void f属性_s限制字数(size_t);
	std::wstring m文本;
	size_t m限制字数 = 10;
};
//输入法
class W虚拟键盘 : public W窗口 {
public:
	enum E按键分布 {
		e数字 = 0,
		e字母 = 10,
		e功能 = 36
	};
	W虚拟键盘();
	W按钮 v按键[38];	//数字10+字母26+上档+退格
};
//连击按钮,按住会不断往父窗口发送按键确定事件
class W连击按钮 : public W按钮 {
public:
	W连击按钮(int = -1, int = 0);
	void f响应_计算() override;
	void f响应_按键(const S按键参数 &) override;
	void f响应_鼠标按下(const S按键参数 &) override;
	void f响应_鼠标松开(const S按键参数 &) override;
	void f属性_s连击间隔(float 首次, float 每次 = 0);
	void f动作_连击重置();
	void f确定回调(const S按键参数 &);
	float m首次;
	float m每次;
	float m计时;
	int m次数;
};
//滑动块,可以用鼠标按住拖动
class W滑动块 : public W按钮 {
public:
	W滑动块(int = -1, int = 0);
	void f响应_初始化() override;
	void f响应_计算() override;
	bool f响应_i范围内(const t向量2 &) override;
	void f响应_鼠标按下(const S按键参数 &) override;
	void f响应_鼠标松开(const S按键参数 &) override;
	void f属性_s布局(const S布局参数 &) override;
	t向量2 m鼠标坐标;
	t向量2 m被动坐标;	//被其它窗口改变的坐标,有平滑移动
};
//滑动块2,响应平移消息
class W滑动块2 : public W按钮 {
public:
	W滑动块2(int = -1, int = 0);
	void f响应_初始化() override;
	void f响应_计算() override;
	bool f响应_i范围内(const t向量2 &) override;
	void f响应_垂直平移(const S平移参数 &) override;
	void f响应_水平平移(const S平移参数 &) override;
	void f属性_s布局(const S布局参数 &) override;
	void f响应平移(const S平移参数 &, float (t向量2::*));
	t向量2 m被动坐标;
};
//复选框
class W复选框 : public W按钮 {
public:
	enum E标志 {
		e选中 = W窗口::e自定义,
		e自定义,
	};
	W复选框(int = -1, int = 0);
	void f响应_初始化() override;
	void f响应_按键(const S按键参数 &) override;
	void f响应_鼠标按下(const S按键参数 &) override;
	void f响应_鼠标松开(const S按键参数 &) override;
	void f属性_反选();
	bool f属性_i选中() const;
	const std::wstring &f属性_g字符() const;
};
//==============================================================================
// 复杂控件-滚动条
//==============================================================================
class W垂直滚动条 : public W窗口 {
public:
	enum E标志 {
		e使用滑块 = e自定义
	};
	enum E控件编号 {
		e向上,
		e向下,
		e滑块
	};
	static constexpr float c字号 = 10;
	static constexpr int c按钮滚动百分比 = 5;
	static constexpr int c空白滚动百分比 = 20;
	static constexpr float c边长 = 16;
	static constexpr int c最大位置 = 1;
	W垂直滚动条(int = -1, int = 0);
	void f事件_窗口移动(W窗口 &, const t向量2 &) override;
	void f事件_按键(W窗口 &, const S按键参数 &) override;
	void f响应_初始化() override;
	void f响应_计算() override;
	void f属性_s布局(const S布局参数 &) override;
	void f属性_s布局(W窗口&, float 上偏移, float 下偏移);	//垂直滚动条附着在窗口右边
	void f属性_s滚动值(int 最大位置, int 显示范围);	//滑块位置=[0,最大位置), 滚到底时最后一行在顶部
	void f属性_s容纳值(int 最大位置, int 显示范围);	//滑块位置=[0,最大位置-显示范围], 滚到底时最后一行在底部
	void f属性_s滚动值_(int 实际最大位置, int 显示最大位置, int 显示范围);
	void f属性_s当前位置(int);
	void f属性_s滑块位置(int, bool 平滑 = true);
	int f属性_g当前位置() const;	//实时位置
	int f属性_g滑块位置() const;	//动画位置,[0, 最大位置)
	void f属性_使用中间(bool);	//是否使用空白和滑块
	void f属性_使用全部(bool);	//是否使用全部
	bool f属性_i使用中间() const;
	bool f属性_i使用全部() const;
	void f动作_百分比滚动(int 百分比);
	void f动作_坐标滚动(float);
	void f更新滑块位置();
	W连击按钮 w向上按钮{e向上, c按钮滚动百分比};
	W连击按钮 w向下按钮{e向下, c按钮滚动百分比};
	W连击按钮 w向上空白{e向上, c空白滚动百分比};
	W连击按钮 w向下空白{e向下, c空白滚动百分比};
	W滑动块 w滑块{e滑块};
	int m最大位置;
	int m当前位置;	//值范围[0, 最大)
	int m显示范围;
	float m滑块移动范围;
};
//==============================================================================
// 复杂控件-下拉列表
//==============================================================================
class W下拉列表 : public W窗口框架 {
public:
	enum E标志 {
		e下拉 = W窗口::e自定义,
		e更新列表,
	};
	enum E控件编号 {
		e中心按钮,
		e下拉按钮
	};
	static constexpr float c字号 = 14;
	W下拉列表(int = -1, int = 0);
	void f事件_按键(W窗口 &, const S按键参数 &) override;
	void f响应_初始化() override;
	bool f响应_i范围内(const t向量2 &) override;
	void f响应_方向键(const S方向键参数 &) override;
	void f属性_s列表(const std::vector<std::wstring> &);
	std::vector<std::wstring> &f属性_g列表();
	const std::vector<std::wstring> &f属性_g列表() const;
	t标志::reference fi下拉();
	float f下拉时_g底部范围();	//是负数
	bool f下拉时_i范围内(const t向量2 &);
	float f下拉时_g半高度();
	void f开始下拉();
	void f结束下拉();
	std::wstring &f属性_g选中文本();
	std::vector<std::wstring> ma文本;
	std::vector<W按钮> ma下拉按钮;
	W按钮 w中心按钮{e中心按钮};
	W标签 w标签;
	int m选择项 = 0;
	int m焦点项 = -1;
};
//==============================================================================
// 复杂控件-横向选择列表
//==============================================================================
class W横向选择列表 : public W窗口 {
public:
	enum E标识 {
		e标签框,
		e左按钮,
		e右按钮,
	};
	class W显示框 : public W窗口, public C控件文本 {
	public:
		W显示框(int = -1, int = 0);
		void f响应_显示(const S显示参数 &) const override;
		void f响应_方向键(const S方向键参数 &) override;
	};
	static constexpr float c边长 = 16;
	W横向选择列表(int = -1, int = 0);
	void f事件_按键(W窗口 &, const S按键参数 &) override;
	void f响应_初始化() override;
	void f属性_s布局(const S布局参数 &) override;
	void f左();
	void f右();
	void f切换项(int &(*变化)(int &));
	std::vector<std::wstring> ma文本;
	W按钮 w左, w右;
	W显示框 w中;
	int m选择项 = 0;
};
//==============================================================================
// 超复杂控件-表格
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
		float m列宽 = c列宽;
		float m字号 = c字号;
		E对齐 m对齐 = c对齐;
		float m计算列宽 = -1;	//按比例计算得到的宽度
	};
	struct S行属性 {
		float m行高 = c行高;
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
		std::wstring &fg列(int);
		int fg行号() const;
		C行流 f流();
		bool f焦点转移(bool 前进, bool 强切换);	//当该行是焦点时把焦点转移到其它行
		std::unique_ptr<W标签[]> ma标签;
		W表格 *mp表格;
		int m行号 = 0;
	};
	class C行流 {
	public:
		C行流(W行 &);
		C行流 &operator <<(const std::wstring_view &);
		C行流 &operator >>(std::wstring &);
		W行 *m行 = nullptr;
		int i = 0;
	};
	W表格(int = -1, int = 0);
	void f初始化_列数(int);	//必需
	void f初始化_行数(int);	//可选
	void f事件_按键(W窗口 &, const S按键参数 &) override;
	void f事件_窗口值变化(W窗口 &, const int &, int &) override;
	void f事件_焦点变化(W窗口&) override;
	void f响应_初始化() override;
	void f响应_计算() override;
	void f响应_更新() override;
	void f响应_显示(const S显示参数 &) const override;
	void f响应_垂直平移(const S平移参数 &) override;
	S列属性 &f属性_g列属性(int 索引);
	S行属性 f属性_g行属性();
	int f属性_g列数() const;	//列数
	int f属性_g行上限() const;	//行上限
	int f属性_g行数() const;	//当前行数
	void f属性_s标题行(bool);	//把首行当做标题行
	bool f属性_i标题行() const;
	bool f属性_i滚动条() const;
	W行 &f新行();
	void f删除行(int = -1);
	void f删除行(W行&);
	W行 &fg行(int 索引);
	void f重置滚动条布局();
	void f重置滚动条值();
	int m列数 = 0;
	int m行上限 = c无限行;
	std::vector<std::unique_ptr<W行>> ma行, ma删除行;
	std::vector<S列属性> ma列属性;
	S行属性 m行属性;
	W垂直滚动条 w垂直滚动条;
	W行 *m焦点行 = nullptr;
	t矩形 m焦点动画矩形;
	int m焦点行号 = -1;
	int m行值 = 0;
	bool m重置行号 = true;
};
//==============================================================================
// 超复杂控件-选项卡组
//==============================================================================
class W选项卡组 : public W窗口 {
public:
	static constexpr float c页按钮宽 = 50;
	static constexpr float c页按钮高 = 20;
	static constexpr float c文本大小 = 16;
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
		W窗口 *m窗口;
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
	void f属性_s文本大小(float);
	void f重置页按钮布局();
	void f隐藏页(int 序号);
	void f显示页(int 序号);
	std::vector<S页> ma页;
	int m页序号 = 0;
	float m文本大小 = c文本大小;
	t向量2 m页按钮尺寸{c页按钮宽, c页按钮高};
};
}	//namespace 用户界面