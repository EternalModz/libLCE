//
// Created by DexrnZacAttack on 1/2/2025.
//

#ifndef COLOR_H
#define COLOR_H
#include <string>
#include <vector>

#include <Color/Colors/ColorCommons.h>
#include <IO/BinaryIO.h>

namespace lce::color {

struct ARGB {
    uint8_t a;
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class LIBLCE_API Color : public ColorCommons {
    public:
    ARGB color;

    Color(std::string name, ARGB color);
    static Color read(std::vector<uint8_t> data);

    static Color read(io::BinaryIO &io);
    uint8_t *create();
    uint32_t getSize() override;
};

} // lce::color

#endif //COLOR_H
