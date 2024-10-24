#pragma once
#include <list>
#include <vector>
#include <glm/glm.hpp>
#include "NodeMap.h"
class PathAgent
{
private:
	glm::vec2 position;

	std::vector<Node*> path;
	int currentIndex;
	Node* currentNode;
	NodeMap* nm;

	float speed;

public:
	void Update(float dt);
	void GoToNode(Node* node);
	void Draw();
	void SetNode(Node* node);
	void SetSpeed(float spd);
	void SetNodeMap(NodeMap* newMap);
	Node* GetNode() { return currentNode; }
};

