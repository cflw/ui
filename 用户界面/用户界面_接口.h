#pragma once
#include "�û�����_����.h"
namespace �û����� {
class I������ {
public:
	virtual void f����Բ��(const t���� &, const t��ɫ &) = 0;
	virtual void f���ƾ���(const t���� &, const t��ɫ &) = 0;
	virtual void f�����ı�(const std::wstring &, const t���� &, const t��ɫ &, const S�ı���ʽ &) = 0;
	virtual void f������(const t���� &, const t��ɫ &) = 0;
	virtual void f���Բ��(const t���� &, const t��ɫ &) = 0;
};
class I�����豸 {
public:
	virtual S���� f����(E����) const = 0;
	virtual t����2 f����() const {
		return t����2::c��;
	}
};
}