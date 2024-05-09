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
// #include "Dijk.h"
#include "Dijkstra.h"

const string PATH = "/Users/suraj/Library/CloudStorage/OneDrive-PlakshaUniversity/Classes/Sem2/PDS/project/closeNav/images/in/";
const string FILENAME = "10-10.png";


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
    grid.printGrid();

    grid.getStartNode()->printLocation();
    grid.getEndNode()->printLocation();
    
    Dijkstra search(grid);

    vector<Node*> path = search.constructPath();

    // int moves = search.solve();
    // cout << moves << endl;

    // vector<Node*> path = search.reconstructPath();
    // search.printReconstructedPath();

    writeImage(grid, path);
    
    stbi_image_free(img);

    return 0;
}
