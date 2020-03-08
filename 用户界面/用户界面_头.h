﻿#pragma once
#include <array>
#include <functional>
#include <vector>
#include <stack>
#include <bitset>
#include <string>
#include <cflw辅助.h>
#include <cflw时间.h>
#include <cflw数学.h>
#include <cflw数学_向量.h>
#include <cflw数学_图形.h>
#include <cflw数学_平面几何.h>
#include <cflw工具.h>
#include <cflw输入.h>
namespace 用户界面 {
//声明
namespace 时间 = cflw::时间;
namespace 输入 = cflw::输入;
namespace 数学 = cflw::数学;
namespace 工具 = cflw::工具;
//using 二维::C文本格式计算;
//using 二维::C中文字号表;
using cflw::时间::C时间间隔;
using t标志 = std::bitset<32>;
using cflw::输入::S按键;
using t向量2 = cflw::数学::S向量2;
using t颜色 = cflw::数学::S颜色;
using t矩形 = cflw::数学::S矩形;
class C用户界面;
class W窗口;
struct S主题;
class C切换动画;
struct S布局参数;
//
constexpr float c切换时间 = 0.5f;	//多少秒切换完毕
constexpr float c切换速度 = 1 / c切换时间;

}