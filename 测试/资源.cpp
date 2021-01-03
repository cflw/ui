#include "资源.h"
C图片资源::C图片资源() {
	g这 = this;
}
C图片资源 *C图片资源::fg这() {
	return g这;
}
void C图片资源::f添加(const std::wstring &a名称, std::unique_ptr<用户界面::I图片源> &&a图片) {
	ma图片源.emplace(a名称, std::move(a图片));
}
const std::unique_ptr<用户界面::I图片源> &C图片资源::fg图片(const std::wstring &a名称) {
	return ma图片源.at(a名称);
}
C图片资源 *C图片资源::g这 = nullptr;