#pragma once
#include "用户界面_头.h"
namespace 用户界面 {
//==============================================================================
// 单向移动
//==============================================================================
class C单向移动布局 {
public:
	void f属性_s单格布局(const t向量2 &坐标, const t向量2 &尺寸);
	void f属性_s移动(const t向量2 &);
	void f属性_s倍数移动(float, float);
	void f属性_s网格布局(const t向量2 &坐标, const t向量2 &尺寸, int 列数 = 1, int 行数 = 1, const t向量2 &间距 = t向量2::c零);	//计算出单元格的坐标,尺寸,移动
	t向量2 f生成_g矩形中心() const;
	t向量2 f生成_g矩形尺寸() const;
	t向量2 f生成_g正方形中心() const;
	t向量2 f生成_g正方形尺寸() const;
	void f生成_移动();
	t向量2 f生成_计算移动(float, float) const;
	S布局参数 f计算生成矩形(float x倍数 = 0, float y倍数 = 0) const;
	S布局参数 f计算生成正方形(float x倍数 = 0, float y倍数 = 0) const;
	S布局参数 f移动生成矩形();
	S布局参数 f移动生成正方形();
	t向量2 m坐标{};
	t向量2 m尺寸{};
	t向量2 m移动{};
};
//==============================================================================
// 网格
//==============================================================================
class C网格布局 {
public:
	enum E尺寸类型 {
		e像素,
		e百分比,
		e倍数
	};
	struct S边属性 {
		E尺寸类型 m类型 = e倍数;
		float m值 = 1;
	};
	struct S边长 {
		float m开始;
		float m大小;
	};
	void f属性_s中心布局(const t向量2 &中心坐标, const t向量2 &大小);
	void f属性_s行列(size_t, size_t);
	S边属性 &f属性_g行(size_t);
	S边属性 &f属性_g列(size_t);
	void f生成_计算布局();
	static std::vector<S边长> f生成_计算布局0(const std::vector<S边属性> &数组, float 坐标, float 尺寸, float 符号 = 1);
	static float f生成_计算尺寸(const std::vector<S边长> &, size_t, size_t);
	S布局参数 f计算生成(size_t 行, size_t 列, size_t 行数 = 1, size_t 列数 = 1) const;	//调用前需要调用一次f生成_计算布局
	std::vector<S边属性> ma行, ma列;
	std::vector<S边长> ma计算行, ma计算列;
	t向量2 m左上坐标, m尺寸;
	bool mi计算 = false;
};
//==============================================================================
// 表格排格
//==============================================================================
class C表格排列布局;
class C表格排行布局 {
public:
	void f属性_s行布局(const t向量2 &坐标, const t向量2 &父尺寸, float 子高度);
	void f属性_s行距(float);
	S布局参数 f移动生成(float y偏移 = 0);
	C表格排列布局 fc移动生成排列布局(float y偏移 = 0);
	t向量2 m坐标{};
	t向量2 m父尺寸{};
	float m子高度 = 0;
	float m上 = 0;
	float m行距 = 0;
};
class C表格排列布局 {
public:
	void f属性_s列布局(const t向量2 &坐标, const t向量2 &父尺寸);
	S布局参数 f移动生成(float x移动 = 0);
	t向量2 m坐标{};
	t向量2 m父尺寸{};
	float m左 = 0;
};
}	//namespace 用户界面