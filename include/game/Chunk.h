#ifndef INCLUDE_GAME_CHUNK_H_
#define INCLUDE_GAME_CHUNK_H_

#include "IChunk.h"
#include "ICell.h"
#include <vector>
#include <memory>

class Chunk : public IChunk
{
public:
    Chunk(std::vector<std::unique_ptr<ICell>>& cells);

    SweepResult Sweep(size_t index) override;
    FlagResult Flag(size_t index) override;
    ICell* GetCell(size_t index) const override;
    size_t GetSize() const override;

private:
    std::vector<std::unique_ptr<ICell>> m_Cells;
};

#endif // INCLUDE_GAME_CHUNK_H_