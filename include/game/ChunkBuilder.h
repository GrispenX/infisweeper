#ifndef INCLUDE_GAME_CHUNKBUILDER_H_
#define INCLUDE_GAME_CHUNKBUILDER_H_

#include "game/IChunkBuilder.h"
#include "game/Chunk.h"

class ChunkBuilder : public IChunkBuilder
{
public:
    void Reset() override;
    void AddCell(const CellInChunkPosition& cell_pos, std::unique_ptr<ICell> cell) override;
    std::unique_ptr<IChunk> GetResult() override;

private:
    std::array<std::array<std::unique_ptr<ICell>, GameConf::CHUNK_WIDTH>, GameConf::CHUNK_HEIGHT> m_Cells;
};

#endif // INCLUDE_GAME_CHUNKBUILDER_H_