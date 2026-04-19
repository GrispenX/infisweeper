#ifndef INCLUDE_GAME_CHUNKFILESTORAGE_SAVEFILEINSPECTOR_H_
#define INCLUDE_GAME_CHUNKFILESTORAGE_SAVEFILEINSPECTOR_H_

#include "game/ChunkFileStorage/Header.h"
#include <filesystem>
#include <unordered_map>

class SaveFileInspector
{
public:
    std::unordered_map<std::filesystem::path, Header> GetValidFiles(std::filesystem::path directory_path);
    Header ReadHeader(std::filesystem::path file_path);
};

#endif // INCLUDE_GAME_CHUNKFILESTORAGE_SAVEFILEINSPECTOR_H_