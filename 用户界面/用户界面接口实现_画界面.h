#pragma once
#include <cflwͼ��_d2d.h>
#include "�û�����_�ӿ�.h"
namespace �û�����::�ӿ�ʵ�� {
namespace ��ά = cflw::ͼ��::d2d;
using cflw::ͼ��::d2d::E�ı�ˮƽ����;
using cflw::ͼ��::d2d::E�ı���ֱ����;
using cflw::ͼ��::d2d::C�����ֺŸ�ʽ;
//==============================================================================
// ������
//==============================================================================
class C������ : public I������ {
public:
	void f��ʼ��(��ά::C��ά &);
	void f����Բ��(const t���� &, const t��ɫ &) override;
	void f���ƾ���(const t���� &, const t��ɫ &) override;
	void f�����ı�(const std::wstring &, const t���� &, const t��ɫ &, const S�ı���ʽ &) override;
	void f������(const t���� &, const t��ɫ &) override;
	void f���Բ��(const t���� &, const t��ɫ &) override;
	static E�ı�ˮƽ���� ftˮƽ����(E����);
	static E�ı���ֱ���� ft��ֱ����(E����);
private:
	IDWriteTextFormat *fg��ʽ(const S�ı���ʽ &);
	��ά::S�ı���ʽ���� f�ı���ʽ����(const S�ı���ʽ &);
	std::shared_ptr<��ά::C��ͼ��> m��ͼ��;
	std::shared_ptr<��ά::C���ı�> m���ı�;
	��ά::C�ı����� m�ı�����;
};
}