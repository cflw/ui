#include "�û�����_�����л�.h"
#include <cflw����_����.h>
#include "�û�����_����.h"
namespace �û����� {
I�����л�::I�����л�(C�û����� &a����, W���� &a����):
	m����(&a����), m����(&a����) {
}
//==============================================================================
// ������л�����
//==============================================================================
void C�����л�_���::f����() {
	//������
	typedef ����::C��<W����*> t������;
	typedef t������::C�ڵ� t�������ڵ�;
	typedef t������::tҶ t������Ҷ;
	t������ v������;
	std::function<void(t������Ҷ &, W���� *)> f������ = [&](t������Ҷ &a��, W���� *a����) {
		//���Ҷ��,���޳��մ������ٵĴ���
		m����->f�����Ӵ���(a����, [&](W���� &a) {
			a��.push_back(&a);
		});
		//����
		std::sort(a��.begin(), a��.end(),
			[](const t�������ڵ� &a0, const t�������ڵ� &a1) {
			W���� *v0 = a0.mֵ;
			W���� *v1 = a1.mֵ;
			if (v0->m��ʶ != v1->m��ʶ) {
				return v0->m��ʶ < v1->m��ʶ;
			} else {
				return v0->mֵ < v1->mֵ;
			}
		});
		//����Ҷ��
		for (auto &v�� : a��) {
			if (v��.mֵ->ma�Ӵ���.size() != 0) {
				v��.mҶ = std::make_unique<std::vector<t�������ڵ�>>();
				f������(*v��.mҶ, v��.mֵ);
			}
		}
	};
	f������(v������.mҶ, m����);
	//����
	int v��� = 0;
	ma����.clear();
	std::function<void(t������Ҷ &)> f������ = [&](t������Ҷ &a��) {
		for (auto &v�� : a��) {
			ma����.push_back(v��.mֵ);
			v��.mֵ->m��� = v���;
			++v���;
			if (v��.mҶ) {
				f������(*v��.mҶ);
			}
		}
	};
	f������(v������.mҶ);
}
W���� *C�����л�_���::f�����л�(bool aǰ��) {
	return f�л�(aǰ��);
}
W���� *C�����л�_���::f�����л�(bool aǰ��) {
	return f�л�(aǰ��);
}
W���� *C�����л�_���::f�л�(bool aǰ��) {
	if (ma����.empty()) {
		return nullptr;
	}
	using t������ = std::vector<W����*>::iterator;
	const t������ v��ʼ = ma����.begin();
	const t������ v���� = ma����.end();
	const t������ v��ǰ = std::find(v��ʼ, v����, m����->m��������);
	t������ v�¸� = v��ǰ;
	const auto f�仯0 = aǰ�� ? &����::fѭ������<t������> : &����::fѭ���Լ�<t������>;
	const auto f�仯 = std::bind(f�仯0, v��ʼ, v����, std::placeholders::_1);
	do {
		v�¸� = f�仯(v�¸�);
		W���� *v���� = *v�¸�;
		if (!v����->f��־_i�ɻ�ð�������()) {
			continue;
		}
		return v����;
	} while (v�¸� != v��ǰ);
	return nullptr;
}
//==============================================================================
// �������л�����
//==============================================================================
void C�����л�_����::f����() {
	ma����.clear();
	const std::function<void(W����&)> f��� = [&](W���� &a) {
		for (W���� *vp���� : a.ma�Ӵ���) {
			f���(*vp����);
		}
		ma����.push_back(&a);
	};
	f���(*m����);
}
W���� *C�����л�_����::f�����л�(bool aǰ��) {
	return f�л�(&t����2::y, &t����2::x, aǰ�� ? ����::fС��<float> : ����::f����<float>);
}
W���� *C�����л�_����::f�����л�(bool aǰ��) {
	return f�л�(&t����2::x, &t����2::y, aǰ�� ? ����::f����<float> : ����::fС��<float>);
}
W���� *C�����л�_����::f�л�(const float t����2::*ap��˳��, const float t����2::*ap��˳��, const std::function<bool(const float &, const float &)> &af���Ƚ�) {
	struct Sѡ�� {
		W���� *m���� = nullptr;
		float m������ = 0, m�ξ��� = 0;
	} v��, vԶ;
	const float &v��������0 = m����->m��������->m����.*ap��˳��;
	const float &v��������1 = m����->m��������->m����.*ap��˳��;
	const auto &vf�����Ƚ� = af���Ƚ�;
	const auto &vf�����Ƚ� = std::bind(����::f��, std::bind(af���Ƚ�, std::placeholders::_1, std::placeholders::_2));
	for (W���� *vp���� : ma����) {	//����ѡ��ǰ����������Ĵ���
		if (!vp����->f��־_i�ɻ�ð�������()) {
			continue;
		}
		const float &v��ǰ����0 = vp����->m����.*ap��˳��;
		if (v��������0 == v��ǰ����0) {
			continue;
		}
		const float &v��ǰ����1 = vp����->m����.*ap��˳��;
		const float v������1 = std::abs(v��������0 - v��ǰ����0);
		const float v�ξ���1 = std::abs(v��������1 - v��ǰ����1);
		const auto fѡ�� = [&](Sѡ�� &aѡ��, const std::function<bool(const float &, const float &)> &af���Ƚ�1, const std::function<bool(const float &, const float &)> &af����Ƚ�) {
			const auto f����ѡ�� = [&]() {
				aѡ��.m���� = vp����;
				aѡ��.m������ = v������1;
				aѡ��.m�ξ��� = v�ξ���1;
			};
			if (af���Ƚ�1(v��ǰ����0, v��������0)) {
				if (aѡ��.m����) {
					if (af����Ƚ�(v������1, aѡ��.m������)) {
						f����ѡ��();
					} else if (v������1 == aѡ��.m������ && v�ξ���1 < aѡ��.m�ξ���) {
						f����ѡ��();
					}
				} else {
					f����ѡ��();
				}
			}
		};
		fѡ��(v��, vf�����Ƚ�, ����::fС��<float>);
		fѡ��(vԶ, vf�����Ƚ�, ����::f����<float>);
	}
	return v��.m���� ? v��.m���� : vԶ.m����;
}
}