#include <string>
#include "draw.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <file_name> [-z <zoom>]" << std::endl;
        return 1;
    }

    std::string file_name = std::string(argv[1]);

    float zoom = 4.0f;
    int x_offset = 0.0f, y_offset = 0.0f;

    for (int i = 0; i < argc; i++) {
        if (std::string(argv[i]) == "-z") {
            zoom = std::stof(argv[i + 1]);
        }
    }
    
    draw(file_name, zoom, x_offset, y_offset);
}