#pragma once
#include "T_Config.h"
#include "T_Vector3.h"
#include "T_Graph.h"
/*
* 
* ����ECS�ܹ�����ά���
* 
* TsukuYomi
* 
*/

class T_GameObject;
class T_GameObjectManager;

/// <summary>
/// �������ӿ�
/// </summary>
class T_IManager {
public:
 	/// <summary>
 	/// ��ù�����ID,��Ϸ���ݹ�����ID˳����и���
 	/// </summary>
	/// <return>����Ψһ������ID</return>
 	virtual int GetManagerID() = 0;
	virtual void Update(){};
	virtual void UpdateLate(){};
	virtual void FixedUpdate() {};
	virtual void KeyAction(int KeyType, int ActionType){};
	virtual void MouseAction(int x, int y, int ActionType){};
};
/// <summary>
/// ��������
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
	/// ÿ֡��Ⱦǰ����һ��
	/// </summary>
	virtual void Update();
	/// <summary>
	/// ÿ֡��Ⱦ�����һ��
	/// </summary>
	virtual void UpdateLate();
	/// <summary>
	/// �̶�ÿ���������
	/// </summary>
	virtual void FixedUpdate();
	/// <summary>
	/// ��Ʒ�ݻ�ǰ����һ��
	/// </summary>
	virtual void OnDestroy();
	/// <summary>
	/// �Լ��̲�����Ӧ
	/// </summary>
	/// <param name="ActionType">���̲�������</param>
	virtual void KeyAction(int KeyType, int ActionType);
	/// <summary>
	/// ����������Ӧ
	/// </summary>
	/// <param name="x">���ָ��x������</param>
	/// <param name="y">���ָ��y������</param>
	/// <param name="MouseAction">����������</param>
	virtual void MouseAction(int x, int y, int MouseAction);
	/// <summary>
	/// ����������ص���Ϸ������
	/// </summary>
	/// <param name="gameObject">�����ص���Ϸ����</param>
	void JoinTo(unique_ptr<T_GameObject> gameObject);
	bool isDestroy = false;
	bool isActive = true;
};
/// <summary>
/// ת��
/// </summary>
class T_Transform {
public:
	T_Transform();
	T_Transform(const T_Vector3& pos, const T_Vector3& rot);
	T_Vector3 position;
	T_Vector3 rotation;
	/// <summary>
	/// ��������ϵΪ�����transformת��Ϊ������ϵΪ�����transform�����λ������ת���䣩
	/// </summary>
	/// <param name="transform">Ҫ��ת����transform</param>
	/// <returns>ת�����</returns>
	T_Transform WorldToLocalTransform(const T_Transform& transform);
	/// <summary>
	/// ��������ϵΪ�����transformת��Ϊ������ϵΪ�����transform�����λ������ת���䣩
	/// </summary>
	/// <param name="transform">Ҫ��ת����transform</param>
	/// <returns>ת�����</returns>
	T_Transform LocalToWorldTransform(const T_Transform& transform);
};

/// <summary>
/// ��Ϸʵ��
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
/// ��Ϸʵ���������������ID��Ч
/// </summary>
class T_GameObjectManager:
        public T_IManager
{
public:
    int GetManagerID() override {return 1;};
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
