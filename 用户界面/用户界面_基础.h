#pragma once
#include "�û�����_ͷ.h"
namespace �û����� {
class C�û�����;
class C�����ƶ�����;
class I������;
class I�����豸;
class I�����л�;
//==============================================================================
// ö��/����
//==============================================================================
enum E���� {
	e����,
	e����,
	e����,
	e����,
	e����,
};
enum class E������Դ {
	e����,
	e���,
	e�ֱ�,
	e����,
	e��,	//�ڲ�����
};
enum class E���� {
	e��,
	e��,
	e��,
	e��,
	eȷ��,
	eȡ��,
	e�л�,
	e����,
	e��,
};
enum class E�����л� {
	e���,
	e����,
};
enum class Eʱ��� {
	eһ��,
	e��ʼ,
	e������,
	e����,
};
//==============================================================================
// ������/�ṹ
//==============================================================================
struct S�ı���ʽ {
	float m�ֺ� = 10;
	E���� mˮƽ���� = E����::e����;
	bool operator ==(const S�ı���ʽ &a) const {
		return m�ֺ� == a.m�ֺ� && mˮƽ���� == a.mˮƽ����;
	}
};
struct S���� {
	static const S���� c��;
	S����(const t��ɫ &, const t��ɫ &);
	t��ɫ mǰ��ɫ;
	t��ɫ m����ɫ;
	t��ɫ fg��ɫ(float ��ֵ, float ����, float ͸����) const;
};
class C�л����� {
public:
	void f����(float ��ʱ = 0);
	void f����(bool ����, float ���);
	bool fi����ʧ() const;
	bool fi������() const;
	bool fi��ʧ��() const;
	float fgĿ��() const;
	float fgʵ��() const;
	float fg͸����() const;
	float mĿ�� = 0;
	float mʵ�� = -1;	//-1��0����,0��1��ʧ
};
class C���л� {
public:
	void f����(W����&);
	float fgĿ��() const;
	float fgʵ��() const;
	float fg͸����() const;
	float m��СĿ��, m���Ŀ��, m��Сʵ��, m���ʵ��;
};
class C�������� {
public:
	typedef std::function<t����2(const W���� &)> tf����;
	void fĬ��();
	//����
	static t����2 f����_��(const W���� &);
	static t����2 f����_���ҵ���(const W���� &);
	static t����2 f����_����(const W���� &);
	static t����2 f����_����(const W���� &);
	//��Χ
	static t����2 f�ߴ�_��(const W���� &);
	static t����2 f�ߴ�_����(const W���� &);
public:
	tf���� mf���� = nullptr;
	tf���� mf�ߴ� = nullptr;
};
struct S�����ֵ {
	static constexpr float c�ٶ� = 5;
	float mֵ = 0;
	operator float() const;
	float f����(bool);	//ֻ���ڸ����е���
	float f��ֵ(float, float) const;
};
class Cƽ�Ƽ��� {
public:
	static constexpr float cֹͣ���ٶ� = -100;
	Cƽ�Ƽ���(W���� &);
	bool fi��Դ(E������Դ) const;
	void f����(E������Դ, const t����2 &);
	void f�϶�����(const t����2 &);
	void f���ּ���(const t����2 &);
	void fֹͣ����();
	void f������Ӧ();
	W���� *m����;
	E������Դ m��Դ;
	Eʱ��� mʱ���;
	t����2 m��ʼλ��;
	t����2 m��ǰλ��;
	t����2 m�ٶ�;
	t����2 mƽ���ٶ�;
};
//==============================================================================
// �¼�/��Ӧ ����
//==============================================================================
struct S��ʾ���� {
	I������ &m������;
	S���� &m����;
};
struct S��������� {
	int x = 0;
	int y = 0;
	bool fi��() const;
	bool fi��() const;
	bool fi��() const;
	bool fi��() const;
	bool fi����() const;
	bool fi����() const;
};
struct S���ֲ��� {
	t����2 m����;
	t����2 m�ߴ�;
};
struct S�������� {
	E������Դ m��Դ;
	E���� m����;
	Eʱ��� mʱ���;
	t����2 m���� = t����2::c��;
};
struct Sƽ�Ʋ��� {
	E������Դ m��Դ;
	Eʱ��� mʱ���;
	float m��ʼλ��;
	float m��ǰλ��;
	float m�ٶ�;
};
//==============================================================================
// ����
//==============================================================================
class W���� {
public:
	friend C�û�����;
	enum E��־ {
		eʹ��,
		e����,	//���������,ˢ�´��ڱ�ʱɾ�����ٵĴ���
		e����,
		e����,	//����ָʾ
		e����,	//������Ϊ�κν���,Ĭ��Ϊ��
		e��갴��,	//����ڴ��ڷ�Χ�ڰ���,����Ӧ�д���
		e��������,
		eѡ��,	//��ѡ��/��ѡ���ѡ��
		//e�����,	//ֻ�ܻ����꽹��,��Ӧ������
		e��귶Χ,	//����ڴ��ڵķ�Χ��
		e��ʾ,	//���Ϊ��,���Ѻ��Ӵ��ڶ�����ʾ
		e��ʾ����,
		e��ʾ�߿�,
		e����,	//Ӱ�촰�ڵ�һЩ������Ϊ. ������Ӵ���,Ĭ��Ϊ��
		e��ʧ,	//��ʧ����,��ʧ֮���ǲ���ʾ
		e�ɻ����꽹��,
		e�ɻ�ð�������,
		e�ɻ��ƽ�ƽ���,
		//eˮƽƽ��,	//��ͨ���϶����ƶ�
		//e��ֱƽ��,
		e�Զ���
	};
	//����/����
	W����();
	W����(int ��ʶ, int ֵ);
	~W����();
	//����
	void f����_ʹ��();
	void f����_����();
	bool f����_iʹ��() const;
	//�¼�,���Ӵ��ڸ������ڷ���Ϣ
	virtual void f�¼�_����(W����&, const S�������� &);
	virtual void f�¼�_�������(W����&);	//����ڴ�����ʱ
	virtual void f�¼�_����ֵ�仯(W����&, const int &�仯ǰ, int &�仯��);
	virtual void f�¼�_�����ƶ�(W����&, const t����2 &);
	virtual void f�¼�_����仯(W����&);
	//��Ӧ,���û���������ڷ���Ϣ
	virtual void f��Ӧ_��ʼ��();
	virtual void f��Ӧ_����();
	virtual void f��Ӧ_����();
	virtual void f��Ӧ_����();
	virtual void f��Ӧ_��ʾ(const S��ʾ���� &) const;
	virtual void f��Ӧ_����(const S�������� &);	//���̺��ֱ��İ���
	virtual bool f��Ӧ_i��Χ��(const t����2 &);	//�����ʹ�����������м���,ȷ���Ƿ��ڷ�Χ��
	virtual void f��Ӧ_��갴��(const S�������� &);	//����꽹�㷶Χ�ڰ��´���,�������Ҳ�������
	virtual void f��Ӧ_����ɿ�(const S�������� &);	//����꽹�㷶Χ���ⵥ�����ᴥ��,ǰ�����ȵ��ð���,�������Ҳ�������
	virtual void f��Ӧ_�ַ�(const std::vector<wchar_t> &);
	virtual void f��Ӧ_�����(const S��������� &);	//������������������ڴ���
	virtual void f��Ӧ_����仯();	//��ý����ʧȥ����ʱ����,�ں����ڵ��� f״̬_i���� �Լ�������Ƿ��н���,�л�����ʱ����Ӧʧȥ����Ĵ�������Ӧ��ý���Ĵ���
	virtual void f��Ӧ_ˮƽƽ��(const Sƽ�Ʋ��� &);
	virtual void f��Ӧ_��ֱƽ��(const Sƽ�Ʋ��� &);
	//�����ڵ��õļ���&����
	void f����_�л�();
	void f����_��ʾ();
	void f����_ƽ��();
	void f����_�л�();
	//����,�ɸ����ڸ��Ӵ��ڷ���Ϣ
	void f����_��Ӵ���(W����&);	//��ĳ�Ա�Ӵ���
	void f����_�ر�();	//���Ҫ�л�����,�ȹرմ������½�����
	void f����_����(bool = true);
	void f����_����(bool = true);	//���õķ�����
	void f����_��ʾ(float ��ʱ = 0);
	void f����_����(bool ��ʧ���� = true);
	void f����_��ý���();
	void f����_���������();
	//��������
	static C�û����� &fg����();
	std::vector<W����*> fg�Ӵ���();
	virtual void f����_s����(const t����2 &���� = {}, const t����2 &�ߴ� = {});
	void f����_s����(float ��, float ��, float ��, float ��);
	void f����_s����(const S���ֲ��� &);
	t����2 f����_g����() const;
	t����2 fg��������(const t����2 &ƫ�� = t����2::c��) const;
	t����2 fg�����ߴ�(const t����2 &ƫ�� = t����2::c��) const;
	t���� fg��������(const t����2 &����ƫ�� = t����2::c��, const t����2 &��Χƫ�� = t����2::c��) const;
	const C���л� &fg���л�() const;	//��ϸ�����,������ܵ��л�
	void fs�����л�(E�����л�);
	Cƽ�Ƽ��� &fgƽ�Ƽ���();
	//t��ɫ fg������ɫ(float, float, float);
	//��������Ƶı�־״̬
	bool f״̬_i����() const;	//�����Ƿ��ý���
	bool f״̬_i������() const;	//�а�������û����꽹��
	bool f״̬_i�() const;	//����������ǻ�ģ��Ӵ���Ҳ�ǻ�ġ�
	bool f״̬_i�����() const;
	bool f״̬_i����() const;
	bool f״̬_iƽ�ƽ���() const;
	//��־ȡ��
	bool f��־_i����() const;
	bool f��־_i�ɻ�ð�������() const;
	void f��־_sĬ��();
	bool f��־_g�̳�(size_t) const;
	bool f��־_g�̳�_������(size_t) const;
	void f��־_s�̳���ʾ();
	bool f��־_i��ʾ() const;
	bool f��־_i��ʾ�߿�() const;
	bool f��־_i��ʾ����() const;
	bool f��־_i�ɻ��ƽ�ƽ���() const;
	void f��־_sƽ��(bool = true);
	bool f��־_i�����() const;
	void f��־_s�����();
public:	//������Ҫ���� C�û����� ����
	W���� *m������ = nullptr;
	int m��� = -1;	//�ڴ��ڱ�����
	int m���ڲ� = 0;
	std::vector<W����*> ma�Ӵ���;
	W���� *m���㴰�� = nullptr;	//ָ�Ӵ���
	E���� m��갴�� = E����::e��;
	I�����л� *m�����л� = nullptr;
	Cƽ�Ƽ��� *mƽ�Ƽ��� = nullptr;
public:	//�ɱ�
	t����2 m���� = t����2::c��;
	t����2 m�ߴ� = t����2(8, 8);
	C�л����� m�л�;
	C���л� m���л�;
	C�������� m����;
	S�����ֵ m���㽥��;
	int m��ʶ;
	int mֵ;
	t��־ m��־;
	t��־ m�̳б�־;
};
}	//namespace �û�����
//=============================================================================
namespace std {
template<> struct hash<�û�����::S�ı���ʽ> {
	size_t operator()(const �û�����::S�ı���ʽ &) const;
};
}