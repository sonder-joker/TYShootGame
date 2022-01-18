#include "MainScene.h"
#include "T_Render.h"
#include "InputManager.h"
#include "PlayerController.h"

void MainScene::LoadScene()
{

}

void TestScene::LoadScene() {
    gameObjectManager= make_unique<T_GameObjectManager>();
    gameMap= make_unique<T_Map>("./Map/MapFile/map1.txt");
    renderManager= make_unique<T_Render>(*gameMap);
    ManagerMap.push_back(make_shared<InputManager>());
    T_GameObject& player= gameObjectManager->AddGameObject(move(make_unique<T_GameObject>("Player")));
    T_GameObject& flower= gameObjectManager->AddGameObject(move(make_unique<T_GameObject>("Flower")));
    player.transform.position = T_Vector3(2.5,0,2.5);
    player.transform.rotation = T_Vector3(0,0,0);
    player.componentArray.push_back(make_shared<Camera>(player));
    player.componentArray.push_back(make_shared<PlayerController>(player));
    flower.componentArray.push_back(Sprite::CreateSprite(flower,50));
    flower.transform.position=T_Vector3(2.5,0,1.5);
}
