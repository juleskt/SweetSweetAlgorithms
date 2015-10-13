#ifndef GENERIC_SORT
#define GENERIC_SORT

#include <vector>
using namespace std;

/** This is a very generic sorting data structure.  It is designed to allow a user
 * to enter a fixed number of objects of class T, to sort the objects, and
 * to provide random access to the k-th item in the data structure.
 */
template <class T>
class genericSort {
public:

    /**
     * Constructs a data structure capable of holding "size" items.
     */
    genericSort() // sets up a Sort object for "size" items
    {}

    /**
     * Delete memory associated with this data structure.
     */
    ~genericSort() {
        data.clear();
    }

    /**
     * Adds an item to the end of the current list of items.
     * @param item The item to be added to the data structure.
     */
    void insert(T item)
    { data.push_back(item); }

    /**
     * Sort all the items in the data structure.  This is the method you
     * will definitely have to overwrite in your bigIntSort subclass.
     */
    virtual void performSort() = 0; // sorts the items in the object

    /**
     * Returns the number of items currently in the data structure.
     */
    int numItems()
    { return data.size(); }
    
    /**
     * Return the kk-th item in the data structure.
     * @param kk The index of the item to return.
     *           kk=0 gives the first item in the data structure.
     *           kk>= the number of items in the data structure gives an undefined response.
     */
    T returnKth(int kk)
    { return data[kk]; }

protected:
    vector<T> data;    /** an array of the items stored by the data structure */
};

#endif
