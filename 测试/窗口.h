#pragma once
#include "ͷ.h"
#include "�û�����.h"
class W������ : public �û�����::W���� {
public:
	enum E�ؼ���� {
		e���� = -1,
		e��ť0,
		e��ť1,
		e��ť2,
		e�����б�,
		e������,
		e������ť,
		e������,
		e�ı���,
	};
	W������() = default;
	void f��Ӧ_��ʼ��() override;
	void f�¼�_����(W���� &, const �û�����::S�������� &) override;
	void f�¼�_����ֵ�仯(W���� &, const int &�仯ǰ, int &�仯��) override;
	�û�����::W��ǩ w����{e����};
	�û�����::W��ť w��ť0{e��ť0};
	�û�����::W��ť w��ť1{e��ť1};
	�û�����::W��ť w��ť2{e��ť2};
	�û�����::W�����б� w�����б�{e�����б�};
	�û�����::W������2 w������{e������};
	�û�����::W������ť w������ť{e������ť};
	�û�����::W��ֱ������ w������{e������};
	�û�����::W�ı��� w�ı���{e�ı���};
};
//4x4��ť
class W����1 : public �û�����::W���� {
public:
	W����1();
	void f��Ӧ_��ʼ��() override;
	std::vector<std::unique_ptr<�û�����::W��ť>> ma��ť;
};
//һ�Ÿ�ѡ��
class W����2 : public �û�����::W���� {
public:
	enum E��ʶ {
		e��ǩ,
		e��ť,
		e��ѡ��,
	};
	W����2();
	void f��Ӧ_��ʼ��() override;
	void f�¼�_����(W���� &, const �û�����::S�������� &) override;
	�û�����::W��ǩ w����{e��ǩ};
	�û�����::W��ť w��ť{e��ť};
	std::vector<�û�����::W��ѡ��> ma��ѡ��;
};
//���ݱ�
class W����3 : public �û�����::W���� {
public:
	enum E��ʶ {
		e���,
		e����,
		e����,
	};
	W����3();
	void f�¼�_����(W���� &, const �û�����::S�������� &) override;
	void f�¼�_����ֵ�仯(W���� &, const int &, int &) override;
	void f��Ӧ_��ʼ��() override;
	void f����();
	void f����();
	�û�����::W��� w���{e���};
	�û�����::W��ǩ w��ǩ0, w��ǩ1;
	�û�����::W��ť w����{e����}, w����{e����};
};
//ѡ�
class W����4 : public �û�����::W���� {
public:
	W����4();
	void f��Ӧ_��ʼ��() override;
	�û�����::Wѡ��� wѡ���;
	std::vector<�û�����::W��ǩ> ma��ǩ;
};