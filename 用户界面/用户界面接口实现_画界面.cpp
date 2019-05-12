#include "用户界面接口实现_画界面.h"
namespace 用户界面::接口实现 {
//=============================================================================
// 画界面
//=============================================================================
void C画界面::f初始化(二维::C二维 &a) {
	m画图形 = a.fc画图形();
	m画文本 = a.fc画文本();
	m文本工厂.f初始化();
}
void C画界面::f绘制圆形(const t矩形 &a矩形, const t颜色 &a颜色) {
	m画图形->fs颜色(a颜色);
	m画图形->f绘制椭圆({a矩形.m坐标, a矩形.m半尺寸});
}
void C画界面::f绘制矩形(const t矩形 &a矩形, const t颜色 &a颜色) {
	m画图形->fs颜色(a颜色);
	m画图形->f绘制矩形({a矩形.m坐标, a矩形.m半尺寸});
}
void C画界面::f绘制文本(const std::wstring_view &a文本, const t矩形 &a矩形, const t颜色 &a颜色, const S文本格式 &a格式) {
	m画文本->fs格式(fg格式(a格式));
	m画文本->fs颜色(a颜色);
	m画文本->fs区域(a矩形);
	m画文本->f绘制文本(a文本);
}
void C画界面::f填充矩形(const t矩形 &a矩形, const t颜色 &a颜色) {
	m画图形->fs颜色(a颜色);
	m画图形->f填充矩形({a矩形.m坐标, a矩形.m半尺寸});
}
void C画界面::f填充圆形(const t矩形 &a矩形, const t颜色 &a颜色) {
	m画图形->fs颜色(a颜色);
	m画图形->f填充椭圆({a矩形.m坐标, a矩形.m半尺寸});
}
IDWriteTextFormat *C画界面::fg格式(const S文本格式 &a) {
	static std::unordered_map<S文本格式, 二维::tp文本格式> va文本格式;
	if (va文本格式.find(a) == va文本格式.end()) {
		二维::tp文本格式 v格式;
		v格式 = m文本工厂.fc文本格式(f文本格式参数(a));
		va文本格式.emplace(a, v格式);
		return v格式.Get();
	} else {
		return va文本格式.at(a).Get();
	}
}
二维::S文本格式参数 C画界面::f文本格式参数(const S文本格式 &a) {
	二维::S文本格式参数 v参数;
	v参数.fs字号(a.m字号);
	v参数.fs水平对齐(ft水平对齐(a.m水平对齐));
	return v参数;
}
E文本水平对齐 C画界面::ft水平对齐(E对齐 a) {
	static const std::unordered_map<E对齐, E文本水平对齐> ca表 = {
		{E对齐::e居左, E文本水平对齐::e左},
		{E对齐::e居右, E文本水平对齐::e右},
		{E对齐::e居中, E文本水平对齐::e中},
		{E对齐::e居上, E文本水平对齐::e中},
		{E对齐::e居下, E文本水平对齐::e中},
	};
	return ca表.at(a);
}
E文本垂直对齐 C画界面::ft垂直对齐(E对齐 a) {
	static const std::unordered_map<E对齐, E文本垂直对齐> ca表 = {
		{E对齐::e居左, E文本垂直对齐::e上},
		{E对齐::e居右, E文本垂直对齐::e下},
		{E对齐::e居中, E文本垂直对齐::e中},
		{E对齐::e居上, E文本垂直对齐::e上},
		{E对齐::e居下, E文本垂直对齐::e下},
	};
	return ca表.at(a);
}

}

