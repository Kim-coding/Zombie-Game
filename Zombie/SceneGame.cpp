#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "ZombieSpawner.h"

SceneGame::SceneGame(SceneIds id)
	:Scene(id)
{
}

void SceneGame::Init()
{
	AddGo(new TileMap("Background"));

	spawners.push_back(new ZombieSpawner());
	spawners.push_back(new ZombieSpawner());
	
	for (auto s : spawners)
	{
		s->SetPosition(Utils::RandomOnUnitCircle() * 250.f);
		AddGo(s);
	}

	player = new Player("Player");
	AddGo(player);

//	AddGo(new TileMap("Background"));     //테스트 코드가 들어갈 부분


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


	/*좀비 Scene클래스 에서 삭제되도록 만들었음*/
	//std::vector<GameObject*> removeZombies;      //좀비 객체들을 저장할 공간
	//for (auto obj : gameObjects)
	//{
	//	Zombie* zombie = dynamic_cast<Zombie*>(obj);
	//	if (zombie != nullptr)
	//	{
	//		float distance = Utils::Distance(player->GetPosition(), zombie->GetPosition());
	//		if (distance <= 10.f)
	//		{
	//			removeZombies.push_back(zombie);           //player와 거리가 10이하인 것은 충돌된 것으로 삭제 대상
	//		}
	//	}
	//}

	/*for (auto obj : removeZombies)
	{
		RemoveGo(obj);
		delete obj;
	}*/


	
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
