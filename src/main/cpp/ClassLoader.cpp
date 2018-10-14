#include "../hpp/ClassLoader.hpp"

/**
 * @brief Construtor da classe da ClassLoader;
 * A ideia é chamar todos os Set's aqui de maneira
 * garantir a qualidade dos dados.
 */

ClassLoader::ClassLoader(FILE * fp) {
    this->setMagic(fp);

    if((this->getMagic() == 0xCAFEBABE)) {
        this->setMinor(fp);
        this->setMajor(fp);
        this->setConstCount(fp);
        this->setConstPool(fp);
        this->setAcessFlag(fp);
        this->setThisClass(fp);
        this->setSuperClass(fp);
        this->setInterCount(fp);
        this->setInterface(fp);
        this->setFieldCount(fp);
        this->setFields(fp);
        this->setMethodCount(fp);
        this->setMethods(fp);
        this->setAttributesCount(fp);
        this->setAttributes(fp);
    }
    else std::cout << "invalid file pointer" << std::endl; // TODO: Modificar esse Else para algum throw ou retorno.  
}

/**
 * Aqui são feitas as desalocações 
 * da ClassLoader
 */

ClassLoader::~ClassLoader() {
    
    for(auto a : this->methods) {
        a->~MethodInfo();
        free(a);
    }
        
    for(auto a : this->constantPool) {
        a->~CpInfo(); // Chama o destrutor para desalocar os bytes alocados no escopo da classe.
        free(a);      // Desaloca o que foi criado alocado dentro de 
    }
}

void ClassLoader::setMagic(FILE * fp) {
    ByteReader<typeof(magicNumber)> bReader;
    magicNumber = bReader.byteCatch(fp);
}

void ClassLoader::setMinor(FILE * fp) {
    ByteReader<typeof(minorVersion)> bReader;
    minorVersion = bReader.byteCatch(fp);
}

void ClassLoader::setMajor(FILE * fp) {
    ByteReader<typeof(majorVersion)> bReader;
    majorVersion = bReader.byteCatch(fp);
}

void ClassLoader::setConstCount(FILE * fp) {
    ByteReader<typeof(constantPoolCounter)> bReader;
    constantPoolCounter = bReader.byteCatch(fp);
}

void ClassLoader::setConstPool(FILE * fp) {
     
    /* Iterate over the size of constant pool */
    for(int i = 0; i < this->getConstCount() - 1; i++) {

        CpInfo * cp = (CpInfo *)calloc(1, sizeof(*cp)); /* Allocate a constante pool */
        cp->read(fp);  
        this->constantPool.push_back(cp); /* Puts into the vector of constant pools  */
    } 
    
}


void ClassLoader::setAcessFlag(FILE * fp) {
    ByteReader<uint16_t> bReader;
    acessFlags = bReader.byteCatch(fp);
}

void ClassLoader::setThisClass(FILE * fp) {
    ByteReader<typeof(thisClass)> bReader;
    thisClass = bReader.byteCatch(fp);
}
void ClassLoader::setSuperClass(FILE * fp) {
    ByteReader<typeof(superClass)> bReader;
    superClass = bReader.byteCatch(fp);
}

void ClassLoader::setInterCount(FILE * fp) {
    ByteReader<typeof(interfaceCounter)> bReader;
    interfaceCounter = bReader.byteCatch(fp);
}

void ClassLoader::setInterface(FILE * fp) {
    //ByteReader<typeof(interfaces)> bReader;
    //interfaces = bReader.byteCatch(fp);
}

void ClassLoader::setFieldCount(FILE * fp) {
    ByteReader<typeof(fieldsCounter)> bReader;
    fieldsCounter = bReader.byteCatch(fp);
}

void ClassLoader::setFields(FILE * fp) {
    //ByteReader<typeof(fields)> bReader;
    //fields = bReader.byteCatch(fp);
}

void ClassLoader::setMethodCount(FILE * fp) {
    ByteReader<typeof(methodsCounter)> bReader;
    methodsCounter = bReader.byteCatch(fp);
}

void ClassLoader::setMethods(FILE * fp) {
    
    for(int i = 0; i < this->getMethoCount(); i++) {

        MethodInfo * mi = (MethodInfo *)calloc(1,sizeof(MethodInfo));
        mi->read(fp);
        this->methods.push_back(mi);

    }
}

void ClassLoader::setAttributesCount(FILE * fp) {
    ByteReader<typeof(attributesCounter)> bReader;
    attributesCounter = bReader.byteCatch(fp);
}

void ClassLoader::setAttributes(FILE * fp) {
   // ByteReader<typeof(attributes)> bReader;
   // attributes = bReader.byteCatch(fp);
}
