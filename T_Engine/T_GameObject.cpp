#include "T_GameObject.h"

unique_ptr<T_GameObject>& T_GameObjectManager::AddGameObject(unique_ptr<T_GameObject> gameObject)
{
	gameObjectArray.push_back(gameObject);
	return gameObject;
}

T_GameObject::T_GameObject()
{
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
