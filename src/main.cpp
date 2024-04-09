#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb/stb_image_write.h"

#include "Node.h"
#include "Grid.h"
#include "BFS.h"
#include "Helpers.h"

const string PATH = "/Users/suraj/Documents/Coding/forUni/final/Path-Finder/assets/";
const string FILENAME = "50-50.png";

int main(void)
{
    int width, height, channels;
    unsigned char *img = stbi_load((PATH + FILENAME).c_str(), &width, &height, &channels, 0);
    if(img == NULL) {
        cout << "Error in loading the image" << endl;
        exit(1);
    }
    cout << height << "x" << width << " px image loaded with " << channels << " channels." << endl;

    size_t img_size = height * width * channels;

    Grid grid(height, width);

    grid.populateGrid(img, channels);

    // printImgPixelColors(img, height, width, channels);

    // grid.printGrid();

    grid.getStartNode()->printLocation();
    grid.getEndNode()->printLocation();
    
    BFS search(grid);
    int moves = search.solve();
    cout << moves << endl;

    vector<Node*> path = search.reconstructPath();
    search.printReconstructedPath();

    unsigned char *out_img = (unsigned char*)malloc(img_size);
    if(out_img == NULL) {
        printf("Unable to allocate memory for the output image.\n");
        exit(1);
    }

    int columnCount = 0, rowCount = 0;
    int num_pixels = width * height;
    Node* startNode = grid.getStartNode();
    Node* endNode = grid.getEndNode();

    for (int i = 0; i < num_pixels; i++) {
        unsigned char *p = out_img + i * channels;
        Node* currentNode = grid.getNode(rowCount, columnCount);

        if (currentNode == startNode) {
            p[0] = (uint8_t) 0;
            p[1] = (uint8_t) 255;
            p[2] = (uint8_t) 0; 
        }
        else if (currentNode == endNode) {
            p[0] = (uint8_t) 0;
            p[1] = (uint8_t) 0;
            p[2] = (uint8_t) 255; 
        }
        else if (findInPath(path, rowCount, columnCount)) {
            p[0] = (uint8_t) 255;
            p[1] = (uint8_t) 255;
            p[2] = (uint8_t) 0; 
        }
        else if (currentNode->walkable) {
            p[0] = (uint8_t) 255;
            p[1] = (uint8_t) 255;
            p[2] = (uint8_t) 255; 
        }
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
    
    stbi_image_free(img);

    return 0;
}
