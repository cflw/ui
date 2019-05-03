﻿#include "头.h"
#include "窗口.h"
#include "程序.h"
#include "用户界面_布局.h"
//==============================================================================
// 主窗口
//==============================================================================
void W主窗口::f响应_初始化() {
	用户界面::C单向移动布局 v单向布局;
	v单向布局.f属性_s单格布局(t向量2{-100, 200}, t向量2{100, 24});
	v单向布局.f属性_s倍数移动(0, -1);
	用户界面::C网格布局 v网格布局;
	v网格布局.f属性_s中心布局(t向量2(-100, 100), t向量2(200, 200));
	v网格布局.f属性_s行列(4, 2);
	constexpr float c按钮字号 = 18;
	//各种控件
	w文字.f属性_s布局({});
	w文字.f属性_s文本内容(L"aaaaaaaaaaa");
	w文字.f动作_显示();
	f动作_添加窗口(w文字);
	w按钮0.f属性_s布局(v网格布局.f计算生成(0, 0));
	w按钮0.f属性_s文本(L"按钮0", c按钮字号);
	w按钮0.f动作_获得焦点();
	w按钮0.f动作_显示();
	f动作_添加窗口(w按钮0);
	w按钮1.f属性_s布局(v网格布局.f计算生成(0, 1));
	w按钮1.f属性_s文本(L"按钮1", c按钮字号);
	w按钮1.f动作_显示();
	f动作_添加窗口(w按钮1);
	w按钮2.f属性_s文本内容(L"空");
	w按钮2.f属性_s布局(v网格布局.f计算生成(1, 0));
	w按钮2.f动作_显示();
	f动作_添加窗口(w按钮2);
	w下拉列表.f属性_s布局(v网格布局.f计算生成(1, 1));
	w下拉列表.f属性_s列表({L"123", L"321"});
	w下拉列表.m标志[W窗口::e显示背景] = false;
	w下拉列表.m标志[W窗口::e显示边框] = false;
	w下拉列表.f动作_显示();
	f动作_添加窗口(w下拉列表);
	w滑动块.f属性_s布局({{0, -150}, {40, 40}});
	w滑动块.f动作_显示();
	f动作_添加窗口(w滑动块);
	w连击按钮.f属性_s布局(v网格布局.f计算生成(2, 0));
	w连击按钮.f属性_s连击间隔(0.1f);
	w连击按钮.f动作_显示();
	f动作_添加窗口(w连击按钮);
	w滚动条.f属性_s布局({{200, 0}, {0, 400}});
	w滚动条.f属性_s滚动值(100, 10);
	w滚动条.f动作_显示();
	f动作_添加窗口(w滚动条);
	w文本框.f属性_s布局({{100, 100}, {200, 0}});
	w文本框.f动作_显示();
	f动作_添加窗口(w文本框);
	f动作_显示();
	//fs按键切换(用户界面::E按键切换::e坐标);
}
void W主窗口::f事件_按键(W窗口 &a窗口, const 用户界面::S按键参数 &a按键) {
	用户界面::C用户界面 *v用户界面 = 用户界面::C用户界面::g这;
	switch (a按键.m按键) {
	case 用户界面::E按键::e确定: 
		switch (a窗口.m标识) {
		case e按钮0:
			w文字.f属性_s文本(L"123aaaaaaaa", 26);
			break;
		case e按钮1:
			w文字.f属性_s文本(L"aaaaaaaaaaa", 10);
			break;
		case e按钮2:
			v用户界面->f切换窗口(C程序::fg窗口(1));
			//v用户界面->f新建窗口(*C程序::m窗口2);
			//v用户界面->f设置活动窗口(*C程序::m窗口2);
			break;
		case e连击按钮:
			w文字.f属性_s文本内容(std::to_wstring(w连击按钮.m次数));
			break;
		}
		break;
	}
}
void W主窗口::f事件_窗口值变化(W窗口 &a, const int &a前, int &a后) {
	switch (a.m标识) {
	case e滚动条:
		w文字.f属性_s文本内容(std::to_wstring(a后));
		break;
	}
}
//==============================================================================
// 窗口1
//==============================================================================
W窗口1::W窗口1() {
	constexpr size_t c边数 = 4;
	用户界面::C网格布局 v布局;
	v布局.f属性_s中心布局({0, 0}, {300, 300});
	v布局.f属性_s行列(c边数, c边数);
	v布局.f生成_计算布局();
	for (size_t i = 0; i != c边数; ++i) {
		for (size_t j = 0; j != c边数; ++j) {
			std::unique_ptr<用户界面::W按钮> v按钮 = std::make_unique<用户界面::W按钮>((int)i, (int)j);
			v按钮->f属性_s布局(v布局.f计算生成(i, j));
			v按钮->f属性_s文本内容(std::to_wstring(i) + std::to_wstring(j));
			ma按钮.push_back(std::move(v按钮));
		}
	}
}
void W窗口1::f响应_初始化() {
	for (const auto &vp按钮 : ma按钮) {
		f动作_添加窗口(*vp按钮);
	}
	f动作_显示();
	fs按键切换(用户界面::E按键切换::e坐标);
}
//==============================================================================
// 窗口2
//==============================================================================
W窗口2::W窗口2() {
	用户界面::C单向移动布局 v布局;
	v布局.f属性_s单格布局(t向量2(-100, 100), t向量2(20, 20));
	v布局.f属性_s倍数移动(1, 0);
	for (int i = 0; i != 10; ++i) {
		用户界面::W复选框 &v复选框 = ma复选框.emplace_back(e复选框, i);
		v复选框.f属性_s布局(v布局.f移动生成矩形());
	}
}
void W窗口2::f响应_初始化() {
	w文字.f属性_s文本内容(L"窗口2");
	f动作_添加窗口(w文字);
	w按钮.f属性_s布局({t向量2(0, -100), t向量2(50, 20)});
	w按钮.f属性_s文本内容(L"按钮");
	f动作_添加窗口(w按钮);
	for (auto &v复选框 : ma复选框) {
		f动作_添加窗口(v复选框);
	}
	f动作_显示();
}
void W窗口2::f事件_按键(W窗口 &a窗口, const 用户界面::S按键参数 &a按键) {
	用户界面::C用户界面 *v用户界面 = 用户界面::C用户界面::g这;
	switch (a按键.m按键) {
	case 用户界面::E按键::e确定:
		switch (a窗口.m标识) {
		case e复选框: {
			用户界面::W复选框 &v复选框 = (用户界面::W复选框&)a窗口;
			const int v值 = 1 << v复选框.m值;
			if (v复选框.f属性_i选中()) {
				m值 |= v值;
			} else {
				m值 &= ~v值;
			}
			w文字.f属性_s文本内容(std::to_wstring(m值));
			break;
		}
		case e按钮:
			v用户界面->f切换窗口(C程序::fg窗口(0));
			break;
		}
		break;
	case 用户界面::E按键::e取消:
		switch (a窗口.m标识) {
		case e按钮:
			v用户界面->f切换窗口(C程序::fg窗口(0));
			break;
		default:
			w按钮.f动作_获得焦点();
			break;
		}
		break;
	}
}
//==============================================================================
// 窗口3
//==============================================================================
W窗口3::W窗口3() {
	constexpr int c列数 = 4;
	constexpr int c行数 = 10;
	w表格.f初始化_列数(c列数);
	w表格.f属性_s布局({{0, 0}, {600, 300}});
	for (int i = 0; i != c行数; ++i) {
		f加行();
	}
	w表格.f属性_s标题行(false);

	用户界面::C单向移动布局 v标签布局;
	v标签布局.f属性_s单格布局({-300, -200}, {40, 20});
	v标签布局.f属性_s倍数移动(1, 0);
	w标签0.f属性_s布局(v标签布局.f移动生成矩形());
	w标签1.f属性_s布局(v标签布局.f移动生成矩形());
	w加行.f属性_s布局(v标签布局.f移动生成矩形());
	w加行.f属性_s文本内容(L"加行");
	w减行.f属性_s布局(v标签布局.f移动生成矩形());
	w减行.f属性_s文本内容(L"减行");
}
void W窗口3::f事件_按键(W窗口 &a窗口, const 用户界面::S按键参数 &a参数) {
	switch (a参数.m按键) {
	case 用户界面::E按键::e确定:
		switch (a窗口.m标识) {
		case e表格:
			if (auto vp行 = dynamic_cast<用户界面::W表格::W行*>(&a窗口)) {
				w表格.f删除行(vp行->fg行号());
			}
			w标签1.f属性_s文本内容(std::to_wstring(a窗口.m值));
			break;
		case e加行:
			f加行();
			break;
		case e减行:
			f减行();
			break;
		}
	}
}
void W窗口3::f事件_窗口值变化(W窗口 &a窗口, const int &a前, int &a后) {
	w标签0.f属性_s文本内容(std::to_wstring(a后));
}
void W窗口3::f响应_初始化() {
	f动作_添加窗口(w表格);
	f动作_添加窗口(w标签0);
	f动作_添加窗口(w标签1);
	f动作_添加窗口(w加行);
	f动作_添加窗口(w减行);
	f动作_显示();
}
void W窗口3::f加行() {
	auto &v行 = w表格.f新行();
	const std::wstring v文本 = std::to_wstring(v行.m值);
	v行.f流() << v文本 << v文本 << v文本 << v文本;
}
void W窗口3::f减行() {
	w表格.f删除行();
}
//==============================================================================
// 窗口4
//==============================================================================
W选项卡页::W选项卡页() {
	constexpr int c数量 = 4;
	for (int i = 0; i != c数量; ++i) {
		auto &v选择列表 = ma控件.emplace_back(i, 0);
		for (int j = 0; j != 5; ++j) {
			const std::wstring ij = std::to_wstring(i) + std::to_wstring(j);
			v选择列表.ma文本.emplace_back(ij);
		}
	}
}
void W选项卡页::f属性_s布局(const 用户界面::S布局参数 &a参数) {
	用户界面::C单向移动布局 v布局;
	v布局.f属性_s网格布局(t向量2::c零, a参数.m尺寸, 1, 10, t向量2(0, 10));
	int i = 0;
	for (用户界面::W横向选择列表 &v选择列表 : ma控件) {
		v选择列表.f属性_s布局(v布局.f计算生成矩形(0, i++));
	}
}
void W选项卡页::f响应_初始化() {
	for (用户界面::W横向选择列表 &v选择列表 : ma控件) {
		f动作_添加窗口(v选择列表);
		v选择列表.f动作_显示();
	}
}
W窗口4::W窗口4() {
	constexpr int c数量 = 4;
	const 用户界面::S布局参数 v布局{t向量2::c零, t向量2(200, 300)};
	for (int i = 0; i != c数量; ++i) {
		auto &v页 = ma页.emplace_back();
		v页.f属性_s布局(v布局);
	}
	w选项卡组.f属性_s布局(v布局);
}
void W窗口4::f响应_初始化() {
	for (用户界面::W窗口 &v窗口 : ma页) {
		w选项卡组.f动作_添加页(v窗口, L"aaa");
	}
	f动作_添加窗口(w选项卡组);
	w选项卡组.f动作_显示();
	f动作_显示();
}
