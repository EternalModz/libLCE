cmake_minimum_required(VERSION 3.26)
project(libLCE)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DCOMPILER_NAME="${CMAKE_CXX_COMPILER_ID}")
add_definitions(-DPLATFORM_NAME="${CMAKE_SYSTEM_NAME}")
add_definitions(-DPLATFORM_ARCH="${CMAKE_SYSTEM_PROCESSOR}")

message(STATUS "${CMAKE_SYSTEM_PROCESSOR}")

include_directories(include external)

# because _DEBUG is not universal
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DCMAKE_BUILD_DEBUG)
endif()

include_directories(external/emsdk/upstream/emscripten/system/include)
link_directories(external/emsdk/upstream/emscripten/system/lib)

#set(ZLIB_LIBRARY ${CMAKE_CURRENT_BINARY_DIR}/external/zlib)
#set(ZLIB_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/zlib)

set(LODEPNG_FILES
    external/lodepng/lodepng.h
    external/lodepng/lodepng.cpp
    external/lodepng/lodepng_util.h
    external/lodepng/lodepng_util.cpp)

set(ZLIB_FILES
	external/zlib/zlib.h
	external/zlib/inflate.h
	external/zlib/inflate.c
	external/zlib/adler32.c
	external/zlib/crc32.c
	external/zlib/zutil.c
	external/zlib/inffast.c
	external/zlib/inftrees.c
)

set(HEADERS
		include/libLCE.h
		include/libLCEExports.h
		include/World/Region.h
		include/World/Chunk.h
		include/Save/SaveFile.h
		include/IO/BinaryIO.h
		include/Filesystem/Filesystem.h
		include/Filesystem/File.h
		include/Archive/Archive.h
		include/Color/Colors/Color.h
		include/Color/ColorFileOld.h
		include/Color/ColorFileCommons.h
		include/Color/ColorFile.h
		include/Color/Colors/ColorCommons.h
		include/Color/Colors/WorldColor.h
		include/Localization/LocalizationFile.h
		include/Localization/Language.h
		include/Soundbank/Soundbank.h
		include/Save/SaveFileOld.h
		include/Save/SaveFileCommons.h
		include/Compression/Compression.h
		include/IO/ByteEnums.h
		include/Save/Thumb.h
		include/World/SplitSave.h
		include/World/Block.h
		include/Filesystem/FSObject.h
		include/Filesystem/Directory.h
)

set(FILES
	src/libLCEExports.cpp
	src/EmscriptenBindings.cpp
	src/World/Region.cpp
	src/World/Chunk.cpp
	src/Save/SaveFile.cpp
	src/IO/BinaryIO.cpp
	src/Filesystem/Filesystem.cpp
	src/Archive/Archive.cpp
	src/Color/Colors/Color.cpp
	src/Color/ColorFileOld.cpp
	src/Color/ColorFileCommons.cpp
	src/Color/ColorFile.cpp
	src/Color/Colors/ColorCommons.cpp
	src/Color/Colors/WorldColor.cpp
	src/Localization/LocalizationFile.cpp
	src/Localization/Language.cpp
	src/Soundbank/Soundbank.cpp
	src/Save/SaveFileOld.cpp
	src/Save/SaveFileCommons.cpp
	src/IO/BinaryString.cpp
	src/Compression/Compression.cpp
	src/Save/Thumb.cpp
	src/World/SplitSave.cpp
	src/World/Block.cpp
	src/World/Chunk/V12.cpp
	src/Filesystem/FSObject.cpp
	src/Filesystem/Directory.cpp
)

if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    set(ENVIRONMENT_TYPE "Emscripten")
    # weird?
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -sNO_DISABLE_EXCEPTION_CATCHING -s USE_ZLIB=1 -s WASM_BIGINT -s MODULARIZE=1 -sEXPORT_ES6=1 -s EXPORT_ALL=1 -s EXPORTED_RUNTIME_METHODS=['ccall','cwrap','getValue','setValue'] -s EXPORTED_FUNCTIONS=['_malloc'] -s ALLOW_MEMORY_GROWTH=1")
    add_executable(libLCE ${HEADERS} ${FILES} ${LODEPNG_FILES})
#    target_link_options(libLCE PRIVATE --emit-tsd libLCE.d.ts)
else ()
    set(ENVIRONMENT_TYPE "Native")
    set(LIB_TYPE SHARED)
    add_library(libLCE ${LIB_TYPE} ${HEADERS} ${FILES} ${LODEPNG_FILES} ${ZLIB_FILES})

    target_compile_definitions(libLCE PRIVATE LIBLCE_EXPORTS)

    add_executable(tests tests.cpp)

    target_link_libraries(tests PRIVATE libLCE)

endif ()

# me: "why don't we use c++20 for std::endian?"
# them: "c++20 is in my nightmares"

#set endianness define
if (CMAKE_CXX_BYTE_ORDER EQUAL BIG_ENDIAN)
    target_compile_definitions(libLCE PRIVATE BR_BIG_ENDIAN)
endif ()
