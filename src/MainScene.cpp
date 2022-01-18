#include "MainScene.h"
#include "T_Render.h"
#include "InputManager.h"
#include "PlayerController.h"
#include "PlayerLogic.h"
#include "Ghost.h"

void MainScene::LoadScene()
{
    gameObjectManager = make_unique<T_GameObjectManager>();
    gameMap = make_unique<T_Map>("./Map/MapFile/map2.txt");
    renderManager = make_unique<T_Render>(*gameMap);
    ManagerMap.push_back(make_shared<InputManager>());
    T_GameObject& player = gameObjectManager->AddGameObject(move(make_unique<T_GameObject>("Player")));
    player.transform.position = T_Vector3(8.5, 0, 8.5);
    player.transform.rotation = T_Vector3(0, 0, 0);
    player.componentArray.push_back(make_shared<Camera>(player));
    player.componentArray.push_back(make_shared<PlayerController>(player));
    player.componentArray.push_back(make_shared<PlayerLogic>(player));
    T_Vector3 flowerVec[3] = { T_Vector3(3.5,-0.6,3.5),T_Vector3(7.5,-0.6,5.5),T_Vector3(4.5,-0.6,7.5) };
    for (int i = 0; i < 3; ++i) {
        T_GameObject& flower =
            gameObjectManager->AddGameObject(move(make_unique<T_GameObject>("Flower")));
        flower.componentArray.push_back(Sprite::CreateSprite(flower, 50));
        flower.transform.position = flowerVec[i];
    }
    for (int i = 0; i < 3; ++i) {
        T_GameObject& ghost =
            gameObjectManager->AddGameObject(move(make_unique<T_GameObject>("Ghost")));
        ghost.componentArray.push_back(Sprite::CreateSprite(ghost, 51));
        ghost.componentArray.push_back(make_shared<Ghost>(ghost,11,10));
    }
    T_GameObject& flag =
        gameObjectManager->AddGameObject(move(make_unique<T_GameObject>("Flag")));
    flag.componentArray.push_back(Sprite::CreateSprite(flag, 52));
    flag.transform.position = T_Vector3(1.5, 0, 1.5);
}

void TestScene::LoadScene() {
    gameObjectManager= make_unique<T_GameObjectManager>();
    gameMap= make_unique<T_Map>("./Map/MapFile/map1.txt");
    renderManager= make_unique<T_Render>(*gameMap);
    ManagerMap.push_back(make_shared<InputManager>());
    T_GameObject& player= gameObjectManager->AddGameObject(move(make_unique<T_GameObject>("Player")));
    player.transform.position = T_Vector3(2.5,0,2.5);
    player.transform.rotation = T_Vector3(0,0,0);
    player.componentArray.push_back(make_shared<PlayerLogic>(player));
    player.componentArray.push_back(make_shared<Camera>(player));
    player.componentArray.push_back(make_shared<PlayerController>(player));
    T_GameObject& flower=
            gameObjectManager->AddGameObject(move(make_unique<T_GameObject>("Flower")));
    flower.componentArray.push_back(Sprite::CreateSprite(flower,50));
    flower.transform.position=T_Vector3(2.5,-0.1,3.5);
    T_GameObject& flower2=
            gameObjectManager->AddGameObject(move(make_unique<T_GameObject>("Flower2")));
    flower2.componentArray.push_back(Sprite::CreateSprite(flower2,50));
    flower2.transform.position=T_Vector3(2.5,-0.1,1.5);
    T_GameObject& flag =
        gameObjectManager->AddGameObject(move(make_unique<T_GameObject>("Flag")));
    flag.componentArray.push_back(Sprite::CreateSprite(flag, 52));
    flag.transform.position = T_Vector3(1.5, 0, 1.5);
    T_GameObject& ghost =
        gameObjectManager->AddGameObject(move(make_unique<T_GameObject>("Ghost")));
    ghost.componentArray.push_back(Sprite::CreateSprite(ghost, 51));
    ghost.componentArray.push_back(make_shared<Ghost>(ghost, 11, 10)); 
}

void Scene1::LoadScene() {


}
