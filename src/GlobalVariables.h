#ifndef GlobalVariables_h
#define GlobalVariables_h

// File Path of Input Image:
char* FILE_PATH = (char *)"/Users/suraj/Documents/Coding/FM131ProjectTest/FM131ProjectTest/images/in/10-10.png";

// Declare myRectangle as Rectangle object in Raylib does not
// have a color attribute
class myRectangle: public Rectangle {
public:
    Color color;
};


// DECLARE CONSTANTS FOR RENDERING
const int screenWidth = 1000;
const int screenHeight = 1000;

Color WALKABLE_TILE_COLOR = BLACK;
Color UNWALKABLE_TILE_COLOR = GRAY;
Color START_TILE_COLOR = GREEN;
Color END_TILE_COLOR = BLUE;
Color BFS_PATH_COLOR = PINK;
Color DFS_PATH_COLOR = BROWN;
Color DJK_PATH_COLOR = LIME;
Color ASTAR_PATH_COLOR = SKYBLUE;

#endif /* GlobalVariables_h */