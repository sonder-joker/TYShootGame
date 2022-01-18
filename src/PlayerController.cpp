#include "PlayerController.h"
#include "InputManager.h"
#include "T_Scene.h"
void PlayerController::Update()
{
	T_Vector3 move;
	if (InputManager::GetInstance().GetKeyDown('W')) {
		move.z += 1;
	}
	else if (InputManager::GetInstance().GetKeyDown('S')) {
		move.z -= 1;
	}
	if (InputManager::GetInstance().GetKeyDown('D')) {
		gameObject.transform.rotation.x += 0.05;
	}
	else if (InputManager::GetInstance().GetKeyDown('A')) {
		gameObject.transform.rotation.x -= 0.05;
	}
    //没有移动，提前跳出

    if(move.z==0) return;
    float xmove = move.z * v * cosf(gameObject.transform.rotation.x);
    float ymove = move.z * v * sinf(gameObject.transform.rotation.x);
    gameObject.transform.position.x += xmove*3;
	gameObject.transform.position.z += ymove*3;
    Rast nextStep=T_Scene::activeScene->gameMap->getBlockTypeAt(gameObject.transform.position);
    if(nextStep.graphIndex!=0){
        gameObject.transform.position.x-=xmove*3;
        gameObject.transform.position.z-=ymove*3;
    }else{
        gameObject.transform.position.x-=xmove*2;
        gameObject.transform.position.z-=ymove*2;
    }
}
