#pragma once
#include "T_Config.h"
#include "T_Vector3.h"
#include "T_Graph.h"

class T_GameObject{
public:
	T_GameObject();
	string name;
	T_Transform transform;
	vector<unique_ptr<T_Component>> componentArray;
	bool isDestroy = false;
	bool isActive = true;

};

static class T_GameObjectManager {
public:
	static vector<unique_ptr<T_GameObject>> gameObjectArray;
	static unique_ptr<T_GameObject>& AddGameObject(unique_ptr<T_GameObject> sprite);
	static void ClearGameObject();
	static unique_ptr<T_GameObject>& FindGameObject(string name);

};

class T_Component
{
public:
	T_GameObject& gameObject;
	virtual void Start();
	/// <summary>
	/// 每帧渲染前调用一次
	/// </summary>
	virtual void Update();
	/// <summary>
	/// 每帧渲染后调用一次
	/// </summary>
	virtual void UpdateLate();
	/// <summary>
	/// 固定每秒调用数次
	/// </summary>
	virtual void FixedUpdate();
	/// <summary>
	/// 物品摧毁前调用一次
	/// </summary>
	virtual void OnDestroy();
	/// <summary>
	/// 将该组件挂载到游戏物体上
	/// </summary>
	/// <param name="gameObject">被挂载的游戏物体</param>
	void JoinTo(unique_ptr<T_GameObject> gameObject);
};

class T_Transform {
public:
	T_Vector3 position;
	T_Vector3 rotation;
};

