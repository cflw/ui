#pragma once
#include "用户界面_引擎.h"
namespace 用户界面 {
//切换接口
class I按键切换 {
public:
	I按键切换(C用户界面 &, W窗口 &);
	virtual void f更新() = 0;	//窗口表发生变动时调用
	virtual W窗口 *f上下切换(bool a前进) = 0;
	virtual W窗口 *f左右切换(bool a前进) = 0;
	C用户界面 *m引擎 = nullptr;	//取信息用
	W窗口 *m窗口 = nullptr;
};
//按序号切换
class C按键切换_序号 : public I按键切换 {
public:
	using I按键切换::I按键切换;
	void f更新() override;
	W窗口 *f上下切换(bool a前进) override;
	W窗口 *f左右切换(bool a前进) override;
	W窗口 *f切换(bool a前进);
	std::vector<W窗口*> ma窗口;
};
//按坐标切换
class C按键切换_坐标 : public I按键切换 {
public:
	using I按键切换::I按键切换;
	void f更新() override;
	W窗口 *f上下切换(bool a前进) override;
	W窗口 *f左右切换(bool a前进) override;
	W窗口 *f切换(const float t向量2::*主顺序, const float t向量2::*次顺序, const std::function<bool(const float &, const float &)> &主比较);
	std::vector<W窗口*> ma窗口;
};
}