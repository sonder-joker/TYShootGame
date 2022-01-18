#pragma once

#include "T_GameObject.h"

class PlayerLogic : public T_Component {
public:
    explicit PlayerLogic(T_GameObject &gameObject) : T_Component(gameObject) {}

    void Update() override;

    int kill = 0;
};

