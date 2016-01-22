#ifndef __SEARCH_CLASS__
#define __SEARCH_CLASS__

#include "data_types.hpp"
#include "memory.hpp"
#include "string.hpp"

namespace kernel
{
namespace std DLL_PUBLIC
{

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
class Search
{
public:
    Search();
    Search(T object);
    Search(T object, SearchLocation location);
    Search(T object, SearchLocation location, SearchObjectSize size);
    ~Search();

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
    kernel::Terminal *dbg_out;

    inline void SearchSucceeded();
    inline void SearchFailed();
};

// ~ Search

template<typename T>
Search<T>::Search() {}

template<typename T>
Search<T>::Search(T object) : Search(object, SEARCH_ALL, SEARCH_QWORD) {}

template<typename T>
Search<T>::Search(T object, SearchLocation location) : Search(object, location, SEARCH_QWORD) {}

template<typename T>
Search<T>::Search(T object, SearchLocation location, SearchObjectSize size)
{
    SetObject(object);
    SetSearchLocation(location);
    SetSearchObjectSize(size);
}

template<typename T>
Search<T>::~Search()
{
    memzero(&search_object, sizeof(search_object));
}

template<typename T>
void Search<T>::StartSearch()
{
    if(!search_object)
        SearchFailed();
    if(!search_loc)
        SearchFailed();

    DoSearch(search_object);
}

template<typename T>
void Search<T>::StartSearchInParts(uint number_of_parts)
{
    if(!search_object)
        SearchFailed();
    if(!search_loc)
        SearchFailed();

    for(uint i = 0; i < number_of_parts; i++)
    {
        DoSearch(search_object);
        if(search_successful == true)
            search_parts_successful++;
    }

    if(search_parts_successful == number_of_parts)
        SearchSucceeded();
    else
        SearchFailed();
}

template<typename T>
bool Search<T>::WasSearchSuccessful()
{
    if(search_finished)
    {
        if(search_successful)
            return true;
        else
            return false;
    }
    else
        return false;
}

template<typename T>
bool Search<T>::IsSearchFinished()
{
    return search_finished;
}

template<typename T>
uint Search<T>::GetSearchResult()
{
    if(WasSearchSuccessful())
        return GetLastSearchAddress();
    else
        return 0;
}

template<typename T>
uint Search<T>::GetLastSearchAddress()
{
    return search_address;
}

template<typename T>
void Search<T>::SetRange(uint first_address, uint last_address)
{
    search_beginning = first_address;
    search_end = last_address;
}

template<typename T>
void Search<T>::SetObject(T object)
{
    memcpy(&search_object, &object, sizeof(object));
}

template<typename T>
void Search<T>::SetSearchLocation(SearchLocation location)
{
    search_loc = location;
}

template<typename T>
void Search<T>::SetSearchObjectSize(SearchObjectSize size)
{
    search_object_size = size;
}

template<typename T>
void Search<T>::SetSearchObjectSize(size_t size)
{
    search_object_size = size;
}

template<typename T>
void Search<T>::DoSearch(T object)
{
    search_current_object = object;
    switch(search_loc)
    {
    case SEARCH_IN_MEMORY:
        SearchMemory();
        break;
    case SEARCH_ON_DISKS:           // TODO: implement
        break;
    case SEARCH_OTHER:              // TODO: implement
        break;
    case SEARCH_ALL:                // TODO: add functionality
        SearchMemory();
        break;
    default:
        break;
    }
}

template<typename T>
void Search<T>::SearchMemory()
{
    if(search_beginning && search_end && search_object_size)
    {
        uchar *pattern = reinterpret_cast<uchar*>(search_current_object);
        uint pattern_size = search_object_size;
        for(uchar *address = reinterpret_cast<uchar*>(search_beginning); address < reinterpret_cast<uchar*>(search_end); address += 16)
        {
            if((address == pattern[0]) && ((address + 1) == pattern[i + 1]) && (i < pattern_size))
                i++;
            else if(i == pattern_size)
            {
                search_address = address - pattern_size;
                SearchSucceeded();
                return;
            }
            else
                continue;
        }
    }
    SearchFailed();
}

template<typename T>
void Search<T>::SearchSucceeded()
{
    search_finished = true;
    search_successful = true;
}

template<typename T>
void Search<T>::SearchFailed()
{
    search_finished = true;
    search_successful = false;
}

}
}

// End Search

#endif
