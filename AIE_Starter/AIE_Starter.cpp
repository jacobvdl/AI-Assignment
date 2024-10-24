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

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------


    /*Node* a = new Node();
    a->position = glm::vec2(125.0f, 75.0f);
    Node* b = new Node();
    b->position = glm::vec2(250.0f, 75.0f);*/

    std::vector<std::string> asciiMap;
    asciiMap.push_back("000000000000");
    asciiMap.push_back("010111011100");
    asciiMap.push_back("010101110110");
    asciiMap.push_back("010100000000");
    asciiMap.push_back("010111111110");
    asciiMap.push_back("010000001000");
    asciiMap.push_back("011111111110");
    asciiMap.push_back("000000000000");

    NodeMap nm;
    nm.Initialise(asciiMap, 32);

    Node* start = nm.GetNode(1, 1);
    Node* end = nm.GetNode(10, 2);
    std::vector<Node*> nmPath = nm.DijkstrasSearch(start, end);
    Color lineColor = { 0,255,0,255 };

    PathAgent agent;
    agent.SetNode(start);
    agent.SetSpeed(64);  
    agent.SetNodeMap(&nm);

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
        DrawPath(nmPath, lineColor);
        //DrawFPS(20, 20);
        agent.Draw();
        EndDrawing();

        if (IsMouseButtonPressed(0)) {
            Vector2 mousePos = GetMousePosition();
            end = nm.GetClosestNode(glm::vec2(mousePos.x, mousePos.y));
            start = agent.GetNode();
            nmPath = nm.DijkstrasSearch(start, end);
            agent.GoToNode(end);
        }
        agent.Update(GetFrameTime());
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}