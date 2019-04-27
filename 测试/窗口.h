#pragma once
#include "头.h"
#include "用户界面.h"
class W主窗口 : public 用户界面::W窗口 {
public:
	enum E控件编号 {
		e文字 = -1,
		e按钮0,
		e按钮1,
		e按钮2,
		e下拉列表,
		e滑动块,
		e连击按钮,
		e滚动条,
		e文本框,
	};
	W主窗口() = default;
	void f响应_初始化() override;
	void f事件_按键(W窗口 &, const 用户界面::S按键参数 &) override;
	void f事件_窗口值变化(W窗口 &, const int &变化前, int &变化后) override;
	用户界面::W标签 w文字{e文字};
	用户界面::W按钮 w按钮0{e按钮0};
	用户界面::W按钮 w按钮1{e按钮1};
	用户界面::W按钮 w按钮2{e按钮2};
	用户界面::W下拉列表 w下拉列表{e下拉列表};
	用户界面::W滑动块2 w滑动块{e滑动块};
	用户界面::W连击按钮 w连击按钮{e连击按钮};
	用户界面::W垂直滚动条 w滚动条{e滚动条};
	用户界面::W文本框 w文本框{e文本框};
};
//4x4按钮
class W窗口1 : public 用户界面::W窗口 {
public:
	W窗口1();
	void f响应_初始化() override;
	std::vector<std::unique_ptr<用户界面::W按钮>> ma按钮;
};
//一排复选框
class W窗口2 : public 用户界面::W窗口 {
public:
	enum E标识 {
		e标签,
		e按钮,
		e复选框,
	};
	W窗口2();
	void f响应_初始化() override;
	void f事件_按键(W窗口 &, const 用户界面::S按键参数 &) override;
	用户界面::W标签 w文字{e标签};
	用户界面::W按钮 w按钮{e按钮};
	std::vector<用户界面::W复选框> ma复选框;
};
//数据表
class W窗口3 : public 用户界面::W窗口 {
public:
	enum E标识 {
		e表格,
		e加行,
		e减行,
	};
	W窗口3();
	void f事件_按键(W窗口 &, const 用户界面::S按键参数 &) override;
	void f事件_窗口值变化(W窗口 &, const int &, int &) override;
	void f响应_初始化() override;
	void f加行();
	void f减行();
	用户界面::W表格 w表格{e表格};
	用户界面::W标签 w标签0, w标签1;
	用户界面::W按钮 w加行{e加行}, w减行{e减行};
};
//选项卡
class W窗口4 : public 用户界面::W窗口 {
public:
	W窗口4();
	void f响应_初始化() override;
	用户界面::W选项卡组 w选项卡组;
	std::vector<用户界面::W标签> ma标签;
};