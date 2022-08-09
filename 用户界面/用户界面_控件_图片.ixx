module;
#include "用户界面_控件.h"
#include "用户界面_布局.h"
#include "用户界面_引擎.h"
export module 用户界面.控件.图片;
export namespace 用户界面 {
//图片
class I图片源;
class W图片 : public W窗口 {
public:
	W图片(int = -1, int = 0);
	void f响应_显示(const S显示参数 &) const override;
	void f属性_s图片源(const I图片源 &);
	void f属性_s透明度(float);
	float m透明度 = 1;
	const I图片源 *m图片源 = nullptr;
};
}	//namespace 用户界面
module : private;
namespace 用户界面 {
//定义
W图片::W图片(int n, int v): W窗口(n, v) {
}
void W图片::f响应_显示(const S显示参数 &a参数) const {
	m图片源->f显示(*this, a参数);
}
void W图片::f属性_s图片源(const I图片源 &a源) {
	m图片源 = &a源;
}
void W图片::f属性_s透明度(float a透明度) {
	m透明度 = a透明度;
}
}	//namespace 用户界面