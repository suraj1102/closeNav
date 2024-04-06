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