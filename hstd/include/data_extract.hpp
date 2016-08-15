#ifndef __DATA_EXTRACTOR__
#define __DATA_EXTRACTOR__

#include <Hybros/BitOperations>
#include <Hybros/Integer>

template<class R, typename T, T R::* P>
inline auto ExtractData(R &object) -> T &;

template<class R, typename T, T R::* P>
inline auto ExtractData(R *object) -> T &;

inline auto ExtractByte(const HInt &value = HInteger(), const HInt &byte_number = HInteger()) -> uchar;      // byte_number: Starting by 0
inline auto ExtractWord(const HInt &value = HInteger(), const HInt &word_number = HInteger()) -> ushort;     // word_number: Starting by 0
inline auto ExtractDword(const HInt &value = HInteger(), const HInt &dword_number = HInteger()) -> uint;     // dword_number: Starting by 0

template<typename T, typename R>
inline constexpr auto Extract(R value, uint position) -> T;


#endif
