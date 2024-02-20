#include "pch.h"
#include "Player.h"

Player::Player(const std::string& name)
	:SpriteGo(name)
{
}

void Player::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/player.png");
	SetOrigin(Origins::MC);
}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Reset()
{
	SpriteGo::Reset();
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);

	sf::Vector2f mousePos = InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = mousePos;

	std::cout << mouseWorldPos.x << "     " << mouseWorldPos.y << std::endl;

	look = mouseWorldPos - position;
	Utils::Normalize(look);        

	float angle = Utils::Angle(look);          //각도
	sprite.setRotation(angle);

	//플레이어부터 마우스 포인터를 바라보는 방향과 각도

	
	direction.x = InputMgr::GetAxis(Axis::Horizontal);    //선생님 코드
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Normalize(direction);
	}
	SetPosition(position + direction * speed * dt);
	

	/*
	float h = InputMgr::GetAxis(Axis::Horizontal);        //내 코드
	sf::Vector2f posX = sprite.getPosition();
	posX.x += h * speed * dt;
	SetPosition(posX);

	float v = InputMgr::GetAxis(Axis::Vertical);
	sf::Vector2f posY = sprite.getPosition();
	posY.y += v * speed * dt;
	SetPosition(posY);
	*/
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
