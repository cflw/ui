#include "用户界面接口实现_图形d2d.h"
namespace 用户界面::接口实现::d2d {
//==============================================================================
// 图片源
//==============================================================================
class C图片源 : public I图片源 {
public:
	C图片源(const 二维::tp位图 &a位图, const 二维::tp画笔 &a画笔): 
		m位图(a位图), m画笔(a画笔) {
	}
	void f显示(const W窗口 &a窗口, const S显示参数 &a参数) const override {
		二维::C画图形 &v画图片 = *static_cast<C图形 &>(a参数.m图形).m画图片;
		v画图片.fs画笔(m画笔);
		v画图片.f填充矩形(数学::S矩形::fc坐标尺寸(a窗口.m坐标, a窗口.m尺寸));
	}
	二维::tp位图 m位图;
	二维::tp画笔 m画笔;
};
//==============================================================================
// 图形设备
//==============================================================================
void C图形::f初始化(二维::C二维 &a) {
	m二维 = &a;
	m画图形 = a.fc画图形();
	m画图片 = a.fc画图形();
	m画文本 = a.fc画文本();
	m文本工厂.f初始化();
	m图像工厂.f初始化();
}
std::unique_ptr<I图片源> C图形::f创建图片(const std::wstring_view &a路径) const {
	auto v纹理 = m图像工厂.f高级读取(a路径, 纹理::格式::F强制转换(纹理::格式::c通用pbgra));
	auto v位图 = m二维->fc位图(v纹理);
	auto v画笔 = m二维->fc位图画笔(v位图);
	auto v源 = std::make_unique<C图片源>(v位图, v画笔);
	return v源;
}
void C图形::f绘制圆形(const t矩形 &a矩形, const t颜色 &a颜色) const {
	m画图形->fs颜色(a颜色);
	m画图形->f绘制椭圆({a矩形.m坐标, a矩形.m半尺寸});
}
void C图形::f绘制矩形(const t矩形 &a矩形, const t颜色 &a颜色) const {
	m画图形->fs颜色(a颜色);
	m画图形->f绘制矩形({a矩形.m坐标, a矩形.m半尺寸});
}
void C图形::f绘制文本(const std::wstring_view &a文本, const t矩形 &a矩形, const t颜色 &a颜色, const S文本格式 &a格式) const {
	m画文本->fs格式(fg格式(a格式));
	m画文本->fs颜色(a颜色);
	m画文本->fs区域(a矩形);
	m画文本->f绘制文本(a文本);
}
void C图形::f填充矩形(const t矩形 &a矩形, const t颜色 &a颜色) const {
	m画图形->fs颜色(a颜色);
	m画图形->f填充矩形({a矩形.m坐标, a矩形.m半尺寸});
}
void C图形::f填充圆形(const t矩形 &a矩形, const t颜色 &a颜色) const {
	m画图形->fs颜色(a颜色);
	m画图形->f填充椭圆({a矩形.m坐标, a矩形.m半尺寸});
}
IDWriteTextFormat *C图形::fg格式(const S文本格式 &a) const {
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
二维::S文本格式参数 C图形::f文本格式参数(const S文本格式 &a) const {
	二维::S文本格式参数 v参数;
	v参数.fs字号(a.m字号);
	v参数.fs水平对齐(ft水平对齐(a.m水平对齐));
	return v参数;
}
E文本水平对齐 C图形::ft水平对齐(E对齐 a) {
	static const std::unordered_map<E对齐, E文本水平对齐> ca表 = {
		{E对齐::e居左, E文本水平对齐::e左},
		{E对齐::e居右, E文本水平对齐::e右},
		{E对齐::e居中, E文本水平对齐::e中},
		{E对齐::e居上, E文本水平对齐::e中},
		{E对齐::e居下, E文本水平对齐::e中},
	};
	return ca表.at(a);
}
E文本垂直对齐 C图形::ft垂直对齐(E对齐 a) {
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

