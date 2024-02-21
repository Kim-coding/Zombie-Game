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

	worldView.setSize(windowSize);             //화면이 캐릭터를 따라가도록 만들거임
	worldView.setCenter({ 0.f,0.f });
	uiView.setSize(windowSize);                //좌 상점이 기본으로 한다.
	uiView.setCenter(centerPos);

	TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));
	tileMap->SetPosition(centerPos);
	tileMap->SetOrigin(Origins::MC);
	tileMap->SetRotation(0);
	//tileMap->SetScale({2.f, 2.f}); //타일 스케일 2배

	player->SetPosition(centerPos);
}

void SceneGame::Exit()
{
	Scene::Exit();

}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	worldView.setCenter(player->GetPosition());

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		Zombie::Types zombieType = (Zombie::Types)Utils::RandomRange(0, Zombie::TotalTypes);
		Zombie* zombie = Zombie::Create(zombieType);
		zombie->Init();
		zombie->Reset();
		zombie->SetPosition(Utils::RandomInUnitCircle() * 500.f);

		AddGo(zombie);
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
