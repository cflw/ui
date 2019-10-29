#pragma once
#include <cflw输入_win.h>
#include "用户界面_接口.h"
namespace 用户界面::接口实现 {
namespace 输入w = cflw::输入::win;
class C键盘w : public I输入设备 {
public:
	void f初始化(输入w::I键盘 &);
	void f更新();
	输入::S按键 f按键(E按键) const override;
	输入w::I键盘 *m键盘 = nullptr;
	输入w::C按键映射 m映射;
};
class C鼠标w : public I输入设备 {
public:
	void f初始化(输入w::I鼠标 &);
	void f更新();
	输入::S按键 f按键(E按键) const override;
	t向量2 f坐标() const override;
	输入w::I鼠标 *m鼠标 = nullptr;
	输入w::C按键映射 m映射;
};
class C触摸w : public I输入设备 {
public:
	void f初始化(输入w::I触摸 &);
	void f更新();
	输入::S按键 f按键(E按键) const override;
	t向量2 f坐标() const override;
	输入w::I触摸 *m触摸 = nullptr;
	输入w::tp触控点 m点 = nullptr;
	t向量2 m坐标;
};
}