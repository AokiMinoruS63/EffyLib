/**
 * @file PhysicusWorld.cpp
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief 
 * @version 0.1
 * @date 2021-09-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "PhysicusWorld.h"
#include "../Sprite/Sprite.h"

PhysicusWorld::PhysicusWorld(){}

PhysicusWorld::~PhysicusWorld(){}

void PhysicusWorld::append(Sprite* sprite) {
	sprites.push_back(sprite);
}