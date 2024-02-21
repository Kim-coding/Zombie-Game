#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"

SceneGame::SceneGame(SceneIds id)
	:Scene(id)
{
}

void SceneGame::Init()
{
	AddGo(new TileMap("Background"));

	player = new Player("Player");
	AddGo(player);

	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	Scene::Enter();


	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = (sf::Vector2f)FRAMEWORK.GetWindowSize() * 0.5f;

	worldView.setSize(windowSize);             //ȭ���� ĳ���͸� ���󰡵��� �������
	worldView.setCenter({ 0.f,0.f });
	uiView.setSize(windowSize);                //�� ������ �⺻���� �Ѵ�.
	uiView.setCenter(centerPos);

	TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));
	tileMap->SetPosition({0, 0});
	tileMap->SetOrigin(Origins::MC);
	tileMap->SetRotation(0);
	//tileMap->SetScale({2.f, 2.f}); //Ÿ�� ������ 2��

	player->SetPosition({ 0, 0 });
}

void SceneGame::Exit()
{
	Scene::Exit();

}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	worldView.setCenter(player->GetPosition());

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))     //���� ����
	{
		Zombie::Types zombieType = (Zombie::Types)Utils::RandomRange(0, Zombie::TotalTypes);
		zombie = Zombie::Create(zombieType);
		zombie->Init();
		zombie->Reset();
		zombie->SetPosition(Utils::RandomInUnitCircle() * 600.f);
		
		AddGo(zombie);
	}

	std::vector<GameObject*> removeZombies;      //���� ��ü���� ������ ����
	for (auto obj : gameObjects)
	{
		Zombie* zombie = dynamic_cast<Zombie*>(obj);
		if (zombie != nullptr)
		{
			float distance = Utils::Distance(player->GetPosition(), zombie->GetPosition());
			if (distance <= 10.f)
			{
				removeZombies.push_back(zombie);           //player�� �Ÿ��� 10������ ���� �浹�� ������ ���� ���
			}
		}
	}

	for (auto obj : removeZombies)
	{
		gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), obj), gameObjects.end());
		//removeZombies�� �ִ� obj�� gameObject���� �����ϱ� ����.
		//std::remove() => obj�� ���� ���� ã�Ƽ� ������ ������ �̵���Ŵ.
		//gameObjects.erase(, gameObjects.end()) => std::remove()�� ���� ��ȯ�� ������ ������������ ����.
		//��, ������ �̵��� ��� ��Ҹ� ����.
		delete obj;
	}


	
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
