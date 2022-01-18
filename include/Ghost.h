#pragma once

#include <T_GameObject.h>
#include <T_Render.h>

class Ghost:
    public T_Component{
public:
    explicit Ghost(T_GameObject& gameObject, int spawnR, int noSpawnR) :T_Component(gameObject),spawnR(spawnR),noSpawnR(noSpawnR) {}
    int spawnR;
    int noSpawnR;
    int tick = 0;
    shared_ptr<Sprite> sprite;
    string GetComponentName()override;
    int BeHit();
    void Update()override;
    void Start()override;

};
