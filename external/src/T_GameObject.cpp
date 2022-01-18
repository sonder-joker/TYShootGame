#include "T_GameObject.h"
#include "T_Render.h"
T_GameObjectManager::T_GameObjectManager()
{
	//TODO ��ʼ��
}
T_GameObject& T_GameObjectManager::AddGameObject(unique_ptr<T_GameObject> gameObject)
{
	gameObjectArray.push_back(move(gameObject));
	return **gameObjectArray.rbegin();
}

void T_GameObjectManager::Start() {
	for (auto& gameObjectItor : gameObjectArray) {
		if (gameObjectItor->isActive) {
			for (auto& componentItor : gameObjectItor->componentArray) {
				componentItor->Start();
			}
		}
	}
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

T_GameObject::T_GameObject(string name)
{
	this->name=name;
}

void T_GameObject::ClearComponent()
{
	auto pSlow = componentArray.begin();
	auto pFast = componentArray.begin();
	while (pFast != componentArray.end()) {
		bool slowIsDestroy = (*pSlow)->isDestroy;
		bool fastIsDestroy = (*pFast)->isDestroy;
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

void T_Component::KeyAction(int KeyType, int ActionType) {

}

void T_Component::MouseAction(int x, int y, int MouseAction) {

}

T_Component::T_Component(T_GameObject& tGameObject):gameObject(tGameObject) {

}


T_Transform::T_Transform()
{

}

T_Transform::T_Transform(const T_Vector3& pos, const T_Vector3& rot)
{
	position = pos;
	rotation = rot;
}

T_Transform T_Transform::WorldToLocalTransform(const T_Transform& transform)
{
	T_Transform ret = T_Transform(transform.position, transform.rotation);
	ret.position = ret.position - position;
	float sinx = sinf(-rotation.x), cosx = cosf(-rotation.x);
	float siny = sinf(-rotation.y), cosy = cosf(-rotation.y);
	float sinz = sinf(-rotation.z), cosz = cosf(-rotation.z);
	T_Matrix3 xRotMatrix = T_Matrix3(
		1, 0, 0,
		0, cosx, -sinx,
		0, sinx, cosx
	);
	T_Matrix3 yRotMatrix = T_Matrix3(
		cosy, 0, siny,
		0, 1, 0,
		-siny, 0, cosy
	);
	T_Matrix3 zRotMatrix = T_Matrix3(
		cosz, -sinz, 0,
		sinz, cosz, 0,
		0, 0, 1
	);
	ret.position = xRotMatrix * ret.position;
	ret.position = yRotMatrix * ret.position;
	ret.position = zRotMatrix * ret.position;
	ret.rotation = ret.rotation - rotation;
	return ret;
}

T_Transform T_Transform::LocalToWorldTransform(const T_Transform& transform)
{
	T_Transform ret = T_Transform(transform.position, transform.rotation);
	float sinx = sinf(rotation.x), cosx = cosf(rotation.x);
	float siny = sinf(rotation.y), cosy = cosf(rotation.y);
	float sinz = sinf(rotation.z), cosz = cosf(rotation.z);
	T_Matrix3 xRotMatrix = T_Matrix3(
		1, 0, 0,
		0, cosx, -sinx,
		0, sinx, cosx
	);
	T_Matrix3 yRotMatrix = T_Matrix3(
		cosy, 0, siny,
		0, 1, 0,
		-siny, 0, cosy
	);
	T_Matrix3 zRotMatrix = T_Matrix3(
		cosz, -sinz, 0,
		sinz, cosz, 0,
		0, 0, 1
	);
	ret.position = xRotMatrix * ret.position;
	ret.position = yRotMatrix * ret.position;
	ret.position = zRotMatrix * ret.position;
	ret.position = ret.position + position;
	ret.rotation = ret.rotation + rotation;
    return ret;
}
