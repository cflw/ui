#include "�û�����_����.h"
#include "�û�����_����.h"
namespace �û����� {
//==============================================================================
// �����ƶ�����
//==============================================================================
void C�����ƶ�����::f����_s����(const t����2 &a����, const t����2 &a��С) {
	m���� = a����;
	m��С = a��С;
}
void C�����ƶ�����::f����_s�ƶ�(const t����2 &a�ƶ�) {
	m�ƶ� = a�ƶ�;
}
void C�����ƶ�����::f����_s�����ƶ�(float x, float y) {
	m�ƶ�.x = x * m��С.x;
	m�ƶ�.y = y * m��С.y;
}
t����2 C�����ƶ�����::f����_g��������() const {
	return m����;
}
t����2 C�����ƶ�����::f����_g���γߴ�() const {
	return m��С;
}
t����2 C�����ƶ�����::f����_g����������() const {
	const float vx = m����.x - m��С.x + m��С.y;
	return t����2{vx, m����.y};
}
t����2 C�����ƶ�����::f����_g�����γߴ�() const {
	return t����2{m��С.y, m��С.y};
}
void C�����ƶ�����::f����_�ƶ�() {
	m���� += m�ƶ�;
}
t����2 C�����ƶ�����::f����_�����ƶ�(float x, float y) const {
	return {m�ƶ�.x * x, m�ƶ�.y * y};
}
S���ֲ��� C�����ƶ�����::f���ɾ���(float x, float y) const {
	S���ֲ��� v;
	v.m���� = f����_g��������() + f����_�����ƶ�(x, y);
	v.m�ߴ� = f����_g���γߴ�();
	return v;
}
S���ֲ��� C�����ƶ�����::f����������(float x, float y) const {
	S���ֲ��� v;
	v.m���� = f����_g����������() + f����_�����ƶ�(x, y);
	v.m�ߴ� = f����_g�����γߴ�();
	return v;
}
S���ֲ��� C�����ƶ�����::f�ƶ����ɾ���() {
	const S���ֲ��� v = f���ɾ���();
	f����_�ƶ�();
	return v;
}
S���ֲ��� C�����ƶ�����::f�ƶ�����������() {
	const S���ֲ��� v = f����������();
	f����_�ƶ�();
	return v;
}
//==============================================================================
// ���񲼾�
//==============================================================================
void C���񲼾�::f����_s����(const t����2 &a����, const t����2 &a�ߴ�) {
	m�������� = a���� + t����2{-a�ߴ�.x / 2, a�ߴ�.y / 2};
	m�ߴ� = a�ߴ�;
	mi���� = false;
}
void C���񲼾�::f����_s����(size_t a��, size_t a��) {
	ma��.resize(a��);
	ma��.resize(a��);
	mi���� = false;
}
C���񲼾�::S������ &C���񲼾�::f����_g��(size_t a��) {
	mi���� = false;
	return ma��[a��];
}
C���񲼾�::S������ &C���񲼾�::f����_g��(size_t a��) {
	mi���� = false;
	return ma��[a��];
}
void C���񲼾�::f����_���㲼��() {
	if (mi����) {
		return;
	}
	ma������ = f����_���㲼��0(ma��, m��������.x, m�ߴ�.x, 1);
	ma������ = f����_���㲼��0(ma��, m��������.y, m�ߴ�.y, -1);
	//����
	mi���� = true;
}
std::vector<C���񲼾�::S�߳�> C���񲼾�::f����_���㲼��0(const std::vector<S������> &aa����, float a����, float a�ߴ�, float a����) {
	float v�ܰٷֱ� = 0;
	float v�ܱ��� = 0;
	float v������ = 0;
	//ͳ��
	for (const S������ &v���� : aa����) {
		switch (v����.m����) {
		case e����:
			v������ += v����.mֵ;
			break;
		case e�ٷֱ�:
			v�ܰٷֱ� += v����.mֵ;
			break;
		case e����:
			v�ܱ��� += v����.mֵ;
			break;
		}
	}
	const float vʣ��ߴ� = a�ߴ� - v������ - (a�ߴ� * v�ܰٷֱ�);	//������ʹ��
	const float vÿ�ݳߴ� = vʣ��ߴ� / v�ܱ���;
	//����
	std::vector<S�߳�> va�߳�;
	va�߳�.reserve(aa����.size());
	float v��ʼλ�� = a����;
	for (const S������ &v���� : aa����) {
		float v�ߴ� = 0;
		switch (v����.m����) {
		case e����:
			v�ߴ� = v����.mֵ;
			break;
		case e�ٷֱ�:
			v�ߴ� = a�ߴ� * v����.mֵ;
			break;
		case e����:
			v�ߴ� = vÿ�ݳߴ� * v����.mֵ;
			break;
		}
		va�߳�.push_back({v��ʼλ��, v�ߴ�});
		v��ʼλ�� += v�ߴ� * a����;
	}
	return va�߳�;
}
float C���񲼾�::f����_����ߴ�(const std::vector<S�߳�> &a����, size_t a����, size_t a��) {
	if (a�� == 1) {
		return a����[a����].m��С;
	} else {
		float v�� = 0;
		for (size_t i = 0; i != a��; ++i) {
			v�� += a����[a���� + i].m��С;
		}
		return v��;
	}
}
S���ֲ��� C���񲼾�::f����(size_t a��, size_t a��, size_t a����, size_t a����) {
	f����_���㲼��();
	const float v�п�ʼ = ma������[a��].m��ʼ;
	const float v�п�ʼ = ma������[a��].m��ʼ;
	const float v�д�С = f����_����ߴ�(ma������, a��, a����);
	const float v�д�С = f����_����ߴ�(ma������, a��, a����);
	S���ֲ��� v;
	v.m����.x = v�п�ʼ + v�д�С / 2;
	v.m����.y = v�п�ʼ - v�д�С / 2;
	v.m�ߴ�.x = v�д�С;
	v.m�ߴ�.y = v�д�С;
	return v;
}
}