#pragma once
#include <unordered_map>
#include "�û�����_ͷ.h"
#include "�û�����_����.h"
#include "�û�����_�ӿ�.h"
namespace �û����� {
//==============================================================================
// �û�����
//==============================================================================
class C�û����� {
public:
	static C�û����� *g��;
	struct S������Ϣ {
		W���� *m����;
		W���� *m�;
	};
	struct S��������� {
		����::C��ס�ظ� m�ظ�;
		����::C����� m����, m����, m����;
	};
	static constexpr float c֡�� = 1.f / 60.f;
public:
	C�û�����();
	~C�û�����();
	void f��ʼ��();
	void fs������(I������ &);
	void fsʱ��Ƶ��(float ������, float ��Ⱦ��);	//Ӱ��ʱ��ļ���
	void fs����(const S���� &);
	void f����_s���̽ӿ�(I�����豸 &);
	void f����_s���ӿ�(I�����豸 &);
	void f����_s�ֱ��ӿ�(I�����豸 &);
	void f����_s�����ӿ�(I�����豸 &);
	void f����_�����ַ�(wchar_t);//�ڴ��ڹ���WM_CHAR��Ϣ�е���
	void f����();
	void f����();
	void f��ʾ();
	void f���ٴ���(W���� &);
	void f�½�����_(W���� &);
	void f�½�����(W���� &);
	void f�½�����(W���� &��, W���� &��);
	void fɾ������(W���� &);
	void fɾ�������Ӵ���(W���� &��);
	void f�л�����(W���� &);
	void f�������д���(const std::function<void(W����&)> &);
	void f�����Ӵ���(W���� *, const std::function<void(W����&)> &);	//�������Ϊ��,��������㴰��
	void f���ý��㴰��(W���� &);
	void f���ð������㴰��(W���� &);
	void f������꽹�㴰��(W���� &);
	void f�������������㴰��(W���� &);	//����ı���꽹��
	void f���û����(W���� &);	//Ҫ�л����ڡ������Ӵ��ڣ��������
	void f��������();
	void f���ڱ�����();	//������½��Ĵ��ں�Ҫɾ���Ĵ���
	float fg������() const;
	float fg��Ⱦ��() const;
	t����2 fgָ���������(const W���� &) const;
	bool fi��꽹�㰴��() const;
public:
	std::vector<W����*> ma���ڱ�;
	std::vector<W����*> ma�½�����;	//�½��Ĵ����ȷ���,�´μ����ٷŵ����ڱ�
	std::stack<S������Ϣ> m����ջ;
	std::vector<wchar_t> ma�ַ�;
	W���� *m������ = nullptr;
	W���� *m�������� = nullptr;
	W���� *m��꽹�� = nullptr;
	W���� *m����� = nullptr;
	float m������ = c֡��, m��Ⱦ�� = c֡��;
	S��������� m���̷��������, m�ֱ����������;
	I������ *m������ = nullptr;
	S���� m���� = S����::c��;
	I�����豸 *m���� = nullptr;
	I�����豸 *m��� = nullptr;
	I�����豸 *m�ֱ� = nullptr;
	I�����豸 *m���� = nullptr;
	t����2 m�������, m��������;
	E���� m��갴�� = E����::e��;
	bool m���ڱ�仯 = false;
	bool m�������� = false;
	int m�ܱ�� = 0;
};
}