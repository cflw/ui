module;
#include "头.h"
#include "用户界面.h"
#include <用户界面_布局.h>
export module 窗口_选项卡;
export import 用户界面.控件.横向选择列表;
export import 用户界面.控件.选项卡;
export class W选项卡页 : public 用户界面::W窗口框架 {
public:
	W选项卡页();
	void f响应_初始化() override;
	void f属性_s布局(const 用户界面::S布局参数 &) override;
	std::vector<用户界面::W横向选择列表> ma控件;
};
export class W窗口4 : public 用户界面::W窗口框架 {
public:
	W窗口4();
	void f响应_初始化() override;
	用户界面::W选项卡组 w选项卡组;
	std::vector<W选项卡页> ma页;
};
module : private;
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
