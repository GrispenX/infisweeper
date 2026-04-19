#include "game/ChunkFileStorage/SaveFileInspector.h"
#include <fstream>
#include <cstring>
#include <iostream>

std::unordered_map<std::filesystem::path, Header> SaveFileInspector::GetValidFiles(std::filesystem::path directory_path)
{
    std::unordered_map<std::filesystem::path, Header> files;
    if(std::filesystem::exists(directory_path) && std::filesystem::is_directory(directory_path))
    {
        for(const auto& entry : std::filesystem::directory_iterator(directory_path))
        {
            try
            {
                Header header = ReadHeader(entry.path());
                files[entry.path()] = header;
            }
            catch(std::runtime_error& e) {};
        }
    }
    return files;
}

Header SaveFileInspector::ReadHeader(std::filesystem::path file_path)
{
    if(!std::filesystem::exists(file_path)) throw std::runtime_error("File does not exist");
    if(!std::filesystem::is_regular_file(file_path)) throw std::runtime_error("Not a regular file");

    std::ifstream file(file_path, std::ios::binary);

    if(!file.is_open()) throw std::runtime_error("Can't open file");

    Header correct_header;
    Header header;

    file.seekg(0);
    file.read(reinterpret_cast<char*>(&header), sizeof(Header));
    file.close();

    if(memcmp(header.magic, correct_header.magic, sizeof(correct_header.magic))) throw std::runtime_error("Invalid magic");
    if(header.geometry_id < 1 || header.geometry_id > 2) throw std::runtime_error("Invalid geometry");

    return header;
}