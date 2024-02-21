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
	tileMap->SetPosition({0, 0});
	tileMap->SetOrigin(Origins::MC);
	tileMap->SetRotation(0);
	//tileMap->SetScale({2.f, 2.f}); //타일 스케일 2배

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

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))     //좀비 생성
	{
		Zombie::Types zombieType = (Zombie::Types)Utils::RandomRange(0, Zombie::TotalTypes);
		zombie = Zombie::Create(zombieType);
		zombie->Init();
		zombie->Reset();
		zombie->SetPosition(Utils::RandomInUnitCircle() * 600.f);
		
		AddGo(zombie);
	}

	std::vector<GameObject*> removeZombies;      //좀비 객체들을 저장할 공간
	for (auto obj : gameObjects)
	{
		Zombie* zombie = dynamic_cast<Zombie*>(obj);
		if (zombie != nullptr)
		{
			float distance = Utils::Distance(player->GetPosition(), zombie->GetPosition());
			if (distance <= 10.f)
			{
				removeZombies.push_back(zombie);           //player와 거리가 10이하인 것은 충돌된 것으로 삭제 대상
			}
		}
	}

	for (auto obj : removeZombies)
	{
		gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), obj), gameObjects.end());
		//removeZombies에 있는 obj를 gameObject에서 삭제하기 위함.
		//std::remove() => obj와 같은 값을 찾아서 벡터의 끝으로 이동시킴.
		//gameObjects.erase(, gameObjects.end()) => std::remove()에 의해 반환된 값부터 마지막값까지 제거.
		//즉, 끝으로 이동된 모든 요소를 삭제.
		delete obj;
	}


	
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
