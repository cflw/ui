module;
#include "头.h"
#include "用户界面.h"
#include <用户界面_布局.h>
export module 窗口_表格;
import 用户界面.控件.表格;
export class W窗口3 : public 用户界面::W窗口框架 {
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
	用户界面::W表格 w表格{e表格, 0};
	用户界面::W标签 w标签0, w标签1;
	用户界面::W按钮 w加行{e加行}, w减行{e减行};
};
module : private;
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
	w表格.f属性_s标题行(true);

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
			if (auto vp行 = dynamic_cast<用户界面::W表格::W行 *>(&a窗口)) {
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
	f动作_添加窗口(w表格, true);
	f动作_添加窗口(w标签0, true);
	f动作_添加窗口(w标签1, true);
	f动作_添加窗口(w加行, true);
	f动作_添加窗口(w减行, true);
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