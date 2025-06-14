//
// Created by DexrnZacAttack on 1/2/2025.
//

#include <Color/Colors/WorldColor.h>

namespace lce::color {
    WorldColor::WorldColor(std::string name, ARGB waterColor, ARGB underwaterColor, ARGB fogColor): ColorCommons(name), waterColor(waterColor), underwaterColor(underwaterColor), fogColor(fogColor) {}

    WorldColor WorldColor::read(std::vector<uint8_t> data) {
        io::BinaryIO io((data.data()));
        const auto strLength = io.readBE<uint16_t>();
        std::string name = io.readUtf8(strLength);

        auto water = io.readBE<ARGB>();
        auto underwater = io.readBE<ARGB>();
        auto fog = io.readBE<ARGB>();

        return {name, water, underwater, fog};
    }

    WorldColor WorldColor::read(io::BinaryIO& io) {
        const auto strLength = io.readBE<uint16_t>();
        std::string name = io.readUtf8(strLength);

        auto water = io.readLE<ARGB>();
        auto underwater = io.readLE<ARGB>();
        auto fog = io.readLE<ARGB>();

        return {name, water, underwater, fog};
    }

    uint8_t *WorldColor::create() {
        io::BinaryIO io(getSize());

        io.writeBE<uint16_t>(name.size());
        io.writeUtf8(name);
        io.writeLE<ARGB>(waterColor);
        io.writeLE<ARGB>(underwaterColor);
        io.writeLE<ARGB>(fogColor);

        return io.getData();
    }

    uint32_t WorldColor::getSize() {
        uint32_t size = 0;
        size += sizeof(uint16_t);
        size += name.size();
        size += sizeof(ARGB);
        size += sizeof(ARGB);
        size += sizeof(ARGB);
        return size;
    }
} // lce::color