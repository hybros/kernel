#ifndef __SEARCH_CLASS__
#define __SEARCH_CLASS__

#include "data_types.hpp"
#include "memory.hpp"
#include "string.hpp"

enum SearchLocation
{
    SEARCH_IN_MEMORY,
    SEARCH_ON_DISKS,
    SEARCH_OTHER,
    SEARCH_ALL
};

enum SearchObjectSize
{
    SEARCH_CHAR,
    SEARCH_WORD,
    SEARCH_DWORD,
    SEARCH_QWORD
};

template<typename T>
class HSearch
{
public:
    HSearch();
    HSearch(T object);
    HSearch(T object, SearchLocation location);
    HSearch(T object, SearchLocation location, SearchObjectSize size);
    ~HSearch();

    void StartSearch();
    void StartSearchInParts(uint number_of_parts);

    bool WasSearchSuccessful();
    inline bool IsSearchFinished();

    inline uint GetSearchResult();
    inline uint GetLastSearchAddress();

    inline void SetRange(uint first_address, uint last_address);
    inline void SetObject(T object);
    inline void SetSearchLocation(SearchLocation location);
    inline void SetSearchObjectSize(SearchObjectSize size);
    inline void SetSearchObjectSize(size_t size);

protected:

    inline void DoSearch(T object);
    void SearchMemory();

private:
    T search_object, search_current_object;
    size_t search_object_size;
    uint search_beginning, search_end;
    bool search_finished, search_successful;
    uint search_parts_successful;
    uint search_loc, search_address;
    uint search_error;

    inline void SearchSucceeded();
    inline void SearchFailed();
};


#endif
