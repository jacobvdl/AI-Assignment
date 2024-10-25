#include "GoToPointBehaviour.h"
#include "raylib.h"


void GoToPointBehaviour::Update(Agent* agent, float dt)
{
	if (IsMouseButtonPressed(0)) {
		Vector2 mousePos = GetMousePosition();
		agent->GoTo(glm::vec2(mousePos.x, mousePos.y));
	}
}
