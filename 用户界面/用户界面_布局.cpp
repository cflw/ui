#include "用户界面_布局.h"
#include "用户界面_基础.h"
namespace 用户界面 {
//==============================================================================
// 单向移动布局
//==============================================================================
void C单向移动布局::f属性_s布局(const t向量2 &a坐标, const t向量2 &a大小) {
	m坐标 = a坐标;
	m大小 = a大小;
}
void C单向移动布局::f属性_s移动(const t向量2 &a移动) {
	m移动 = a移动;
}
void C单向移动布局::f属性_s倍数移动(float x, float y) {
	m移动.x = x * m大小.x;
	m移动.y = y * m大小.y;
}
t向量2 C单向移动布局::f生成_g矩形中心() const {
	return m坐标;
}
t向量2 C单向移动布局::f生成_g矩形尺寸() const {
	return m大小;
}
t向量2 C单向移动布局::f生成_g正方形中心() const {
	const float vx = m坐标.x - m大小.x + m大小.y;
	return t向量2{vx, m坐标.y};
}
t向量2 C单向移动布局::f生成_g正方形尺寸() const {
	return t向量2{m大小.y, m大小.y};
}
void C单向移动布局::f生成_移动() {
	m坐标 += m移动;
}
t向量2 C单向移动布局::f生成_计算移动(float x, float y) const {
	return {m移动.x * x, m移动.y * y};
}
S布局参数 C单向移动布局::f生成矩形(float x, float y) const {
	S布局参数 v;
	v.m坐标 = f生成_g矩形中心() + f生成_计算移动(x, y);
	v.m尺寸 = f生成_g矩形尺寸();
	return v;
}
S布局参数 C单向移动布局::f生成正方形(float x, float y) const {
	S布局参数 v;
	v.m坐标 = f生成_g正方形中心() + f生成_计算移动(x, y);
	v.m尺寸 = f生成_g正方形尺寸();
	return v;
}
S布局参数 C单向移动布局::f移动生成矩形() {
	const S布局参数 v = f生成矩形();
	f生成_移动();
	return v;
}
S布局参数 C单向移动布局::f移动生成正方形() {
	const S布局参数 v = f生成正方形();
	f生成_移动();
	return v;
}
//==============================================================================
// 网格布局
//==============================================================================
void C网格布局::f属性_s布局(const t向量2 &a坐标, const t向量2 &a尺寸) {
	m左上坐标 = a坐标 + t向量2{-a尺寸.x / 2, a尺寸.y / 2};
	m尺寸 = a尺寸;
	mi计算 = false;
}
void C网格布局::f属性_s行列(size_t a行, size_t a列) {
	ma行.resize(a行);
	ma列.resize(a列);
	mi计算 = false;
}
C网格布局::S边属性 &C网格布局::f属性_g行(size_t a行) {
	mi计算 = false;
	return ma行[a行];
}
C网格布局::S边属性 &C网格布局::f属性_g列(size_t a列) {
	mi计算 = false;
	return ma列[a列];
}
void C网格布局::f生成_计算布局() {
	if (mi计算) {
		return;
	}
	ma计算列 = f生成_计算布局0(ma列, m左上坐标.x, m尺寸.x, 1);
	ma计算行 = f生成_计算布局0(ma行, m左上坐标.y, m尺寸.y, -1);
	//结束
	mi计算 = true;
}
std::vector<C网格布局::S边长> C网格布局::f生成_计算布局0(const std::vector<S边属性> &aa属性, float a坐标, float a尺寸, float a符号) {
	float v总百分比 = 0;
	float v总倍数 = 0;
	float v总像素 = 0;
	//统计
	for (const S边属性 &v属性 : aa属性) {
		switch (v属性.m类型) {
		case e像素:
			v总像素 += v属性.m值;
			break;
		case e百分比:
			v总百分比 += v属性.m值;
			break;
		case e倍数:
			v总倍数 += v属性.m值;
			break;
		}
	}
	const float v剩余尺寸 = a尺寸 - v总像素 - (a尺寸 * v总百分比);	//给倍数使用
	const float v每份尺寸 = v剩余尺寸 / v总倍数;
	//分配
	std::vector<S边长> va边长;
	va边长.reserve(aa属性.size());
	float v开始位置 = a坐标;
	for (const S边属性 &v属性 : aa属性) {
		float v尺寸 = 0;
		switch (v属性.m类型) {
		case e像素:
			v尺寸 = v属性.m值;
			break;
		case e百分比:
			v尺寸 = a尺寸 * v属性.m值;
			break;
		case e倍数:
			v尺寸 = v每份尺寸 * v属性.m值;
			break;
		}
		va边长.push_back({v开始位置, v尺寸});
		v开始位置 += v尺寸 * a符号;
	}
	return va边长;
}
float C网格布局::f生成_计算尺寸(const std::vector<S边长> &a数组, size_t a索引, size_t a跨) {
	if (a跨 == 1) {
		return a数组[a索引].m大小;
	} else {
		float v和 = 0;
		for (size_t i = 0; i != a跨; ++i) {
			v和 += a数组[a索引 + i].m大小;
		}
		return v和;
	}
}
S布局参数 C网格布局::f生成(size_t a行, size_t a列, size_t a行数, size_t a列数) {
	f生成_计算布局();
	const float v行开始 = ma计算行[a行].m开始;
	const float v列开始 = ma计算列[a列].m开始;
	const float v行大小 = f生成_计算尺寸(ma计算行, a行, a行数);
	const float v列大小 = f生成_计算尺寸(ma计算列, a列, a列数);
	S布局参数 v;
	v.m坐标.x = v列开始 + v列大小 / 2;
	v.m坐标.y = v行开始 - v行大小 / 2;
	v.m尺寸.x = v列大小;
	v.m尺寸.y = v行大小;
	return v;
}
}