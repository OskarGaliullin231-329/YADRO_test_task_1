#ifndef FILELOGER_H_
#define FILELOGER_H_

#include <fstream>
#include <string>

#include "Loger.h"

class FileLoger: public Loger {
public:
    FileLoger(std::string);
    bool write();
    void showErrorMsg(std::string&);

private:
    std::ofstream file;
};

#endif // FILELOGER_H_
