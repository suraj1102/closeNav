#include <iostream>
#include <vector>
using namespace std;

#include "raylib.h"
#include "GlobalVariables.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb/stb_image_write.h"

#include "Node.h"
#include "Grid.h"
#include "Helpers.h"
#include "BFS.h"
#include "DFS.h"
#include "Dijkstra.h"
#include "AStar.h"


int main(void) {
    
    // Load Image and create grid
    Grid* grid = loadImage(FILE_PATH);
    
    int gridHeight = grid->getHeight();
    int gridWidth = grid->getWidth();
    
    grid->printGrid();
    
    
    
/*-------------------------------------------------------------------------------------------------------------*/
    
    
    
    // Constant variables used below are imported from GlobalVariables
    
    InitWindow(screenWidth, screenHeight, "CloseNav");
    SetTargetFPS(60);
    
    // DrawRectangle(int posX, int posY, int width, int height, Color color);
    float TILE_WIDTH = (float)screenWidth / gridWidth;
    float TILE_HEIGHT = (float)screenHeight / gridHeight;
    
    vector<vector<myRectangle> > recs;
    recs.resize(gridHeight);
    for (int r = 0; r < gridHeight; r++) {
        recs[r].resize(gridWidth);
    }
    
    for (int r = 0; r < gridHeight; r++) {
        for (int c = 0; c < gridWidth; c++) {
            
            recs[r][c].width = TILE_WIDTH;
            recs[r][c].height = TILE_HEIGHT;
            recs[r][c].x = c * TILE_WIDTH;
            recs[r][c].y = r * TILE_HEIGHT;
            
            initializeRecs(recs, grid);
        }
    }

    
    bool isPathDone = false; // To not allow change of wall / not wall when path is displayed
    bool initialized = false; // To see if initialize image grid has been changed

    
    while (!WindowShouldClose()) {
        
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && isPathDone == false) {
            Vector2 mousePosiiton = GetMousePosition();
            int c = mousePosiiton.x / TILE_WIDTH;
            int r = mousePosiiton.y / TILE_HEIGHT;
            if (ColorToInt(recs[r][c].color) != ColorToInt(UNWALKABLE_TILE_COLOR)) {
                recs[r][c].color = UNWALKABLE_TILE_COLOR;
                grid->getNode(r, c)->walkable = false;
            }
            else {
                recs[r][c].color = WALKABLE_TILE_COLOR;
                grid->getNode(r, c)->walkable = true;
            }
        }
                
        BeginDrawing();
        
        ClearBackground(BLACK);
        
        if (initialized == false) {
            initialized = true;
            for (int r = 0; r < gridHeight; r++) {
                for (int c = 0; c < gridWidth; c++) {
                    initializeRecs(recs, grid);
                    DrawRectangleRec(recs[r][c], recs[r][c].color);
                    DrawRectangleLinesEx(recs[r][c], 0.4, WHITE);
                }
            }
        } 
        else {
            for (int r = 0; r < gridHeight; r++) {
                for (int c = 0; c < gridWidth; c++) {
                    DrawRectangleRec(recs[r][c], recs[r][c].color);
                    DrawRectangleLinesEx(recs[r][c], 0.4, WHITE);
                }
            }
        }
        
        if (IsKeyPressed(KEY_D)) {
            isPathDone = true;
            
            DFS search(*grid);
            int moves = search.solve();
            cout << moves << endl;
            
            vector<Node*> path = search.reconstructPath();
            search.printReconstructedPath();
            
            for (int i = 1; i < path.size() - 1; i++) {
                recs[path[i]->r][path[i]->c].color = DFS_PATH_COLOR;
            }
        }
        
        if (IsKeyPressed(KEY_B)) {
            isPathDone = true;
            
            BFS search(*grid);
            int moves = search.solve();
            cout << moves << endl;
            
            vector<Node*> path = search.reconstructPath();
            search.printReconstructedPath();
            
            for (int i = 1; i < path.size() - 1; i++) {
                recs[path[i]->r][path[i]->c].color = BFS_PATH_COLOR;
            }

            writeImage(*grid, path);
        }
        
        if (IsKeyPressed(KEY_J)) {
            isPathDone = true;
            
            Dijkstra search(*grid);
            vector<Node*> path = search.constructPath();
            
            for (int i = 1; i < path.size() - 1; i++) {
                recs[path[i]->r][path[i]->c].color = DJK_PATH_COLOR;
            }
        }

        if (IsKeyPressed(KEY_A)) {
            isPathDone = true;
            
            AStar search(*grid);
            vector<Node*> path = search.findPath();
            
            for (int i = 1; i < path.size() - 1; i++) {
                recs[path[i]->r][path[i]->c].color = ASTAR_PATH_COLOR;
            }
        }
        
        if (IsKeyPressed(KEY_R)) {
            initializeRecs(recs, grid);
            initialized = false;
            isPathDone = false;
            cout << "RESET" << endl;
        }
        
        
        if (IsKeyPressed(KEY_I)) {
            initialized = false;
            isPathDone = false;
            delete grid;
            
            grid = loadImage(FILE_PATH);
            initializeRecs(recs, grid);
            cout << "HARD RESET" << endl;
        }
        
        if (IsKeyPressed(KEY_P)) {
            grid->printGrid();
            cout << endl;
        }
        EndDrawing();
    }

    CloseWindow();
    delete grid; // Grid was dynamically allocated in LoadImage
    return 0;
}

/// Usage:
/// Left Mouse Click: change node walkable parameter
/// R: restart - removes computed path from map
/// I: initialize - restores map to the input image
/// P: print - print grid for debugging purposes
/// B: BFS
/// D: DFS
/// J: DIJKSTRA
