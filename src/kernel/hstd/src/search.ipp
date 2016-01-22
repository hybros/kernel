#include "../include/search.hpp"

namespace kernel
{
namespace hstd
{

template<typename T>
HSearch<T>::HSearch() {}

template<typename T>
HSearch<T>::HSearch(T object) : HSearch(object, SEARCH_ALL, SEARCH_QWORD) {}

template<typename T>
HSearch<T>::HSearch(T object, SearchLocation location) : HSearch(object, location, SEARCH_QWORD) {}

template<typename T>
HSearch<T>::HSearch(T object, SearchLocation location, SearchObjectSize size)
{
    SetObject(object);
    SetSearchLocation(location);
    SetSearchObjectSize(size);
}

template<typename T>
HSearch<T>::~HSearch()
{
    memzero(&search_object, sizeof(search_object));
}

template<typename T>
void HSearch<T>::StartSearch()
{
    if(!search_object)
        SearchFailed();
    if(!search_loc)
        SearchFailed();

    DoSearch(search_object);
}

template<typename T>
void HSearch<T>::StartSearchInParts(uint number_of_parts)
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
bool HSearch<T>::WasSearchSuccessful()
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
bool HSearch<T>::IsSearchFinished()
{
    return search_finished;
}

template<typename T>
uint HSearch<T>::GetSearchResult()
{
    if(WasSearchSuccessful())
        return GetLastSearchAddress();
    else
        return 0;
}

template<typename T>
uint HSearch<T>::GetLastSearchAddress()
{
    return search_address;
}

template<typename T>
void HSearch<T>::SetRange(uint first_address, uint last_address)
{
    search_beginning = first_address;
    search_end = last_address;
}

template<typename T>
void HSearch<T>::SetObject(T object)
{
    memcpy(&search_object, &object, sizeof(object));
}

template<typename T>
void HSearch<T>::SetSearchLocation(SearchLocation location)
{
    search_loc = location;
}

template<typename T>
void HSearch<T>::SetSearchObjectSize(SearchObjectSize size)
{
    search_object_size = size;
}

template<typename T>
void HSearch<T>::SetSearchObjectSize(size_t size)
{
    search_object_size = size;
}

template<typename T>
void HSearch<T>::DoSearch(T object)
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
void HSearch<T>::SearchMemory()
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
void HSearch<T>::SearchSucceeded()
{
    search_finished = true;
    search_successful = true;
}

template<typename T>
void HSearch<T>::SearchFailed()
{
    search_finished = true;
    search_successful = false;
}

}
}
