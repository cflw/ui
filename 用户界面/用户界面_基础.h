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
	float mĿ�� = 0;
	float mʵ�� = 0;	//-1��0����,0��1��ʧ
	void f����(float ��ʱ = 0);
	void f����(bool ����, float ���);
	bool fi����ʧ() const;
	bool fi������() const;
	bool fi��ʧ��() const;
	float fg͸����() const;
};
class C�������� {
public:
	typedef std::function<t����2(const W���� &)> tf����;
	tf���� mf���� = nullptr;
	tf���� mf�ߴ� = nullptr;
	void fĬ��();
	//����
	static t����2 f����_��(const W���� &);
	static t����2 f����_���ҵ���(const W���� &);
	static t����2 f����_����(const W���� &);
	static t����2 f����_����(const W���� &);
	//��Χ
	static t����2 f�ߴ�_��(const W���� &);
	static t����2 f�ߴ�_����(const W���� &);
};
struct S�����ֵ {
	static constexpr float c�ٶ� = 5;
	float mֵ = 0;
	operator float() const;
	float f����(bool);	//ֻ���ڸ����е���
	float f��ֵ(float, float) const;
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
	t����2 m���� = t����2::c��;
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
		e����,
		e����,	//������Ϊ����
		e��갴��,	//����ڴ��ڷ�Χ�ڰ���,����Ӧ�д���
		e��������,
		eѡ��,	//��ѡ��/��ѡ���ѡ��
		e���,	//ֻ����Ӧ�������Ĵ���
		e��귶Χ,	//����ڴ��ڵķ�Χ��
		e��ʾ,
		e��ʾ����,
		e��ʾ�߿�,
		e����,	//�����յ�һЩ��Ӧ��������Ӵ��ڣ�Ĭ��Ϊtrue
		e�Զ���
	};
	//����/����
	W����();
	W����(int ��ʶ, int ֵ);
	~W����();
	//����
	void f����_ʹ��();
	void f����_����();
	bool f����_iʹ��();
	//�¼�,���Ӵ��ڸ������ڷ���Ϣ
	virtual void f�¼�_����(W����&, const S�������� &);
	virtual void f�¼�_�������(W����&);	//����ڴ�����ʱ
	virtual void f�¼�_����ֵ�仯(W����&, const int &�仯ǰ, int &�仯��);
	virtual void f�¼�_�����ƶ�(W����&, const t����2 &);
	//��Ӧ,���û���������ڷ���Ϣ
	virtual void f��Ӧ_��ʼ��();
	virtual void f��Ӧ_����();
	virtual void f��Ӧ_����();
	virtual void f��Ӧ_����();
	virtual void f��Ӧ_��ʾ(const S��ʾ���� &) const;
	virtual void f��Ӧ_����(const S�������� &);	//���̺��ֱ��İ���
	virtual bool f��Ӧ_i��Χ��(const t����2 &);	//�����ʹ�����������м���,ȷ���Ƿ��ڷ�Χ��
	virtual void f��Ӧ_��갴��(const S�������� &);	//�ڷ�Χ�ڰ��´���,�������Ҳ�������
	virtual void f��Ӧ_����ɿ�(const S�������� &);	//�ڷ�Χ���ⵥ�����ᴥ��,ǰ�����ȵ��ð���,�������Ҳ�������
	virtual void f��Ӧ_�ַ�(const std::vector<wchar_t> &);
	virtual void f��Ӧ_�����(const S��������� &);	//������������������ڴ���
	//����,�ɸ����ڸ��Ӵ��ڷ���Ϣ
	void f����_��Ӵ���(W����&);	//��ĳ�Ա�Ӵ���
	void f����_�ر�();	//���Ҫ�л�����,�ȹرմ������½�����
	void f����_����(bool = true);
	void f����_��ʾ(float ��ʱ = 0);
	void f����_����();
	void f����_��ý���();
	//��������
	C�û����� &fg����() const;
	std::vector<W����*> fg�Ӵ���();
	virtual void f����_s����(const t����2 &���� = {}, const t����2 &�ߴ� = {});
	void f����_s����(const S���ֲ��� &);
	t����2 f����_g����() const;
	t����2 fg��������(const t����2 &ƫ�� = t����2::c��) const;
	t����2 fg�����ߴ�(const t����2 &ƫ�� = t����2::c��) const;
	t���� fg��������(const t����2 &����ƫ�� = t����2::c��, const t����2 &��Χƫ�� = t����2::c��) const;
	void fs�����л�(E�����л�);
	//t��ɫ fg������ɫ(float, float, float);
	bool fi����();	//�����Ƿ��ý���
	bool fi�();	//����������ǻ�ģ��Ӵ���Ҳ�ǻ�ġ�
	bool fi�����();
	bool fi����();
	bool fi�ɻ�ð�������() const;
	void f��־_sĬ��();
	bool f��־_g�̳�(size_t) const;
	bool f��־_g�̳�_������(size_t) const;
	void f��־_s�̳���ʾ();
	bool f��־_i��ʾ() const;
	bool f��־_i��ʾ�߿�() const;
	bool f��־_i��ʾ����() const;
public:	//������Ҫ����"C�û�����"����
	W���� *m������ = nullptr;
	int m��� = -1;	//�ڴ��ڱ�����
	int m���ڲ� = 0;
	std::vector<W����*> ma�Ӵ���;
	W���� *m���㴰��;	//ָ�Ӵ���
	E���� m��갴�� = E����::e��;
	I�����л� *m�����л� = nullptr;
public:	//�ɱ�
	t����2 m���� = t����2::c��;
	t����2 m�ߴ� = t����2(8, 8);
	C�л����� m�л�;
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