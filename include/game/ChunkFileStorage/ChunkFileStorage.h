#ifndef INCLUDE_GAME_CHUNKFILESTORAGE_H_
#define INCLUDE_GAME_CHUNKFILESTORAGE_H_

#include "game/IChunkStorage.h"
#include "game/IChunkFactory.h"
#include "game/Cell.h"
#include "game/ChunkFileStorage/Header.h"
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <cstring>

template<Geometry T>
class ChunkFileStorage : public IChunkStorage<T>
{
public:
    using ChunkPosition = typename T::ChunkPosition;
    using CellPosition = typename T::CellPosition;

    ChunkFileStorage(std::filesystem::path file_path, std::unique_ptr<IChunkFactory<T>> chunk_factory) :
        m_FilePath(file_path),
        m_ChunkFactory(std::move(chunk_factory))
    {
        if(std::filesystem::exists(m_FilePath))
        {
            // Validate header
            m_File.open(m_FilePath, std::ios::binary | std::ios::in | std::ios::out);
            m_File.seekg(0, std::ios::beg);
            Header header;
            ReadBinary(m_File, &header);
            ValidateHeader(header);

            // Build offsets
            m_File.seekg(0, std::ios::end);
            const std::uint64_t file_size = static_cast<std::uint64_t>(m_File.tellg());
            std::uint64_t offset = sizeof(Header);
            while (offset < file_size)
            {
                m_File.seekg(offset, std::ios::beg);
                ChunkFileData chunk_data;
                ReadBinary(m_File, &chunk_data);
                m_ChunkOffsets[chunk_data.pos] = offset;
                offset += chunk_data.cells_amount * sizeof(CellFileData) + sizeof(ChunkFileData);
            } 
        }
        else
        {
            std::ofstream file(m_FilePath, std::ios::binary);
            file.seekp(0, std::ios::beg);
            Header header;
            header.geometry_id = T::ID;
            WriteBinary(file, &header);
            file.close();
            m_File.open(m_FilePath, std::ios::binary | std::ios::in | std::ios::out);
        }
    }

    ~ChunkFileStorage()
    {
        m_File.close();
    }

    std::shared_ptr<IChunk<T>> GetChunk(const ChunkPosition& chunk_pos) override
    {
        auto it = m_ChunkOffsets.find(chunk_pos);
        if(it == m_ChunkOffsets.end()) return nullptr;
        return ReadChunk(it->second);
    }

    std::unordered_map<ChunkPosition, std::shared_ptr<IChunk<T>>> GetAllChunks() override
    {
        std::unordered_map<ChunkPosition, std::shared_ptr<IChunk<T>>> chunks;
        for(const auto& [pos, offset] : m_ChunkOffsets)
        {
            chunks[pos] = ReadChunk(offset);
        }
        return chunks;
    }

    void PushChunk(const ChunkPosition& chunk_pos, std::shared_ptr<IChunk<T>> chunk) override
    {
        auto it = m_ChunkOffsets.find(chunk_pos);
        if(it == m_ChunkOffsets.end())
        {
            m_File.seekp(0, std::ios::end);
            if(m_File.tellp() < sizeof(Header)) m_File.seekp(sizeof(Header));
            m_ChunkOffsets[chunk_pos] = m_File.tellp();
        }
        else
        {
            m_File.seekp(it->second);
        }

        std::vector<CellPosition> cell_positions = T::GetAllCellPositions(chunk_pos);
        ChunkFileData chunk_data {
            .pos = chunk_pos,
            .cells_amount = cell_positions.size()
        };
        WriteBinary(m_File, &chunk_data);
        for(const CellPosition& cell_pos : cell_positions)
        {
            ICell* cell = chunk->GetCell(cell_pos);
            CellFileData cell_data {
                .pos = cell_pos,
                .state = cell->GetState(),
                .type = cell->GetType()
            };
            WriteBinary(m_File, &cell_data);
        }
    }

private:
    std::filesystem::path m_FilePath;
    std::fstream m_File;
    std::unique_ptr<IChunkFactory<T>> m_ChunkFactory;
    std::unordered_map<ChunkPosition, std::uint64_t> m_ChunkOffsets;

    template<typename U>
    static bool ReadBinary(std::istream& stream, U* buf)
    {
        stream.read(reinterpret_cast<char*>(buf), sizeof(U));
        return stream.good();
    }

    template<typename U>
    static void WriteBinary(std::ostream& stream, U* buf)
    {
        stream.write(reinterpret_cast<char*>(buf), sizeof(U));
    }

    struct ChunkFileData
    {
        ChunkPosition pos;
        size_t cells_amount;
    };

    struct CellFileData
    {
        CellPosition pos;
        CellState state;
        CellType type;
    };

    std::shared_ptr<IChunk<T>> ReadChunk(std::uint64_t offset)
    {
        m_File.seekg(offset, std::ios::beg);
        ChunkFileData chunk_data;
        ReadBinary(m_File, &chunk_data);
        
        std::unordered_map<CellPosition, std::unique_ptr<ICell>> cells;
        for(size_t i = 0; i < chunk_data.cells_amount; i++)
        {
            CellFileData cell_data;
            ReadBinary(m_File, &cell_data);
            cells[cell_data.pos] = std::make_unique<Cell>(cell_data.type, cell_data.state);
        }

        return m_ChunkFactory->CreateChunk(std::move(cells));
    }

    void ValidateHeader(const Header& header)
    {
        Header correct_header;
        correct_header.geometry_id = T::ID;
        if(memcmp(header.magic, correct_header.magic, sizeof(header.magic))) throw std::runtime_error("Invalid magic");
        if(header.version != correct_header.version) throw std::runtime_error("Invalid version");
        if(header.geometry_id != correct_header.geometry_id) throw std::runtime_error("Invalid geometry");
    }
};

#endif // INCLUDE_GAME_CHUNKFILESTORAGE_H_