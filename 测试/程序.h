#pragma once
#include <memory>
#include <Windows.h>
#include <�û�����.h>
class C���� {
public:
	static void f��ʼ��(HINSTANCE);
	static void f����();
	static void f����();
	static �û�����::W���� &fg����(int);
private:
	class Cʵ��;
	static std::unique_ptr<Cʵ��> mʵ��;
};