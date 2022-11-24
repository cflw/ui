#pragma once
#include "用户界面_基础.h"
namespace 用户界面 {
//==============================================================================
// 图形接口
//==============================================================================
class I图片源 {
public:
	virtual void f显示(const W窗口 &, const S显示参数 &) const = 0;
};
class I图形设备 {
public:
	//画
	virtual void f绘制圆形(const t矩形 &, const t颜色 &) const = 0;
	virtual void f绘制矩形(const t矩形 &, const t颜色 &) const = 0;
	virtual void f绘制文本(const std::wstring_view &, const t矩形 &, const t颜色 &, const S文本样式 &) const = 0;
	virtual void f填充矩形(const t矩形 &, const t颜色 &) const = 0;
	virtual void f填充圆形(const t矩形 &, const t颜色 &) const = 0;
};
//==============================================================================
// 输入接口
//==============================================================================
class I输入设备 {
public:
	virtual S按键 f按键(E按键) const = 0;
	virtual t向量2 f坐标() const {
		return t向量2::c零;
	}
};
//==============================================================================
// 音频接口
//==============================================================================
enum class E声音 {
	e方向键切换按键焦点,
};
struct S声音参数 {
	E声音 m声音;
};
class I音频设备 {
public:
	virtual void f播放音效(const S声音参数 &) const = 0;
};
}	//namespace 用户界面