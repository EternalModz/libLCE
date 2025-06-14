//
// Created by DexrnZacAttack on 12/21/2024.
//

#ifndef SAVEFILECOMMONS_H
#define SAVEFILECOMMONS_H
#include <optional>
#include <string>
#include <variant>
#include <vector>
#include <IO/ByteEnums.h>
#include <libLCE.h>
#include <Filesystem/Filesystem.h>

namespace lce::save {
    class SaveFileOld;
    class SaveFile;

    enum SaveFileVersion : uint16_t {
        PR = 1,
        TU0054,
        TU5,
        TU9,
        TU14,
        TU17,
        TU19,
        TU36,
        TU69
    };

    class LIBLCE_API SaveFileCommons : public fs::Filesystem {
        protected:
        static constexpr uint32_t HEADER_SIZE = 12;
        uint16_t originalVersion;
        uint16_t version;
        ByteOrder endian;
        public:
            SaveFileCommons(): endian(ByteOrder::LITTLE), originalVersion(11), version(11) {};

            virtual ~SaveFileCommons() = default;

            uint64_t getSize() const;

            uint32_t calculateIndexOffset() const;

            [[nodiscard]] virtual uint8_t* toData() const = 0;

#ifndef __EMSCRIPTEN__
            static std::variant<SaveFile, SaveFileOld> readAuto(std::vector<uint8_t> data, ByteOrder endian = LITTLE);
#endif
            static uint16_t getVersionFromData(std::vector<uint8_t> data, ByteOrder endian = LITTLE);
            uint16_t getOriginalVersion() const;
            uint16_t getVersion() const;
            ByteOrder getEndian() const;   
            void setOriginalVersion(uint16_t version);
            void setVersion(uint16_t version);
            void setEndian(ByteOrder endian);
        protected:
        /**
         * Gets the size of an index entry based on the save file class type.
         * @return The size of an index entry
         */
        [[nodiscard]] virtual uint32_t getIndexEntrySize() const { return 0; };
    };
}


#endif //SAVEFILECOMMONS_H
