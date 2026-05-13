#ifndef FILELOGER_H_
#define FILELOGER_H_

#include <fstream>

#include "Loger.h"

class FileLoger: public Loger {
public:
    bool write(std::ofstream&);
};

#endif // FILELOGER_H_
