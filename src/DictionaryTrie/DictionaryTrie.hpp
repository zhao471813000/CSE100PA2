/**
 * This file defines an DictionaryTrie which realizes a
 * autocompleter and a wildcard completer.
 * Author: Kexin Hong A53311871, Dingqian Zhao A53319585.
 */
#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <limits>  // numeric_limits<type>::max()
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

struct MyComparator {
    bool operator()(pair<int, string> const& p1, pair<int, string> const& p2) {
        if (p1.first != p2.first) {
            return p1.first < p2.first;
        } else {
            return (p1.second.compare(p2.second) > 0);
        }
    }
};
// typedef pair<int, string> my_pair;
// typedef priority_queue<my_pair, vector<my_pair>, MyComparator> my_queue;
typedef priority_queue<pair<int, string>, vector<pair<int, string> >,
                       MyComparator>
    my_queue;

/* Use priority_queue to sort the word according to freq from top to low.
 * Priority_queue by default uses less<T> comparator, vector<T> container.*/
// struct MyPair {
//     int freq;
//     string str;

//     MyPair(int freq, string str) : freq(freq), str(str) {}
// };

// implements the operator overlading
// struct MyComparator {
//     bool operator()(MyPair const& p1, MyPair const& p2) {
//         if (p1.freq != p2.freq) {
//             return p1.freq < p2.freq;
//         } else {
//             p1.str < p2.str;
//         }
//     }
// };

/**
 * The class for a dictionary ADT, implemented as either
 * a mulit-way trie or a ternary search tree.
 */
class DictionaryTrie {
  private:
    // Add private members and helper methods here

    /** The class for a Multi-Way Trie Node, which uses unordered_map
     * to map from current char to next Trie Node. */
    class TrieNode {
      public:
        /* Frequency is also used to indicate a word node.
        Frequency 0 means it is not word node, vice versa. */
        unsigned int frequency;

        unordered_map<char, TrieNode*> map;
        /** Initializes a new TrieNode. */
        TrieNode() : frequency(0), map() {}

        TrieNode(char c, unsigned int freq) : frequency(freq) {
            map[c] = new TrieNode();
        }
    };

    TrieNode* root;

    /** Helper function for predictCompletions.
     *  Returns a priority queue of pairs of frequency and word.
     */
    void collect(string s, my_queue& q, TrieNode* n, string prefix);

    /** Helper function for predictUnderscores.
     *  Returns a priority queue of pairs of frequency and word.
     */
    void collectUnderscore(TrieNode* n, string s, string pattern, my_queue& q);

    /** Return a vector of strings with top N frequency from PQ. */
    vector<string> topNFreq(my_queue& q, int n);
    /** Helper funciton for destructor. */

    void deleteAll(TrieNode* node);

  public:
    /** Initializes a new DictionaryTrie. */
    DictionaryTrie();

    /** Insert a word with its frequency into the DictionaryTrie.
     *  Return true if the word was inserted successfully,
     *  or false if given string is empty or already inserted. */
    bool insert(string word, unsigned int freq);

    /** Return true if the words in the DictionaryTrie and
     *  false otherwise. */
    bool find(string word) const;

    /** Return a vector holding up to numCompletions of the most frequent
     * completions of prefix, and the completions must be valid words in the
     * dictionary. These completions should be listed from most to least
     * frequent. */
    vector<string> predictCompletions(string prefix,
                                      unsigned int numCompletions);

    /** Return a vector holding up to numCompletions of the most frequent
     *  completions of pattern, which includes one or more underscores '_' */
    vector<string> predictUnderscores(string pattern,
                                      unsigned int numCompletions);

    /** Destructor to avoid memory leaks. */
    ~DictionaryTrie();
};

#endif  // DICTIONARY_TRIE_HPP
