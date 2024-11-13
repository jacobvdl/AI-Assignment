/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

//#define RAYGUI_IMPLEMENTATION
//#define RAYGUI_SUPPORT_ICONS
//#include "raygui.h"
#include "Pathfinding.h"
#include <list>
#include <vector>
#include "NodeMap.h"
#include "PathAgent.h"
#include "Agent.h"
#include "GoToPointBehaviour.h"
#include "WanderBehaviour.h"
#include "FollowBehaviour.h"
#include "SelectorBehaviour.h"
#include "DistanceCondition.h"
#include "FiniteStateMachine.h"
#include "ABDecision.h"
#include "ActionDecision.h"
#include "BehaviourCondition.h"

using namespace AIForGames;
void DrawPath(std::vector<Node*> path, Color lineColor) {

    for (Node* current : path) {
        if (current != nullptr && current->previous != nullptr) {
            DrawLine(current->position.x, current->position.y, current->previous->position.x, current->previous->position.y, lineColor);
        }
    }
}

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "AI For Games");

    

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------


    /*Node* a = new Node();
    a->position = glm::vec2(125.0f, 75.0f);
    Node* b = new Node();
    b->position = glm::vec2(250.0f, 75.0f);*/

    std::vector<std::string> asciiMap;
    asciiMap.push_back("00000000000000000");
    asciiMap.push_back("01011101110001100");
    asciiMap.push_back("01110111011000100");
    asciiMap.push_back("01010000001011110");
    asciiMap.push_back("01011111111010010");
    asciiMap.push_back("01000000100011110");
    asciiMap.push_back("01111111111110010");
    asciiMap.push_back("01000000010000010");
    asciiMap.push_back("01000111111111110");
    asciiMap.push_back("01000100000000010");
    asciiMap.push_back("01111111111111110");
    asciiMap.push_back("00000000000000000");

    NodeMap nm;
    nm.Initialise(asciiMap, 32);

    Node* start = nm.GetNode(1, 1);
    Node* end = nm.GetNode(10, 2);
    std::vector<Node*> nmPath = nm.AStarSearch(start, end);
    Color lineColor = { 0,255,0,255 };

    //PathAgent pagent;
    //pagent.SetNode(start);
    //pagent.SetSpeed(64);  
    //pagent.SetNodeMap(&nm);

    Agent agent(&nm, new GoToPointBehaviour());
    agent.SetNode(start);
    agent.SetSpeed(64);

    //Agent agent2(&nm, new WanderBehaviour());
    //agent2.SetNode(nm.GetRandomNode());
    //agent2.SetSpeed(64);

    FollowBehaviour* followB = new FollowBehaviour();

    ActionDecision followDec(followB);
    ActionDecision wanderDec(new WanderBehaviour());


    DistanceCondition* closerThan3 = new DistanceCondition(3.0f * nm.GetCellSize(), true);
    DistanceCondition* closerThan5 = new DistanceCondition(5.0f * nm.GetCellSize(), true);
    BehaviourCondition* isFollowing = new BehaviourCondition(followB);

    /*State* wanderState = new State(new WanderBehaviour());
    State* followState = new State(new FollowBehaviour());
    wanderState->AddTransition(closerThan3, followState);
    followState->AddTransition(closerThan5, wanderState);

    FiniteStateMachine* fsm = new FiniteStateMachine(wanderState);
    fsm->AddState(wanderState);
    fsm->AddState(followState);*/
    
    
    //Agent agent3(&nm, fsm);
    //agent3.SetNode(nm.GetRandomNode());
    //agent3.SetSpeed(32);
    //agent3.SetTarget(&agent);
    //wanderState->Enter(&agent3);
    


    

    
    ABDecision isWithin5(closerThan5, &followDec, &wanderDec);
    ABDecision isFollow(isFollowing, &isWithin5, &wanderDec);
    ABDecision isWithin3(closerThan3, &followDec, &isFollow);


    Agent agent3(&nm, new WanderBehaviour());
    agent3.SetNode(nm.GetRandomNode());
    agent3.SetSpeed(32);
    agent3.SetTarget(&agent);
    agent3.SetDecision(&isWithin3);
    

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        /*BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();*/
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(BLACK);
        nm.Draw();
        //DrawPath(pagent.path, lineColor);
        //DrawFPS(20, 20);
        //pagent.Draw();
        agent.Update(GetFrameTime());
        DrawPath(agent.GetPathAgent()->path, lineColor);
        agent.Draw();

        //agent2.Update(GetFrameTime());
        //agent2.Draw();

        agent3.Update(GetFrameTime());
        agent3.Draw();
        EndDrawing();

        //if (IsMouseButtonPressed(0)) {
        //    Vector2 mousePos = GetMousePosition();
        //    end = nm.GetClosestNode(glm::vec2(mousePos.x, mousePos.y));
        //    start = pagent.GetNode();
        //    nmPath = nm.AStarSearch(start, end);
        //    pagent.GoToNode(end);
        //}
        //pagent.Update(GetFrameTime());
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}