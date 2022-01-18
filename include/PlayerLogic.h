//
// Created by yang on 2022/1/18.
//

#ifndef TYSHOOTGAME_PLAYERLOGIC_H
#define TYSHOOTGAME_PLAYERLOGIC_H

#include "T_GameObject.h"


class PlayerLogic:public T_Component {
public:
    explicit PlayerLogic(T_GameObject& gameObject) :T_Component(gameObject) {}
    void Update()override;
    int kill = 0;
};


#endif //TYSHOOTGAME_PLAYERLOGIC_H
