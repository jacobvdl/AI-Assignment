#include "NodeMap.h"
#include <glm/glm.hpp>
#include <iostream>
#include <list>
#include "raylib.h"

void NodeMap::Initialise(std::vector<std::string> asciiMap, int cellSize)
{
	m_cellSize = cellSize;
	const char emptySqr = '0';

	m_height = asciiMap.size();
	m_width = asciiMap[0].size();

	m_nodes = new Node * [m_width * m_height];

	for (int y = 0; y < m_height; y++) {
		std::string& line = asciiMap[y];
		if (line.size() != m_width)
			std::cout << "Mismatched line #" << y << " in ASCII map (" << line.size() << " instead of " << m_width << ")\n";

		for (int x = 0; x < m_width; x++) {
			char tile = x < line.size() ? line[x] : emptySqr;

			m_nodes[x + m_width * y] = tile == emptySqr ? nullptr
				: new Node(((float)x + 0.5f) * m_cellSize, ((float)y + 0.5f) * m_cellSize);
		}
	}

	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			Node* node = GetNode(x, y);
			if (node) {
				Node* nodeWest = x == 0 ? nullptr : GetNode(x - 1, y);
				if(nodeWest) {
					std::cout << "connection\n";
					node->ConnectTo(nodeWest, 1);
					nodeWest->ConnectTo(node, 1);
				}

				Node* nodeSouth = y == 0 ? nullptr : GetNode(x, y - 1);
				if (nodeSouth) {
					std::cout << "connection\n";
					node->ConnectTo(nodeSouth, 1);
					nodeSouth->ConnectTo(node, 1);
				}
			}
		}
	}
}

void NodeMap::Draw()
{
	Color cellColor;
	cellColor.a = 255;
	cellColor.r = 255;
	cellColor.g = 0;
	cellColor.b = 0;

	Color lineColor;
	lineColor.a = 255;
	lineColor.r = 0;
	lineColor.g = 255;
	lineColor.b = 0;

	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			Node* node = GetNode(x, y);
			if (node == nullptr) {
				DrawRectangle((int)(x * m_cellSize), (int)(y * m_cellSize),
					(int)m_cellSize - 1, (int)m_cellSize - 1, cellColor);
			}
			else {
				for (int i = 0; i < node->connections.size(); i++) {
					Node* other = node->connections[i].target;
					DrawLine((x + .5f) * m_cellSize, (y + .5f) * m_cellSize,
						(int)other->position.x, (int)other->position.y,
						lineColor);
				}
			}
		}
	}
}

bool comparegScore(Node* node1, Node* node2) {
	if (node1->gScore < node2->gScore)
		return true;
}

std::list<Node*> NodeMap::DijkstrasSearch(Node* startNode, Node* endNode) //
{
	if (startNode == nullptr || endNode == nullptr) //
		throw; //
	if (startNode == endNode) //
		return std::list<Node*>(); //
	startNode->gScore = 0; //
	startNode->previous = nullptr; //

	std::list<Node*> openList; //
	std::list<Node*> closedList; //

	openList.push_back(startNode); //
	

	while (openList.size() != 0) { //
		openList.sort(comparegScore); // need to test this
		//std::cout << "AAAA\n";
		Node* currentNode = openList.front(); //

		if (currentNode == endNode)  //
			break; //
		
		
		openList.remove(currentNode); //
		closedList.push_back(currentNode); //


		Edge* c = &currentNode->connections.front(); //
		std::cout << "CONNECTIONS: " << currentNode->connections.size() << std::endl;
		for (int i = 0; i <= currentNode->connections.size(); i++) {
			std::cout << "AAAA\n";
			
			Node* checkingNode;
			bool isInClosed = true;
			if (closedList.size() != 0) {
				checkingNode = closedList.front();
				for (int a = 0; a < closedList.size(); a++) {
					for (int b = 0; b < currentNode->connections.size(); b++) {
						if (currentNode != c->target) {
							isInClosed = false;
							std::cout << "ITS NOT CLOSED\n";
							break;
						}
						if (b != currentNode->connections.size())
							c = std::next(c);
					}
					if (a != closedList.size())
						checkingNode = std::next(checkingNode);
				}
			}
			

			if (isInClosed == false) {
				std::cout << "IS THIS RUNNING\n";
				int gScore = currentNode->gScore + c->cost;
				bool isInOpen = false;
				if (openList.size() != 0) {
					checkingNode = openList.front();
					for (int a = 0; a < openList.size(); a++) {
						if (checkingNode == c->target) {
							isInOpen = true;
							std::cout << "IS IN OPEN\n";
						}
						if (a != openList.size())
							checkingNode = std::next(checkingNode);
					}
				}

				if (!isInOpen) {
					std::cout << "THIS SHOULD RUN\n";
					c->target->gScore = gScore;
					c->target->previous = currentNode;
					openList.push_back(c->target);
				}
				else if (currentNode->gScore < c->target->gScore) {
					std::cout << "TEST\n";
					c->target->gScore = gScore;
					c->target->previous = currentNode;
				}

			}
			

			//if (i != currentNode->connections.size())
				//checkingNode = std::next(checkingNode);
		}

		std::list<Node*> path;
		currentNode = endNode;
		std::cout << "test\n";
		if (currentNode == nullptr)
			std::cout << "CURRENT NULL\n";
		while (currentNode != nullptr) {
			std::cout << "test\n";
			path.push_front(currentNode);
			std::cout << "test\n";
			std::cout << "CURRENT: " << currentNode->gScore;
			if (currentNode->previous == nullptr)
				break;
			
			std::cout << " PREVIOUS: " << currentNode->previous->gScore << std::endl;
			currentNode = currentNode->previous;
			std::cout << "WORKED\n";
		}

		return path;
		
	}
}
