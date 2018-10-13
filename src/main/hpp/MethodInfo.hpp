#ifndef ___METHOD_H___
#define ___METHOD_H___

#include <cstdint>
#include "AttributeInfo.hpp"

struct MethodInfo{
    uint16_t acess_flags;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t attributes_count;
    AttributeInfo * attributes;

    void read(FILE * fp);
    ~MethodInfo();
};

#endif // ___METHOD_H___