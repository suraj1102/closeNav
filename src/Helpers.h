/**
 * @file Helpers.h
 * @brief Contains helper functions which will be used in main.cpp
*/

#include "GlobalVariables.h"

/**
 * @brief Simply print the RGB values of each pixel line by line
 * @param img pointer to image loaded in memory from stbi_load
 * @param height height of the image
 * @param width width of the image
 * @param channels number of channels in the image
 */
void printImgPixelColors(unsigned char* img, int height, int width, int channels) {
    size_t img_size = height * width * channels;
    for (unsigned char *p = img; p != img + img_size; p += channels) {
        cout << (int)p[0] << "\t";
        cout << (int)p[1] << "\t";
        cout << (int)p[2] << "\t";
        cout << endl;
    }
    return;
}

/**
 * @brief Check if a node is present in the path
 * @param path path computed from any pathfinding algorithm
 * @param i what row the node is on (node->x)
 * @param j what column the node is on (node->y)
 * @return boolean indicating if node exists in path
 */
bool findInPath(vector<Node*> path, int r, int c) {
    for (Node* node : path) {
        if (node->r == r && node->c == c) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Write the computed path to a output image
 * @param grid Grid object containing all the nodes
 * @param path path computed by algorithm
 */
void writeImage(Grid& grid, vector<Node*> path) {

    int height = grid.getHeight();
    int width = grid.getWidth();
    int channels = grid.getChannels();

    size_t imgSize = height * width * channels;

    unsigned char *out_img = (unsigned char*)malloc(imgSize);
    if(out_img == NULL) {
        printf("Unable to allocate memory for the output image.\n");
        exit(1);
    }

    int rowCount = 0, columnCount = 0;
    int num_pixels = width * height;
    Node* startNode = grid.getStartNode();
    Node* endNode = grid.getEndNode();

    for (int i = 0; i < num_pixels; i++) {
        unsigned char *p = out_img + i * channels;
        Node* currentNode = grid.getNode(rowCount, columnCount);

        // Make start node green
        if (currentNode == startNode) {
            p[0] = (uint8_t) 0;
            p[1] = (uint8_t) 255;
            p[2] = (uint8_t) 0; 
        }
        // Make end node blue
        else if (currentNode == endNode) {
            p[0] = (uint8_t) 0;
            p[1] = (uint8_t) 0;
            p[2] = (uint8_t) 255; 
        }
        // if node is in path, make it yellow
        else if (findInPath(path, rowCount, columnCount)) {
            p[0] = (uint8_t) 255;
            p[1] = (uint8_t) 255;
            p[2] = (uint8_t) 0; 
        }
        // If node is walkable, make it white
        else if (currentNode->walkable) {
            p[0] = (uint8_t) 255;
            p[1] = (uint8_t) 255;
            p[2] = (uint8_t) 255; 
        }
        // Else, if node is not walkable, make it black
        else {
            p[0] = (uint8_t) 0;
            p[1] = (uint8_t) 0;
            p[2] = (uint8_t) 0; 
        }
    
        columnCount++;
        if (columnCount >= width) {
            columnCount = 0;
            rowCount++;        
        }
    }

    stbi_write_jpg("output.jpg", width, height, channels, out_img, 100);

    return;
}
/**
 * @brief Load Image and Populate Grid
 * @param file_path from GlobalVariables.h
 * @return pointer to Grid object
 */
Grid* loadImage(char* file_path) {
    int gridWidth, gridHeight, channels;
    unsigned char *img = stbi_load(
                                   file_path,
                                   &gridWidth,
                                   &gridHeight,
                                   &channels,
                                   0
                                   );
    if(img == NULL) {
        cout << "Error in loading the image" << endl;
        exit(1);
    }
    cout << gridHeight << "x" << gridWidth << " px image loaded with " << channels << " channels." << endl;
    
    Grid* grid = new Grid(gridHeight, gridWidth);
    grid->populateGrid(img, channels);
    
    return grid;
}

void initializeRecs(vector<vector<myRectangle>>& recs, Grid* grid) {
    for (int r = 0; r < grid->getHeight(); r++) {
        for (int c = 0; c < grid->getWidth(); c++) {
            if (grid->getNode(r, c)->isSame(grid->getStartNode())) {
                recs[r][c].color = START_TILE_COLOR;
            } else if (grid->getNode(r, c)->isSame(grid->getEndNode())) {
                recs[r][c].color = END_TILE_COLOR;
            } else if (grid->getNode(r, c)->isWalkable()) {
                recs[r][c].color = WALKABLE_TILE_COLOR;
            } else {
                recs[r][c].color = UNWALKABLE_TILE_COLOR;
            }
        }
    }
}
