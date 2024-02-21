#include "pch.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& name)
	: GameObject(name)
{
}

void TileMap::Set(const sf::Vector2f& count, const sf::Vector2f& size)
{
	cellCount = count;
	cellSize = size;

	va.clear();
	va.setPrimitiveType(sf::Quads);
	va.resize(count.x * count.y * 4);                     //���� ���ؽ� ��̰� ������ �ִ� ������?

	sf::Vector2f posOffsets[4] = {                        //�簢���� �� ���� ������ �̸� ����� ����
		{ 0, 0 },
		{ size.x, 0 },
		{ size.x, size.y },
		{ 0, size.y }

	};

	sf::Vector2f texCoord0[4] = {                        
		{ 0, 0 },
		{ 50.f, 0 },
		{ 50.f, 50.f },
		{ 0, 50.f }

	};

	for (int i = 0; i < count.y; ++i)                    
	{
		for (int j = 0; j < count.x; ++j)                 
		{

			int texIndex = Utils::RandomRange(0, 3);
			if (i == 0 || i == count.y - 1 || j == 0 || j == count.x - 1)
			{
				texIndex = 3;                                  // �ܰ�
			}

			int quadIndex = i * count.x + j;                   //�簢�� �ε���    // 2���� �迭�� 1�������� �����ϴ� ������ �ʿ��ϴ�
			
			sf::Vector2f quadPos(position.x + size.x * j, position.y + size.y * i);

			for (int k = 0; k < 4; ++k)                        //���� ����
			{
				int vertexIndex = (quadIndex * 4) + k;
				va[vertexIndex].position = quadPos + posOffsets[k];
				va[vertexIndex].texCoords = texCoord0[k];
				va[vertexIndex].texCoords.y += texIndex * 50.f;
			}
		}
	}
}

void TileMap::SetSpriteSheetId(const std::string& id)
{
	spriteSheetId = id;
	texture = &RES_MGR_TEXTURE.Get(spriteSheetId);
}

void TileMap::SetOrigin(Origins preset)
{
	if (preset == Origins::Custom)
		return;

	sf::FloatRect bound = va.getBounds();
	sf::Vector2f newOrigin(bound.width, bound.height);
	newOrigin.x *= ((int)preset % 3) * 0.5f;
	newOrigin.y *= ((int)preset / 3) * 0.5f;

	for (int i = 0; i < va.getVertexCount(); ++i)
	{
		va[i].position -= newOrigin;
	}
	
	/*va.getBounds();*/

	/*if (preset == Origins::Custom)
	{
		preset = Origins::MC;
	}
	originPreset = preset;
	origin ={ 0, 0 };*/
	
}

void TileMap::SetOrigin(const sf::Vector2f& newOrigin)
{

}

void TileMap::SetPosition(const sf::Vector2f& pos)    //�̵��� ��ŭ Ÿ�ϵ� �̵�
{
	sf::Vector2f delta = pos - position;
	for (int i = 0; i < va.getVertexCount(); ++i)
	{
		va[i].position += delta;
	}
	position = pos;
}

void TileMap::SetScale(const sf::Vector2f& scale)
{
}

void TileMap::SetFlipX(bool flip)
{
}

void TileMap::SetFlipY(bool flip)
{
}

void TileMap::Init()
{
	GameObject::Init();
	SetSpriteSheetId("graphics/background_sheet.png");

	
	Set({ 20, 20 }, { 50, 50 });
	SetOrigin(Origins::MC);
}

void TileMap::Release()
{
	GameObject::Release();
}

void TileMap::Reset()
{
	GameObject::Reset();
}

void TileMap::Update(float dt)
{
	GameObject::Update(dt);
}

void TileMap::Draw(sf::RenderWindow& window)
{
	//GameObject::Draw(window);
	window.draw(va, texture);
}
