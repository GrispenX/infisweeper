#ifndef INCLUDE_GAME_GEOMETRYCONCEPT_H_
#define INCLUDE_GAME_GEOMETRYCONCEPT_H_

#include "game/PlainPosition.h"
#include "game/ViewportData.h"
#include <concepts>
#include <vector>


template<typename T>
concept Geometry = requires
(
    const typename T::MinefieldPosition& minefield_pos,
    const T::ChunkPosition& chunk_pos,
    const PlainPosition& plain_pos,
    const PlainPosition& plain_pos2
)
{
    typename T::ChunkPosition;
    typename T::CellPosition;
    typename T::MinefieldPosition;
    typename T::ChunkPositionHasher;
    requires std::equality_comparable<typename T::ChunkPosition>;

    { typename T::ChunkPositionHasher()(chunk_pos) } -> std::same_as<size_t>;

    { minefield_pos.chunk_pos } -> std::convertible_to<typename T::ChunkPosition>;
    { minefield_pos.cell_pos } -> std::convertible_to<typename T::CellPosition>;

    { T::CellsAmount(chunk_pos) } -> std::convertible_to<std::size_t>;
    { T::PlainToMinefield(plain_pos) } -> std::same_as<typename T::MinefieldPosition>;
    { T::MinefieldToIndex(minefield_pos) } -> std::convertible_to<size_t>;
    { T::GetNeighboursPositions(minefield_pos) } -> std::same_as<std::vector<typename T::MinefieldPosition>>;

    { T::GetChunksInRectangle(plain_pos, plain_pos2) } -> std::same_as<std::vector<typename T::ChunkPosition>>;
    { T::GetCellsInRectangle(plain_pos, plain_pos2) } -> std::same_as<std::vector<typename T::MinefieldPosition>>;
    { T::GetChunkBoundaries(chunk_pos) } -> std::same_as<std::vector<std::pair<PlainPosition, PlainPosition>>>;

    { T::GetCellShape(minefield_pos) } -> std::same_as<CellShape>;
    { T::GetCellCenter(minefield_pos) } -> std::same_as<PlainPosition>;
    { T::GetCellScale(minefield_pos) } -> std::same_as<double>;
    { T::GetCellRotation(minefield_pos) } -> std::same_as<double>;
};

#endif // INCLUDE_GAME_GEOMETRYCONCEPT_H_