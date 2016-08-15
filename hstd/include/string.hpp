#ifndef __STRING_MANIPULATION_FUNCTIONS__
#define __STRING_MANIPULATION_FUNCTIONS__

#include <Hybros/StdTypes>

class HString
{
public:
    HString();
    HString(const char character);
    HString(const char *string);
    HString(const HString &string);
    HString(HString &&string);
    ~HString();

    auto IsEmpty() const -> bool;

    auto GetSize() const -> size_t;
    auto GetSize(const char *other_string) const -> size_t;
    auto GetLength() const -> size_t;
    auto GetLength(const char *other_string) const -> size_t;
    auto GetUnicodeString() const -> char *;

    void Free();

    auto CopyFrom(const char character) -> bool;
    auto CopyFrom(const char *string) -> bool;
    auto CopyFrom(const HString &string) -> bool;

    auto MoveFrom(char *string) -> bool;
    auto MoveFrom(HString &string) -> bool;

    auto Append(const char append) -> HString &;
    auto Append(const char *append) -> HString &;
    auto Append(const HString &append) -> HString &;

    auto operator =(const char source) -> HString &;
    auto operator =(const char *source) -> HString &;
    auto operator =(const HString &source) -> HString &;
    auto operator =(const HString &&source) -> HString &;

    auto operator [](const size_t position) -> char &;
    auto operator [](const size_t position) const -> char;

    void operator +=(const char append);
    void operator +=(const char *append);
    void operator +=(const HString &append);

    auto operator +(const char character) -> HString;
    auto operator +(const char *string) -> HString;
    auto operator +(const HString &string) -> HString;

protected:
    char *CreateNewBuffer(size_t size);

private:
    char *string_pointer;
    size_t string_size;
    size_t string_length;
};

template<typename T>
auto IntegerToString(T number, char *string, int base) -> T;

template<typename T>
auto ConvertToRawString(T number, int base) -> char *;

template<typename T>
auto ConvertToHString(T number, int base) -> HString;

#endif
