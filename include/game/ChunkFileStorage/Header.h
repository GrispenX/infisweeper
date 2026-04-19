#ifndef INCLUDE_GAME_CHUNKFILESTORAGE_HEADER_H_
#define INCLUDE_GAME_CHUNKFILESTORAGE_HEADER_H_

struct Header
{
    char magic[8] = "INFSWPR";
    int version = 1;
    int geometry_id;
    char reserved[256 - 8 - 2 * sizeof(int)];
};

static_assert(sizeof(Header) == 256);

#endif // INCLUDE_GAME_CHUNKFILESTORAGE_HEADER_H_