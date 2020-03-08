#include "用户界面_控件.h"
#include "用户界面_接口.h"
namespace 用户界面 {
W图片::W图片(int n, int v) : W窗口(n, v) {
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
}