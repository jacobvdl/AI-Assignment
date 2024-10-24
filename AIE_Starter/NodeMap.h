#pragma once
#include <iostream>
#include "Pathfinding.h"
#include <list>

using namespace AIForGames;

class NodeMap
{
	int m_width, m_height;
	float m_cellSize;

	Node** m_nodes;

public:
	void Initialise(std::vector<std::string> asciiMap, int cellSize);
	Node* GetNode(int x, int y) { return m_nodes[x + m_width * y]; }
	Node* GetClosestNode(glm::vec2 worldPos);
	void Draw();
	std::vector<Node*> DijkstrasSearch(Node* startNode, Node* endNode);
	std::vector<Node*> AStarSearch(Node* startNode, Node* endNode);

};

