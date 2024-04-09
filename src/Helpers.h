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

bool findInPath(vector<Node*> path, int i, int j) {
    for (Node* node : path) {
        if (node->x == i && node->y == j) {
            return true;
        }
    }
    return false;
}

void outputImage(unsigned char *img, vector<Node*> path) {
    
}