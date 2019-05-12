#include "用户界面接口实现_音频x.h"
namespace 用户界面::接口实现 {
void C音频x::f初始化(音频x::C音频 &a音频, 音频x::C播放控制 &a控制) {
	m音频 = &a音频;
	a音频.f创建混合(m混合);
	m播放控制 = &a控制;
}
void C音频x::f添加声音(E声音 a枚举, const std::wstring_view &a文件名) {
	音频x::tp声音 v声音;
	m音频->f创建声音(v声音, a文件名);
	ma载入.push_back(v声音);
	f添加声音(a枚举, v声音);
}
void C音频x::f添加声音(E声音 a枚举, const 音频x::tp声音 &a指针) {
	ma声音.emplace(a枚举, a指针.get());
}
void C音频x::f播放音效(const S声音参数 &a) {
	m播放控制->f播放(*ma声音.at(a.m声音), *m混合);
}
}	//namespace 用户界面::接口实现