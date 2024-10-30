#pragma once
#include <list>
#include <vector>
#include <glm/glm.hpp>
#include "NodeMap.h"
#include "raylib.h"
class PathAgent
{
private:
	glm::vec2 position = { 0,0 };

	
	int currentIndex;
	Node* currentNode;
	NodeMap* nm;

	float speed;
	Node* startingNode;

public:
	std::vector<Node*> path;
	void Update(float dt);
	void GoToNode(Node* node);
	void Draw(Color clr);
	void SetNode(Node* node);
	void SetSpeed(float spd);
	void SetNodeMap(NodeMap* newMap);
	Node* GetNode() { return currentNode; }
	glm::vec2 GetPosition() { return position; }
};

