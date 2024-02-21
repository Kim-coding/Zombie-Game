#include "pch.h"
#include "Zombie.h"
#include "Player.h"


Zombie* Zombie::Create(Types ZombieType)
{
	Zombie* zombie = new Zombie();

	zombie->type = ZombieType;
	switch (ZombieType)
	{
	case Zombie::Types::Bloater:
		zombie->textureId = "graphics/bloater.png";
		zombie->maxHp = 40;
		zombie->speed = 100;

		break;
	case Zombie::Types::Chaser:
		zombie->textureId = "graphics/chaser.png";
		zombie->maxHp = 70;
		zombie->speed = 75;

		break;
	case Zombie::Types::Crawler:
		zombie->textureId = "graphics/crawler.png";
		zombie->maxHp = 10;
		zombie->speed = 50;

		break;
	}

	return zombie;
}

Zombie::Zombie(const std::string& name)
	:SpriteGo(name)
{
}

void Zombie::Init()
{
	SpriteGo::Init();
	SetTexture(textureId);
	SetOrigin(Origins::MC);
}

void Zombie::Release()
{
	SpriteGo::Release();

}

void Zombie::Reset()
{
	SpriteGo::Reset();
	

	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));

}

void Zombie::Update(float dt)
{
	SpriteGo::Update(dt);

	sf::Vector2f playerpos = player->GetPosition() - position;
	SetRotation(Utils::Angle(playerpos));
	Translate(Utils::GetNormal(playerpos) * speed * dt);


	//SetPosition( position + direction * speed * dt);

	//sf::Vector2f direction = player->GetPosition() - position;
	//Utils::Normalize(direction);
	//Translate(direction * speed * dt);
	//SetRotation(Utils::Angle(direction));
}

void Zombie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}


