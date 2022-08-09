module;
#include "头.h"
#include "用户界面.h"
#include <用户界面_布局.h>
#include "程序.h"
export module 窗口_按钮;
//4x4按钮
export class W窗口1 : public 用户界面::W窗口框架 {
public:
	W窗口1();
	void f响应_初始化() override;
	void f事件_按键(用户界面::W窗口 &, const 用户界面::S按键参数 &) override;
	std::vector<std::unique_ptr<用户界面::W按钮>> ma按钮;
};
module : private;
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
		vp按钮->f动作_显示();
	}
	f动作_显示();
	fs按键切换(用户界面::E按键切换::e坐标);
}
void W窗口1::f事件_按键(用户界面::W窗口 &a窗口, const 用户界面::S按键参数 &a参数) {
	用户界面::C用户界面 &v用户界面 = fg引擎();
	switch (a参数.m按键) {
	case 用户界面::E按键::e确定:
		switch (a窗口.fg组合标识值()) {
		case 用户界面::f组合标识值(3, 3):
			v用户界面.f切换窗口(C程序::fg窗口(0));
			break;
		}
	}
}