#pragma once
#include <cflw����_win.h>
#include "�û�����_�ӿ�.h"
namespace �û�����::�ӿ�ʵ�� {
namespace ����w = cflw::����::win;
class C����w : public I�����豸 {
public:
	void f��ʼ��(����w::I���� &);
	void f����();
	����::S���� f����(E����) const override;
	����w::I���� *m���� = nullptr;
	����w::C����ӳ�� mӳ��;
};
class C���w : public I�����豸 {
public:
	void f��ʼ��(����w::I��� &);
	void f����();
	����::S���� f����(E����) const override;
	t����2 f����() const override;
	����w::I��� *m��� = nullptr;
	����w::C����ӳ�� mӳ��;
};
class C����w : public I�����豸 {
public:
	void f��ʼ��(����w::I���� &);
	void f����();
	����::S���� f����(E����) const override;
	t����2 f����() const override;
	����w::I���� *m���� = nullptr;
	����w::tp���ص� m�� = nullptr;
	t����2 m����;
};
}