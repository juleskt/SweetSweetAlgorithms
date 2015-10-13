#ifndef BLOOMFILTER_H
#define	BLOOMFILTER_H
#include <string>
using namespace std;

class BloomFilter {
        public:
        /**
 *         * Instantiate an empty Bloom filter of length [ mm ] chars.
 *                 */
        BloomFilter (int mm) : length(mm) {}
        
        /**
 *         * Instantiates a Bloom filter from a given string [filter]
 *                 * @requires [filter] must have been produces by the output() call of a BloomFilter object.
 *                         */
        BloomFilter (string filter) : length(filter.length()) {}
        /**
 *         * inserts  into the filter
 *                 */
        void insert(string item);
        
        /**
 *         * Checks whether [item] is in the filter.
 *                 * @return  true if the item is probably in the filter
 *                         *          false if the item is definitely not in the filter
 *                                 */
        bool exists(string item);
        
        /**
 *         * @return A string of [length] characters representing the Bloom filer
 *                 */
        string output();
        
        protected:
        int length; /** The length of the Bloom filter, in chars. */
};

#endif	/* BLOOMFILTER_H */
