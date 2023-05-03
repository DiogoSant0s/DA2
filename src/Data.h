#ifndef DA2_DATA_H
#define DA2_DATA_H

#include "Graph.h"

using namespace std;

class Data {
private:
    Graph Network;
public:
    /**
     * Creates a new data.
     * @details Creates a new Graph and reads all the data from the files.
     */
    Data();
};

#endif //DA2_DATA_H
