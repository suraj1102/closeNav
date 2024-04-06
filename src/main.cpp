#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

#include "Node.h"
#include "Grid.h"
#include "BFS.h"
#include "Helpers.h"

const string PATH = "/Users/suraj/Documents/Coding/forUni/final/Path-Finder/assets/";
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

    // grid.printGrid();

    grid.getStartNode()->printLocation();
    grid.getEndNode()->printLocation();
    
    BFS search(grid);
    int moves = search.solve();
    cout << moves << endl;

    search.printReconstructedPath();
    
    
    stbi_image_free(img);
    return 0;
}
