#pragma once
#include "�û�����_����.h"
namespace �û����� {
//�л��ӿ�
class I�����л� {
public:
	I�����л�(C�û����� &, W���� &);
	virtual void f����() = 0;	//���ڱ����䶯ʱ����
	virtual W���� *f�����л�(bool aǰ��) = 0;
	virtual W���� *f�����л�(bool aǰ��) = 0;
	C�û����� *m���� = nullptr;	//ȡ��Ϣ��
	W���� *m���� = nullptr;
};
//������л�
class C�����л�_��� : public I�����л� {
public:
	using I�����л�::I�����л�;
	void f����() override;
	W���� *f�����л�(bool aǰ��) override;
	W���� *f�����л�(bool aǰ��) override;
	W���� *f�л�(bool aǰ��);
	std::vector<W����*> ma����;
};
//�������л�
class C�����л�_���� : public I�����л� {
public:
	using I�����л�::I�����л�;
	void f����() override;
	W���� *f�����л�(bool aǰ��) override;
	W���� *f�����л�(bool aǰ��) override;
	W���� *f�л�(const float t����2::*��˳��, const float t����2::*��˳��, const std::function<bool(const float &, const float &)> &���Ƚ�);
	std::vector<W����*> ma����;
};
}