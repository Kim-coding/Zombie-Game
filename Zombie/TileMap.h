#pragma once
#include "GameObject.h"
class TileMap : public GameObject
{
protected:
	sf::VertexArray va;                  // �׸��� ��ü�� ���, Ÿ�� ���� ���� �����
	std::string spriteSheetId;           // 
	sf::Texture* texture;

	int rows = 10;
	int cols = 10;

	sf::Vector2f cellCount;    
	sf::Vector2f cellSize;     

public:
	TileMap(const std::string& name = "");

	void SetSpriteSheetId(const std::string& id);

	void Set(const sf::Vector2f& count, const sf::Vector2f& size);

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void SetPosition(const sf::Vector2f& pos) override;

	void SetScale(const sf::Vector2f& scale) override;

	void SetFlipX(bool flip) override;

	void SetFlipY(bool flip) override;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;


};

