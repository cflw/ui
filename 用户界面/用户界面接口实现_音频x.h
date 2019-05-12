#pragma once
#include <map>
#include <vector>
#include <cflw音频_xa2.h>
#include "用户界面_接口.h"
namespace 用户界面::接口实现 {
namespace 音频x = cflw::音频::xa2;
class C音频x : public I音频设备 {
public:
	void f初始化(音频x::C音频 &, 音频x::C播放控制 &);
	void f添加声音(E声音, const std::wstring_view &文件名);	//从文件载入
	void f添加声音(E声音, const 音频x::tp声音 &);	//外部声音
	void f播放音效(const S声音参数 &) override;
	音频x::C音频 *m音频 = nullptr;
	音频x::C播放控制 *m播放控制;
	std::map<E声音, const 音频x::t声音*> ma声音;
	std::vector<音频x::tp声音> ma载入;
	音频x::tp混合 m混合;
};
}	//namespace 用户界面::接口实现