#pragma once
#include "T_Engine/T_GameObject.h"
class PlayerController:
	public T_Component
{
public:
	/// <summary>
	/// 玩家行走速度
	/// </summary>
	const float v = 0.3;
	void Update() override;
};

