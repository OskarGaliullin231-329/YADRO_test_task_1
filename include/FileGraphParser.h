#ifndef FILEGRAPHPARSER_H_
#define FILEGRAPHPARSER_H_

#include <fstream>

#include "GraphParser.h"

class FileGraphParser: public GraphParser<FileGraphParser> {
public:
    bool parseFrom(std::ifstream&);

private:
};

#endif // FILEGRAPHPARSER_H_
