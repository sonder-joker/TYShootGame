#pragma once
#include "T_Config.h"
#include "T_Vector3.h"
#include "T_Graph.h"
/*
* 
* 采用ECS架构的三维组件
* 
*/

/// <summary>
/// 游戏实体
/// </summary>
class T_GameObject{
public:
	T_GameObject();
	string name;
	T_Transform transform;
	vector<unique_ptr<T_Component>> componentArray;
	bool isDestroy = false;
	bool isActive = true;

};
/// <summary>
/// 管理器接口
/// </summary>
class T_IManager {
public:
 	/// <summary>
 	/// 获得管理器ID,游戏根据管理器ID顺序进行更新
 	/// </summary>
	/// <return>返回唯一管理器ID</return>
 	virtual int GetManagerID() = 0;
	virtual void Update() = 0;
	virtual void UpdateLate() = 0;
	virtual void FixedUpdate() = 0;
	virtual void KeyAction(int ActionType) = 0;
	virtual void MouseAction(int x, int y, int ActionType) = 0;
};
/// <summary>
/// 场景基类
/// </summary>
class T_Scene {
public:
	virtual void LoadScene() = 0;
	map<int, unique_ptr<T_IManager> > ManagerMap;
	unique_ptr<T_IManager> gameObjectManager;
	unique_ptr<T_IManager> renderManager;
};
/// <summary>
/// 游戏实体管理器，管理器ID无效
/// </summary>
class T_GameObjectManager:
	public T_IManager
{
public:
	vector<unique_ptr<T_GameObject>> gameObjectArray;
	unique_ptr<T_GameObject>& AddGameObject(unique_ptr<T_GameObject> sprite);
	void ClearGameObject();
	unique_ptr<T_GameObject>& FindGameObject(string name);

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
/// <summary>
/// 转换
/// </summary>
class T_Transform {
public:
	T_Vector3 position;
	T_Vector3 rotation;
};

