#ifndef __LFUCACHE_H__
#define __LFUCACHE_H__

#include <Utility.h>

class LFUCache {
    unordered_map<int, list<int>> freqListKeyMap; // freq->list<key>;
    unordered_map<int, int> keyFreqMap;           // key->freq;
    unordered_map<int, int> keyValueMap;          // key->value;
    int _capacity;
    int _size;
    int _minFreq;

  public:
    LFUCache(int capacity) : _capacity(capacity), _size(0), _minFreq(INT_MAX) {}
    int get(int key) {
        int res = -1;
        if (keyFreqMap.count(key) != 0) {
            res = keyValueMap[key];
            int freq = keyFreqMap[key];
            // update status
            ++keyFreqMap[key];
            freqListKeyMap[freq].remove(key);
            freqListKeyMap[freq + 1].push_back(key);
            if (freqListKeyMap[_minFreq].size() == 0)
                _minFreq = freq + 1;
        }

        return res;
    }
    // O(1)
    void put(int key, int value) {
        int cur_value = get(key);
        if (cur_value == value)
            return;
        if (cur_value != -1) {
            int freq = keyFreqMap[key];
            // update status
            freqListKeyMap[freq].remove(key);
            keyFreqMap[key] = 1;
            keyValueMap[key] = value;
            freqListKeyMap[1].push_back(key);
            _minFreq = 1;
        } else if (cur_value == -1 && _size < _capacity) {
            // update status
            keyFreqMap[key] = 1;
            keyValueMap[key] = value;
            freqListKeyMap[1].push_back(key);
            _minFreq = 1;
            ++_size;
        } else if (cur_value == -1 && _size == _capacity && _capacity > 0) {
            // delete LRU key
            int LRUKey = freqListKeyMap[_minFreq].front();
            freqListKeyMap[_minFreq].pop_front();
            keyValueMap.erase(LRUKey);
            keyFreqMap.erase(LRUKey);

            // update new key
            keyFreqMap[key] = 1;
            keyValueMap[key] = value;
            freqListKeyMap[1].push_back(key);
            _minFreq = 1;
        }
    }
};

#endif