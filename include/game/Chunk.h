#ifndef INCLUDE_GAME_CHUNK_H_
#define INCLUDE_GAME_CHUNK_H_

#include "IChunk.h"
#include "ICell.h"
#include "GlobalConfig.h"
#include <array>
#include <memory>

class Chunk : public IChunk
{
public:
    Chunk(std::array<std::array<std::unique_ptr<ICell>, GameConf::CHUNK_WIDTH>, GameConf::CHUNK_HEIGHT> cells);

    SweepResult Sweep(const CellInChunkPosition& cell_pos) override;
    FlagResult Flag(const CellInChunkPosition& cell_pos) override;
    const ICell* GetCell(const CellInChunkPosition& cell_pos) const override;

private:
    std::array<std::array<std::unique_ptr<ICell>, GameConf::CHUNK_WIDTH>, GameConf::CHUNK_HEIGHT> m_Cells;
};

#endif // INCLUDE_GAME_CHUNK_H_