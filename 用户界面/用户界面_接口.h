#pragma once
#include "用户界面_基础.h"
namespace 用户界面 {
class I画界面 {
public:
	virtual void f绘制圆形(const t矩形 &, const t颜色 &) = 0;
	virtual void f绘制矩形(const t矩形 &, const t颜色 &) = 0;
	virtual void f绘制文本(const std::wstring &, const t矩形 &, const t颜色 &, const S文本格式 &) = 0;
	virtual void f填充矩形(const t矩形 &, const t颜色 &) = 0;
	virtual void f填充圆形(const t矩形 &, const t颜色 &) = 0;
};
class I输入设备 {
public:
	virtual S按键 f按键(E按键) const = 0;
	virtual t向量2 f坐标() const {
		return t向量2::c零;
	}
};
}