#pragma once
#include <cflw图形_d2d.h>
#include <cflw图形_dx纹理.h>
#include "用户界面_接口.h"
namespace 用户界面::接口实现::d2d {
namespace 二维 = cflw::图形::d2d;
namespace 纹理 = cflw::图形::dx纹理;
using cflw::图形::d2d::E文本水平对齐;
using cflw::图形::d2d::E文本垂直对齐;
using cflw::图形::d2d::C中文字号格式;
using tp图片源 = std::unique_ptr<I图片源>;
//==============================================================================
// 画界面
//==============================================================================
class C图片源;
class C图形 : public I图形设备 {
public:
	friend C图片源;
	void f初始化(二维::C二维 &);
	std::unique_ptr<I图片源> f创建图片(const std::wstring_view &) const;
	void f绘制圆形(const t矩形 &, const t颜色 &) const override;
	void f绘制矩形(const t矩形 &, const t颜色 &) const override;
	void f绘制文本(const std::wstring_view &, const t矩形 &, const t颜色 &, const S文本格式 &) const override;
	void f填充矩形(const t矩形 &, const t颜色 &) const override;
	void f填充圆形(const t矩形 &, const t颜色 &) const override;
	static E文本水平对齐 ft水平对齐(E对齐);
	static E文本垂直对齐 ft垂直对齐(E对齐);
private:
	IDWriteTextFormat *fg格式(const S文本格式 &) const;
	二维::S文本格式参数 f文本格式参数(const S文本格式 &) const;
	二维::C二维 *m二维 = nullptr;
	std::shared_ptr<二维::C画图形> m画图形;
	std::shared_ptr<二维::C画图形> m画图片;
	std::shared_ptr<二维::C画文本> m画文本;
	二维::C文本工厂 m文本工厂;
	纹理::C图像工厂 m图像工厂;
};
}