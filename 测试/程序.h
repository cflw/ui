#pragma once
#include <memory>
#include <Windows.h>
#include <用户界面.h>
class C程序 {
public:
	static void f初始化(HINSTANCE);
	static void f运行();
	static void f销毁();
	static 用户界面::W窗口 &fg窗口(int);
private:
	class C实现;
	static std::unique_ptr<C实现> m实现;
};