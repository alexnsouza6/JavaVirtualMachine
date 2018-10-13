#include "../hpp/MethodInfo.hpp"
#include "ByteReader.cpp"

MethodInfo::~MethodInfo() {
    free(this->attributes);
    std::cout << "DESALOQUEI" << std::endl;
}

void MethodInfo::read(FILE * fp) {
    ByteReader<uint16_t> reader;

    this->acess_flags      = reader.byteCatch(fp);
    this->name_index       = reader.byteCatch(fp);
    this->descriptor_index = reader.byteCatch(fp);
    this->attributes_count = reader.byteCatch(fp);

    //TODO: Settar isso daqui.
    this->attributes = (AttributeInfo *)calloc(attributes_count, sizeof(AttributeInfo)); 
    

}