#pragma once
#include "T_Config.h"
#include "T_Vector3.h"
#include "T_Graph.h"

class T_GameObject;
class T_GameObjectManager;

class T_IManager {
public:
    virtual int GetManagerID() { return -1; };
    virtual void Start() {};
    virtual void Update(){};
    virtual void Update(HDC hdc){};
	virtual void UpdateLate(){};
	virtual void FixedUpdate() {};
	virtual void KeyAction(int KeyType, int ActionType){};
	virtual void MouseAction(int x, int y, int ActionType){};
};


class T_Component
{
public:
    T_Component(T_GameObject& tGameObject);

	T_GameObject& gameObject;

    virtual string GetComponentName(){return "component";};

	virtual void Start();

	virtual void Update();

	virtual void UpdateLate();

	virtual void FixedUpdate();

	virtual void OnDestroy();

	virtual void KeyAction(int KeyType, int ActionType);

	virtual void MouseAction(int x, int y, int MouseAction);

    bool isDestroy = false;
	bool isActive = true;
};
class T_Transform {
public:
	T_Transform();
	T_Transform(const T_Vector3& pos, const T_Vector3& rot);
	T_Vector3 position;
	T_Vector3 rotation;

	T_Transform WorldToLocalTransform(const T_Transform& transform);

	T_Transform LocalToWorldTransform(const T_Transform& transform);
};

class T_GameObject{
public:
    T_GameObject(string name);
    string name;
    T_Transform transform;
    vector<shared_ptr<T_Component>> componentArray;
    void ClearComponent();
    bool isDestroy = false;
    bool isActive = true;
    bool componentClearFlag=false;
};

class T_GameObjectManager:
        public T_IManager
{
public:
    int GetManagerID() override {return 1;};
    T_GameObjectManager();
    vector<unique_ptr<T_GameObject>> gameObjectArray;
    T_GameObject& AddGameObject(unique_ptr<T_GameObject> gameObject);
    void ClearGameObject();
    bool gameObjectClearFlag = false;
    void Destroy(unique_ptr<T_GameObject>& gameObject);
    void Start() override;
    void Update() override;
    void UpdateLate() override;
    void FixedUpdate() override;
    void KeyAction(int,int) override;
    void MouseAction(int, int, int) override;

};
