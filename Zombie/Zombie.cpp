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
	case Zombie::Types::Chase:
		zombie->textureId = "graphics/chase.png";
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

	sf::Vector2i playerpos = (sf::Vector2i)player->GetPosition();
	sf::Vector2f playerWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(playerpos);

	look = playerWorldPos - position;
	Utils::Normalize(look);

	float angle = Utils::Angle(look);
	sprite.setRotation(angle);



}

void Zombie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
