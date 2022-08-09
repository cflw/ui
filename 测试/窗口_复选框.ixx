module;
#include "头.h"
#include "用户界面.h"
#include <用户界面_布局.h>
#include "程序.h"
export module 窗口_复选框;
//一排复选框
export class W窗口2 : public 用户界面::W窗口框架 {
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
module : private;
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
			用户界面::W复选框 &v复选框 = (用户界面::W复选框 &)a窗口;
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
