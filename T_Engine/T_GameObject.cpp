#include "T_GameObject.h"
#include "../T_Render.h"
T_GameObjectManager::T_GameObjectManager()
{
	//TODO ≥ı ºªØ
}
unique_ptr<T_GameObject>& T_GameObjectManager::AddGameObject(unique_ptr<T_GameObject> gameObject)
{
	gameObjectArray.push_back(gameObject);
	return gameObject;
}

void T_GameObjectManager::ClearGameObject()
{
	auto pSlow = gameObjectArray.begin();
	auto pFast = gameObjectArray.begin();
	while (pFast != gameObjectArray.end()) {
		bool slowIsDestroy = pSlow->get()->isDestroy;
		bool fastIsDestroy = pFast->get()->isDestroy;
		if (slowIsDestroy && fastIsDestroy) {
			++pFast;
		}
		else if (slowIsDestroy) {
			swap(pSlow, pFast);
			++pSlow; ++pFast;
		}
		else if (pSlow == pFast) {
			++pSlow; ++pFast;
		}
		else {
			++pSlow;
		}
	}
	gameObjectArray.erase(pSlow, gameObjectArray.end());
	gameObjectClearFlag = false;
}

void T_GameObjectManager::Destroy(unique_ptr<T_GameObject>& gameObject)
{
	gameObject->isDestroy = true;
	gameObject->isActive = false;
	gameObjectClearFlag = true;
	for (auto& componentItor : gameObject->componentArray) {
		componentItor->OnDestroy();
	}
}

void T_GameObjectManager::Update()
{
	if (gameObjectClearFlag) {
		ClearGameObject();
	}
	for (auto& gameObjectItor : gameObjectArray) {
		if (gameObjectItor->isActive) {
			for (auto& componentItor : gameObjectItor->componentArray) {
				componentItor->Update();
			}
		}
	}
}

void T_GameObjectManager::UpdateLate()
{
	if (gameObjectClearFlag) {
		ClearGameObject();
	}
	for (auto& gameObjectItor : gameObjectArray) {
		if (gameObjectItor->isActive) {
			for (auto& componentItor : gameObjectItor->componentArray) {
				componentItor->UpdateLate();
			}
		}
	}
}

void T_GameObjectManager::FixedUpdate()
{
	if (gameObjectClearFlag) {
		ClearGameObject();
	}
	for (auto& gameObjectItor : gameObjectArray) {
		if (gameObjectItor->isActive) {
			for (auto& componentItor : gameObjectItor->componentArray) {
				componentItor->FixedUpdate();
			}
		}
	}
}

void T_GameObjectManager::KeyAction(int KeyType, int ActionType)
{
	if (gameObjectClearFlag) {
		ClearGameObject();
	}
	for (auto& gameObjectItor : gameObjectArray) {
		if (gameObjectItor->isActive) {
			for (auto& componentItor : gameObjectItor->componentArray) {
				componentItor->KeyAction(KeyType, ActionType);
			}
		}
	}
}

void T_GameObjectManager::MouseAction(int x, int y, int t)
{
	if (gameObjectClearFlag) {
		ClearGameObject();
	}
	for (auto& gameObjectItor : gameObjectArray) {
		if (gameObjectItor->isActive) {
			for (auto& componentItor : gameObjectItor->componentArray) {
				componentItor->MouseAction(x,y,t);
			}
		}
	}
}

T_GameObject::T_GameObject()
{
	
}

void T_GameObject::ClearComponent()
{
	auto pSlow = componentArray.begin();
	auto pFast = componentArray.begin();
	while (pFast != componentArray.end()) {
		bool slowIsDestroy = pSlow->get()->isDestroy;
		bool fastIsDestroy = pFast->get()->isDestroy;
		if (slowIsDestroy && fastIsDestroy) {
			++pFast;
		}
		else if (slowIsDestroy) {
			swap(pSlow, pFast);
			++pSlow; ++pFast;
		}
		else if(pSlow==pFast){
			++pSlow; ++pFast;
		}
		else {
			++pSlow;
		}
	}
	componentArray.erase(pSlow, componentArray.end());
	componentClearFlag = false;
}

void T_Component::Start()
{
}

void T_Component::Update()
{
}

void T_Component::UpdateLate()
{
}

void T_Component::FixedUpdate()
{
}

void T_Component::OnDestroy()
{
}

void T_Component::JoinTo(unique_ptr<T_GameObject> gameObject)
{
}

T_Scene::T_Scene()
{
	gameObjectManager = make_unique<T_GameObjectManager>();
	renderManager = make_unique<T_Render>();
}
