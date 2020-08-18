#include <algorithm>
#include <iostream>
#include <list>
#include <stdexcept>
#include <utility>
#include <vector>

template <class KeyType, class ValueType, class Hash = std::hash<KeyType>>
class HashMap {
public:
    HashMap(Hash _hash = Hash()) : hash(_hash) {
        real_size = 0;
        data.resize(tablesize());
    }

    template <class InitIterType>
    HashMap(InitIterType start, InitIterType ending, Hash _hash = Hash()) : hash(_hash) {
        real_size = 0;
        data.resize(tablesize());
        for (auto it = start; it != ending; ++it) {
            insert(*it);
        }
    }

    HashMap(const std::initializer_list<std::pair<KeyType, ValueType>>& ilist,
        Hash _hash = Hash()) : hash(_hash) {
        real_size = 0;
        data.resize(tablesize());
        for (auto it = ilist.begin(); it != ilist.end(); ++it) {
            insert(*it);
        }
    }

    size_t size() const {
        return real_size;
    }

    bool empty() const {
        return real_size == 0;
    }

    Hash hash_function() const {
        return hash;
    }

    void insert(const std::pair<KeyType, ValueType>& item) {
        // if (2 * real_size > tablesize()) {
        //     expand();
        // }
        insert_item(item);
        // edit_item(item);
    }

    void erase(const KeyType& key) {
        erase_item(key);
    }

    typedef typename std::list<std::pair<KeyType, ValueType>>::iterator iterator;
    typedef typename std::list<std::pair<KeyType, ValueType>>::const_iterator const_iterator;

    iterator begin() {
        return all.begin();
    }

    const_iterator begin() const {
        return all.cbegin();
    }

    iterator end() {
        return all.end();
    }

    const_iterator end() const {
        return all.cend();
    }

    iterator find(const KeyType& key) {
        size_t index = hash(key) % tablesize();
        if (data[index].begin() == data[index].end()) {
            return end();
        }
        for (auto it = data[index].begin(); it != data[index].end(); ++it) {
            if ((*it)->first == key) {
                return *it;
            }
        }
        return end();
    }

    const_iterator find(const KeyType& key) const {
        size_t index = hash(key) % tablesize();
        if (data[index].begin() == data[index].end()) {
            return end();
        }
        for (auto it = data[index].begin(); it != data[index].end(); ++it) {
            if ((*it)->first == key) {
                return *it;
            }
        }
        return end();
    }

    ValueType& operator[](const KeyType& key) {
        size_t index = hash(key) % tablesize();
        if (data[index].begin() == data[index].end()) {
            insert(std::make_pair(key, ValueType()));
            index = hash(key) % tablesize();
            return (data[index].back())->second;
        }
        for (auto it = data[index].begin(); it != data[index].end(); ++it) {
            if ((*it)->first == key) {
                return (*it)->second;
            }
        }
        insert(std::make_pair(key, ValueType()));
        index = hash(key) % tablesize();
        return (data[index].back())->second;
    }

    const ValueType& at(const KeyType& key) const {
        size_t index = hash(key) % tablesize();
        if (data[index].begin() == data[index].end()) {
            throw std::out_of_range("oops");
            return (data[index].back())->second;
        }
        for (auto it = data[index].begin(); it != data[index].end(); ++it) {
            if ((*it)->first == key) {
                return (*it)->second;
            }
        }
        throw std::out_of_range("oops");
        return (data[index].back())->second;
    }

    void clear() {
        auto all_cpy = all;
        for (auto it = all_cpy.begin(); it != all_cpy.end(); ++it) {
            erase(it->first);
        }
    }

    std::vector<std::list<iterator>> data;
    std::list<std::pair<KeyType, ValueType>> all;

private:
    Hash hash;
    size_t real_size;

    const size_t tablesize() const {
        return 262147;
    }

    void insert_item(const std::pair<KeyType, ValueType>& item) {
        size_t index = hash(item.first) % tablesize();
        for (auto it = data[index].begin(); it != data[index].end(); ++it) {
            if ((*it)->first == item.first) {
                return;
            }
        }
        ++real_size;
        all.push_back(item);
        data[index].push_back(std::prev(all.end()));
    }

    void erase_item(const KeyType& key) {
        size_t index = hash(key) % tablesize();
        if (data[index].begin() == data[index].end()) {
            return;
        }
        for (auto it = data[index].begin(); it != data[index].end(); ++it) {
            if ((*it)->first == key) {
                --real_size;
                all.erase(*it);
                data[index].erase(it);
                return;
            }
        }
    }
};
