#ifndef INCLUDE_GAME_GEOMETRYCONCEPT_H_
#define INCLUDE_GAME_GEOMETRYCONCEPT_H_

#include <concepts>
#include <vector>

template<typename T>
concept Geometry = requires
(
    const typename T::MinefieldPosition& minefield_pos,
    const T::ChunkPosition& chunk_pos
)
{
    typename T::ChunkPosition;
    typename T::CellPosition;
    typename T::MinefieldPosition;
    requires std::equality_comparable<typename T::ChunkPosition>;

    { typename T::ChunkPositionHasher()(chunk_pos) } -> std::same_as<size_t>;

    { minefield_pos.chunk_pos } -> std::convertible_to<typename T::ChunkPosition>;
    { minefield_pos.cell_pos } -> std::convertible_to<typename T::CellPosition>;

    { T::GetAllCellPositions(chunk_pos) } -> std::same_as<std::vector<typename T::CellPosition>>;
    { T::GetNeighboursPositions(minefield_pos) } -> std::same_as<std::vector<typename T::MinefieldPosition>>;
};

#endif // INCLUDE_GAME_GEOMETRYCONCEPT_H_