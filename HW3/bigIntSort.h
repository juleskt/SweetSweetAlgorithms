#include "bigInt.h"
#include "genericSort.h"

/**
 * bigIntSort is a sort data structure that handles pointers to bigInts.
 */

class bigIntSort : public genericSort<bigInt *> {
public:
    void performSort();
};
