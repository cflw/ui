#pragma once
#include <cflw����_xi.h>
#include "�û�����_�ӿ�.h"
namespace �û�����::�ӿ�ʵ�� {
namespace ����x = cflw::����::xi;
class C�ֱ�x : public I�����豸 {
public:
	void f��ʼ��(����x::I�ֱ� &);
	void f����();
	����::S���� f����(E����) const override;
	����x::I�ֱ� *m�ֱ� = nullptr;
	����x::C����ӳ�� mӳ��;
};
}