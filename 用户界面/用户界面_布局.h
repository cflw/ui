#pragma once
#include "�û�����_ͷ.h"
namespace �û����� {
class C�����ƶ����� {
public:
	void f����_s����(const t����2 &����, const t����2 &��С);
	void f����_s�ƶ�(const t����2 &);
	void f����_s�����ƶ�(float, float);
	t����2 f����_g��������() const;
	t����2 f����_g���γߴ�() const;
	t����2 f����_g����������() const;
	t����2 f����_g�����γߴ�() const;
	void f����_�ƶ�();
	t����2 f����_�����ƶ�(float, float) const;
	S���ֲ��� f���ɾ���(float x = 0, float y = 0) const;
	S���ֲ��� f����������(float x = 0, float y = 0) const;
	S���ֲ��� f�ƶ����ɾ���();
	S���ֲ��� f�ƶ�����������();
	t����2 m����{};
	t����2 m��С{};
	t����2 m�ƶ�{};
};
class C���񲼾� {
public:
	enum E�ߴ����� {
		e����,
		e�ٷֱ�,
		e����
	};
	struct S������ {
		E�ߴ����� m���� = e����;
		float mֵ = 1;
	};
	struct S�߳� {
		float m��ʼ;
		float m��С;
	};
	void f����_s����(const t����2 &��������, const t����2 &��С);
	void f����_s����(size_t, size_t);
	S������ &f����_g��(size_t);
	S������ &f����_g��(size_t);
	void f����_���㲼��();
	static std::vector<S�߳�> f����_���㲼��0(const std::vector<S������> &����, float ����, float �ߴ�, float ���� = 1);
	static float f����_����ߴ�(const std::vector<S�߳�> &, size_t, size_t);
	S���ֲ��� f����(size_t ��, size_t ��, size_t ���� = 1, size_t ���� = 1);
	std::vector<S������> ma��, ma��;
	std::vector<S�߳�> ma������, ma������;
	t����2 m��������, m�ߴ�;
	bool mi���� = false;
};
}