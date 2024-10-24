#include "PathAgent.h"
#include "raylib.h"

void PathAgent::Update(float dt)
{
	//If path is empty return
	if (path.empty()) return;

	//Calculate the distance to the next node and the unit vector to that node'
	glm::vec2 nodePos = path.front()->position;

	//float dist = (position.x - nodePos.x) + (position.y - nodePos.y);
	/*if (dist < 0) {
		dist *= -1;
	}*/

	float dist = (position.x +position.y) - (nodePos.x+nodePos.y);

	if (dist < 0) {
		dist *= -1; // make the number positive
	}

	if (dist == 0 || dist < 1) {
		position = nodePos;
		currentNode = path.front();
		path.erase(path.begin());
		return;
	}

	glm::vec2 moveAxis;
	if (position.x != nodePos.x) { // moving on X axis
		if (position.x > nodePos.x)
			moveAxis = { -1,0 };
		else
			moveAxis = { 1,0 };
	}
	else if (position.y != nodePos.y) {// moving on Y axis
		if (position.y > nodePos.y)
			moveAxis = { 0,-1 };
		else
			moveAxis = { 0,1 };
	}

	//Subtract speed * deltaTime from the distance(how much we’re going to move this frame)
	dist -= speed * dt;

	position += speed * dt * moveAxis;


	//OLD CODE
	//std::cout << "Path Size: " << path.size() << std::endl;
	//std::cout << "Distance is 0, switching to next node\n";
	//position = nodePos;
	//currentNode = path.front();
	//path.erase(path.begin());
		
	//If distance is greater than zero, then this frame we’re just moving towards the target node.Add speed* deltaTime* unit vector to our position
	//if (dist.x < 0 && dist.y < 0) {
		//position = nodePos;
		//currentNode = path.front();
		//path.erase(path.begin());
		//return;
	//}
	//position += speed * dt * moveAxis;
	//position = { (position.x) * speed * dt, (position.y) * speed * dt };
	//position = position * moveAxis;
	std::cout << "DIST: " << dist << std::endl;
	//Otherwise, we’ve overshot the node.Add one to currentIndex.If we’ve reached the end of our path, snap to the final node and empty the path so future updates do nothing.
	//If we have a next node, then distance with the subtracted speed* deltaTime tells us how far we’ve overshot the node if we invert it.Find the unit vector from our previous node to the new next node, and move along this vector by the overshoot distance from the previous next node.
}

void PathAgent::GoToNode(Node* node)
{
	path = nm->DijkstrasSearch(currentNode, node);
	currentIndex = 0;
}

void PathAgent::Draw()
{
	DrawCircle(position.x, position.y, 15, { 0,0,255,255 });
}

void PathAgent::SetNode(Node* node)
{
	currentNode = node;
	position = node->position;
}

void PathAgent::SetSpeed(float spd)
{
	speed = spd;
}

void PathAgent::SetNodeMap(NodeMap* newMap)
{
	nm = newMap;
}
