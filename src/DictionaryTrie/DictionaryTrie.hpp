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

/** Define a MyComparator to allow for two priorities of the priority queue.
 *  During optimization, change the underlying PQ to a min-PQ to keep the PQ a
 *  fixed size later in predictions.
 */
struct MyComparator {
    bool operator()(pair<unsigned int, string> const& p1,
                    pair<unsigned int, string> const& p2) const {
        if (p1.first != p2.first) {
            return p1.first > p2.first;
        } else {
            return p1.second < p2.second;
            return p1.second > p2.second;
        }
    }
};

/** The PQ uses a Comparator first compare the pair's first element--frequency;
 *  if frequency is equal, then compare the second element (alphabetical order)
 */
typedef priority_queue<pair<unsigned int, string>,
                       vector<pair<unsigned int, string> >, MyComparator>
    my_queue;

/**
 * The class for a dictionary ADT, implemented as either
 * a mulit-way trie or a ternary search tree.
 */
class DictionaryTrie {
  private:
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
    void collect(string s, my_queue& q, TrieNode* node, string prefix, int num);

    /** Helper function for predictUnderscores.
     *  Returns a priority queue of pairs of frequency and word.
     */
    void collectUnderscore(TrieNode* n, string s, string pattern, my_queue& q);

    /** Return a vector of strings from PQ. */
    vector<string> popVector(my_queue& q, int num);

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
