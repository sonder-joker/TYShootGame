#include "T_GameObject.h"

unique_ptr<T_GameObject>& T_GameObjectManager::AddGameObject(unique_ptr<T_GameObject> gameObject)
{
	gameObjectArray.push_back(gameObject);
	return gameObject;
}

T_GameObject::T_GameObject()
{
}
