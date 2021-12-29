#pragma once
#include "T_Config.h"
#include "T_Vector3.h"
#include "T_Graph.h"
/*
* 
* 采用ECS架构的三维组件
* 
* TsukuYomi
* 
*/

class T_GameObject;
class T_GameObjectManager;

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
	virtual void KeyAction(int KeyType, int ActionType) = 0;
	virtual void MouseAction(int x, int y, int ActionType) = 0;
};
/// <summary>
/// 场景基类
/// </summary>
class T_Scene {
public:
	T_Scene();
	static unique_ptr<T_Scene> activeScene;
	virtual void LoadScene() = 0;
	map<int, unique_ptr<T_IManager> > ManagerMap;
	unique_ptr<T_GameObjectManager> gameObjectManager;
	unique_ptr<T_IManager> renderManager;
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
	/// 对键盘操作响应
	/// </summary>
	/// <param name="ActionType">键盘操作类型</param>
	virtual void KeyAction(int KeyType, int ActionType);
	/// <summary>
	/// 对鼠标操作响应
	/// </summary>
	/// <param name="x">鼠标指针x轴坐标</param>
	/// <param name="y">鼠标指针y轴坐标</param>
	/// <param name="MouseAction">鼠标操作类型</param>
	virtual void MouseAction(int x, int y, int MouseAction);
	/// <summary>
	/// 将该组件挂载到游戏物体上
	/// </summary>
	/// <param name="gameObject">被挂载的游戏物体</param>
	void JoinTo(unique_ptr<T_GameObject> gameObject);
	bool isDestroy = false;
	bool isActive = true;
};
/// <summary>
/// 转换
/// </summary>
class T_Transform {
public:
	T_Transform();
	T_Transform(const T_Vector3& pos, const T_Vector3& rot);
	T_Vector3 position;
	T_Vector3 rotation;
	/// <summary>
	/// 将父坐标系为世界的transform转换为父坐标系为自身的transform（相对位置与旋转不变）
	/// </summary>
	/// <param name="transform">要做转换的transform</param>
	/// <returns>转换结果</returns>
	T_Transform WorldToLocalTransform(const T_Transform& transform);
	/// <summary>
	/// 将父坐标系为自身的transform转换为父坐标系为世界的transform（相对位置与旋转不变）
	/// </summary>
	/// <param name="transform">要做转换的transform</param>
	/// <returns>转换结果</returns>
	T_Transform LocalToWorldTransform(const T_Transform& transform);
};

/// <summary>
/// 游戏实体
/// </summary>
class T_GameObject{
public:
    T_GameObject();
    string name;
    T_Transform transform;
    vector<unique_ptr<T_Component>> componentArray;
    void ClearComponent();
    bool isDestroy = false;
    bool isActive = true;
    bool componentClearFlag=false;
};

/// <summary>
/// 游戏实体管理器，管理器ID无效
/// </summary>
class T_GameObjectManager:
        public T_IManager
{
public:
    T_GameObjectManager();
    vector<unique_ptr<T_GameObject>> gameObjectArray;
    unique_ptr<T_GameObject>& AddGameObject(unique_ptr<T_GameObject> sprite);
    void ClearGameObject();
    bool gameObjectClearFlag = false;
    void Destroy(unique_ptr<T_GameObject>& gameObject);
    void Update() override;
    void UpdateLate() override;
    void FixedUpdate() override;
    void KeyAction(int,int) override;
    void MouseAction(int, int, int) override;

};
