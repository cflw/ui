#pragma once
#include <cflw输入_xi.h>
#include "用户界面_接口.h"
namespace 用户界面::接口实现::xi {
namespace 输入x = cflw::输入::xi;
class C手柄 : public I输入设备 {
public:
	void f初始化(输入x::I手柄 &);
	void f更新();
	输入::S按键 f按键(E按键) const override;
	输入x::I手柄 *m手柄 = nullptr;
	输入x::C按键映射 m映射;
};
}