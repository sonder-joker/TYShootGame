//
// Created by yang on 2022/1/18.
//
#include <Ghost.h>

string Ghost::GetComponentName()
{
	return "Ghost";
}

int Ghost::BeHit()
{
	if (tick > 0) return 0;
	tick = 5;
	sprite->graphIndex = 54;
	return 1;
}

void Ghost::Update() {
	if (tick == 0) {
		gameObject.transform.position.x = (noSpawnR + rand() % (spawnR - noSpawnR)) * (rand() % 2 == 0 ? 1 : -1);
		gameObject.transform.position.z = (noSpawnR + rand() % (spawnR - noSpawnR)) * (rand() % 2 == 0 ? 1 : -1);
		tick = -1;
		sprite->graphIndex = 51;
	}
	else if(tick>0) {
		tick -= 1;
	}
}

void Ghost::Start()
{
	for (auto& component : gameObject.componentArray) {
		if ( component->GetComponentName() == "Sprite") {
			sprite = dynamic_pointer_cast<Sprite>(component);
			break;
		}
	}
	BeHit();
}

