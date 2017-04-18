#ifndef _BOUNDINGOBJECTMANAGER_H
#define _BOUNDINGOBJECTMANAGER_H

#include "RE\ReEng.h"
#include "MyBoundingObjectClass.h"
#include <iostream>
#include <vector>
#include <string>

#endif

class BoundingObjectManager
{
public:
	std::vector<MyBoundingObjectClass> objectList;

	static BoundingObjectManager* GetInstance() {
		if (instance == nullptr)
			instance = new BoundingObjectManager();
		return instance;
	}
	static void ReleaseInstance() {
		if (instance != nullptr) {
			delete instance;
			instance = nullptr;
		}

	}
	static void AddObject(MyBoundingObjectClass temp) {
		instance->objectList.push_back(temp);
	}

	static void SetColorAtIndex(int index, vector3 color) {
		instance->objectList[index].SetColor(color);
	}

	static void SetVisibilityAtIndex(int index, bool visible) {
		if (visible) {
			instance->objectList[index].m_iBoundingObjectType = 3;
		}
		else {
			instance->objectList[index].m_iBoundingObjectType = 2;
		}
	}


	static void RenderAtIndex(int index) {
		instance->objectList[index].RenderBO();
	}
	static void RenderAll() {
		for (int i = 0; i < instance->objectList.size(); i++) {
			instance->objectList[i].RenderBO();
		}
	}	
	
	static void CheckCollisions() {
		
		for (int i = 0; i < instance->objectList.size(); i++) {
			instance->objectList[i].SetColor(REPURPLE);
			instance->objectList[i].m_bColliding = false;
		}

		for (int i = 0; i < instance->objectList.size() - 1; i++) {
			for (int j = i + 1; j < instance->objectList.size(); j++) {
				MyBoundingObjectClass* temp = &instance->objectList[j];
				if (instance->objectList[i].IsColliding(temp)) {
					instance->objectList[i].SetColor(RERED);
					instance->objectList[j].SetColor(RERED);
					instance->objectList[i].m_bColliding = true;
					instance->objectList[j].m_bColliding = true;
				}
			}
		}
	}

private:
	static BoundingObjectManager* instance;
	BoundingObjectManager() {};
	~BoundingObjectManager() {};
};
