#pragma once
#include <cflw图形_d2d.h>
#include "用户界面_接口.h"
namespace 用户界面::接口实现 {
namespace 二维 = cflw::图形::d2d;
using cflw::图形::d2d::E文本水平对齐;
using cflw::图形::d2d::E文本垂直对齐;
using cflw::图形::d2d::C中文字号格式;
//==============================================================================
// 画界面
//==============================================================================
class C画界面 : public I画界面 {
public:
	void f初始化(二维::C二维 &);
	void f绘制圆形(const t矩形 &, const t颜色 &) override;
	void f绘制矩形(const t矩形 &, const t颜色 &) override;
	void f绘制文本(const std::wstring &, const t矩形 &, const t颜色 &, const S文本格式 &) override;
	void f填充矩形(const t矩形 &, const t颜色 &) override;
	void f填充圆形(const t矩形 &, const t颜色 &) override;
	static E文本水平对齐 ft水平对齐(E对齐);
	static E文本垂直对齐 ft垂直对齐(E对齐);
private:
	IDWriteTextFormat *fg格式(const S文本格式 &);
	二维::S文本格式参数 f文本格式参数(const S文本格式 &);
	std::shared_ptr<二维::C画图形> m画图形;
	std::shared_ptr<二维::C画文本> m画文本;
	二维::C文本工厂 m文本工厂;
};
}