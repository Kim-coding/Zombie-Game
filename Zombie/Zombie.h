#pragma once
#include "SpriteGo.h"
#include "Player.h"

class Zombie : public SpriteGo
{
public:
	enum class Types   //���� ����
	{
		Bloater,
		Chase,
		Crawler,
	};
	static const int TotalTypes = 3;   //���� ��?
	static Zombie* Create(Types ZombieType);

protected:
	Types type;
	
	//����
	int maxHp;
	float speed;

	//���� ����
	int hp;
	
	Player* player;                     //���� �÷��̾ ������ �� �ֵ���

	sf::Vector2f direction;  //���� ����
	sf::Vector2f look;       //ȸ�� ����


	Zombie(const std::string& name = "");

public:
	~Zombie() override = default;

	void Init()override;
	void Release()override;
	void Reset()override;
	void Update(float dt)override;
	void Draw(sf::RenderWindow& window)override;


};

