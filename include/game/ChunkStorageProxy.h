#ifndef INCLUDE_GAME_ICHUNKSTORAGEPROXY_H_
#define INCLUDE_GAME_ICHUNKSTORAGEPROXY_H_

#include "game/IChunkStorage.h"
#include <unordered_map>

template<Geometry T>
class ChunkStorageProxy : public IChunkStorage<T>
{
public:
    using ChunkPosition = T::ChunkPosition;

    ChunkStorageProxy(std::unique_ptr<IChunkStorage<T>> storage) :
        m_ChunkStorage(std::move(storage))
    {
        m_Chunks = m_ChunkStorage->GetAllChunks();
    }

    ~ChunkStorageProxy()
    {
        for(const auto& [pos, chunk] : m_Chunks)
        {
            m_ChunkStorage->PushChunk(pos, chunk);
        }
    }

    std::shared_ptr<IChunk<T>> GetChunk(const ChunkPosition& chunk_pos) override
    {
        auto it = m_Chunks.find(chunk_pos);
        if(it == m_Chunks.end()) return nullptr;
        return it->second;
    }
    
    std::unordered_map<ChunkPosition, std::shared_ptr<IChunk<T>>> GetAllChunks() override
    {
        return m_Chunks;
    }

    void PushChunk(const ChunkPosition& chunk_pos, std::shared_ptr<IChunk<T>> chunk) override
    {
        m_Chunks[chunk_pos] = chunk;
    }

private:
    std::unique_ptr<IChunkStorage<T>> m_ChunkStorage;
    std::unordered_map<ChunkPosition, std::shared_ptr<IChunk<T>>> m_Chunks;
};

#endif // INCLUDE_GAME_ICHUNKSTORAGEPROXY_H_