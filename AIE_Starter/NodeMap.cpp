#include "NodeMap.h"
#include <glm/glm.hpp>
#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
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
					//std::cout << "connection\n";
					node->ConnectTo(nodeWest, 1);
					nodeWest->ConnectTo(node, 1);
				}

				Node* nodeSouth = y == 0 ? nullptr : GetNode(x, y - 1);
				if (nodeSouth) {
					//std::cout << "connection\n";
					node->ConnectTo(nodeSouth, 1);
					nodeSouth->ConnectTo(node, 1);
				}
			}
		}
	}
}

Node* NodeMap::GetClosestNode(glm::vec2 worldPos)
{
	int i = (int)(worldPos.x / m_cellSize);
	if (i < 0 || i >= m_width) return nullptr;
	int j = (int)(worldPos.y / m_cellSize);
	if (j < 0 || j >= m_height) return nullptr;

	return GetNode(i, j);
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
	lineColor.r = 255;
	lineColor.g = 255;
	lineColor.b = 255;

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
	return node1->gScore < node2->gScore;
}

std::vector<Node*> NodeMap::DijkstrasSearch(Node* startNode, Node* endNode) //
{
	// if startNode is null OR endNode is null
	if (startNode == nullptr || endNode == nullptr) 
		// Raise Error
		return std::vector<Node*>();
	// if startNode == endNode
	if (startNode == endNode) 
		// return empty Path
		return std::vector<Node*>();

	// Set startNode.gScore to 0
	startNode->gScore = 0;
	// Set startNode.previous to null
	startNode->previous = nullptr;

	// Let openList be a List of Nodes
	std::vector<Node*> openList; 
	// Let closedList be a List of Nodes
	std::vector<Node*> closedList; 
	
	// Add startNode to openList
	openList.push_back(startNode);
	
	// While openList is not empty
	while (openList.size() != 0) {
		// Sort openList by Node.gScore



		//std::sort(openList.begin(), openList.end(), [](Node* a, Node* b)
		//	{
		//		return a->gScore < b->gScore;
		//	}
		//); // need to test this

		std::sort(openList.begin(), openList.end(), comparegScore); // need to test this





		// Let currentNode = first item in openList
		Node* currentNode = openList.front();

		// If currentNode is endNode
		if (currentNode == endNode)
			// Exit While Loop
			break;

		// Remove currentNode from openList
		openList.erase(openList.begin());
		// Add currentNode to closedList
		closedList.push_back(currentNode);


		// For all connections c in currentNode
		for (Edge& c : currentNode->connections) {
			//If c.target not in closedList
			/*bool isClosed = false;
			for (Node* closedNode : closedList) {
				if (c.target == closedNode)
					isClosed = true;
			}*/

			if (std::find(closedList.begin(), closedList.end(), c.target) == closedList.end())
			{
				//Let gScore = currentNode.gScore + c.cost
				float gScore = currentNode->gScore + c.cost;

				////If c.target not in openList
				//bool isOpen = false;
				//for (Node* openedNode : openList) {
				//	if (c.target == openedNode)
				//		isOpen = true;
				//}

				if (std::find(openList.begin(), openList.end(), c.target) == openList.end())
				{
					//Set c.target.gScore = gScore
					c.target->gScore = gScore;
					//Set c.target.previous = currentNode
					c.target->previous = currentNode;
					//Add c.target to openList
					openList.push_back(c.target);
				}
				//Else if (gScore < c.target.gScore)
				else if (gScore < c.target->gScore) {
					//Set c.target.gScore = gScore
					c.target->gScore = gScore;
					//Set c.target.previous = currentNode
					c.target->previous = currentNode;
				}
			}


		}
	}

	// Create Path in reverse from endNode to startNode
	//Let Path be a list of Nodes
	std::vector<Node*> Path;
	//Let currentNode = endNode
	Node* currentNode = endNode;

	//While currentNode is not null
	while (currentNode != nullptr) {
		//Add currentNode to beginning of Path
		Path.insert(Path.begin(), currentNode);
		//Set currentNode = currentNode.previous
		currentNode = currentNode->previous;
	}
		
	// DEBUGGING
	/*for (Node* debugnode : Path) {
		std::cout << "NODE IN PATH\n";
	}*/

	// Return the path for navigation between startNode/endNode
	//Return Path
	return Path;
	
}

bool comparefScore(Node* node1, Node* node2) {
	return node1->fScore < node2->fScore;
}

float Heuristic(Node* target, Node* endNode) {
	 
}

std::vector<Node*> NodeMap::AStarSearch(Node* startNode, Node* endNode)
{
	return std::vector<Node*>();

	// if startNode is null OR endNode is null
	if (startNode == nullptr || endNode == nullptr)
		// Raise Error
		return std::vector<Node*>();
	// if startNode == endNode
	if (startNode == endNode)
		// return empty Path
		return std::vector<Node*>();

	// Initialise the starting node
	//Set startNode.gScore to 0
	startNode->gScore = 0;
	//Set startNode.parent to null
	startNode->parent = nullptr;

	// Create our temporary lists for storing nodes we’re visiting/visited
	//Let openList be a List of Nodes
	std::vector<Node*> openList;
	//Let closedList be a List of Nodes
	std::vector<Node*> closedList;

	//Add startNode to openList
	openList.push_back(startNode);

	//While openList is not empty
	while (openList.size() != 0) {
		//Sort openList by Node.fScore
		std::sort(openList.begin(), openList.end(), comparefScore);

		//Let currentNode = first item in openList
		Node* currentNode = openList.front();

		// If we visit the endNode, then we can exit early.
		// Sorting the openList guarantees the shortest path is found,
		// given no negative costs (a prerequisite of the algorithm).
		//If currentNode is endNode
		if (currentNode == endNode)
			//Exit While Loop
			break;

		//Remove currentNode from openList
		openList.erase(openList.begin());
		//Add currentNode to closedList
		closedList.push_back(currentNode);

		//For all connections c in currentNode
		for (Edge& c : currentNode->connections) {
			//If c.target not in closedList
			if (std::find(closedList.begin(), closedList.end(), c.target) == closedList.end()) {
				//Let gScore = currentNode.gScore + c.cost
				float gScore = currentNode->gScore + c.cost;
				//Let hScore = Heuristic(c.target, endNode)
				float hScore = Heuristic(c.target, endNode);
				//Let fScore = gScore + hScore
				float fScore = gScore + hScore;

				// Have not yet visited the node.
				// So calculate the Score and update its parent.
				// Also add it to the openList for processing.
				//If c.target not in openList
				if (std::find(openList.begin(), openList.end(), c.target) == openList.end()) {
					//Let c.target.gScore = gScore
					c.target->gScore = gScore;
					//Let c.target.fScore = fScore
					c.target->fScore = fScore;
					//Let c.target.parent = currentNode
					c.target->parent = currentNode;
					//Add c.target to openList
					openList.push_back(c.target);
				}

				// Node is already in the openList with a valid Score.
				// So compare the calculated Score with the existing
				// to find the shorter path.
				//Else if (fScore < c.target.fScore)
				else if (fScore < c.target->fScore){
					//Let c.target.gScore = gScore
					c.target->gScore = gScore;
					//Let c.target.fScore = fScore
					c.target->fScore = fScore;
					//Let c.target.parent = currentNode
					c.target->parent = currentNode;
				}
			}
		}
	}
	// Create Path in reverse from endNode to startNode
	//Let Path be a list of Nodes
	std::vector<Node*> Path;
	//Let currentNode = endNode
	Node* currentNode = endNode;

	//While currentNode is not null
	while (currentNode != nullptr) {
		//Add currentNode to beginning of Path
		Path.insert(Path.begin(), currentNode);
		//Let currentNode = currentNode.parent
		currentNode = currentNode->parent;
	}

	// Return the path for navigation between startNode/endNode
	//Return Path
	return Path;
}
