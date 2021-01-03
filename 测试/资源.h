#pragma once
#include <map>
#include <string>
#include <用户界面_接口.h>
class C图片资源 {
public:
	C图片资源();
	static C图片资源 *fg这();
	void f添加(const std::wstring &, std::unique_ptr<用户界面::I图片源> &&);
	const std::unique_ptr<用户界面::I图片源> &fg图片(const std::wstring &);
public:
	static C图片资源 *g这;
	std::map<std::wstring, std::unique_ptr<用户界面::I图片源>> ma图片源;
};