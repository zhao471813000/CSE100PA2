/**
 * This file defines an DictionaryTrie which realizes a
 * autocompleter and a wildcard completer.
 * Author: Kexin Hong A53311871, Dingqian Zhao A53319585.
 */
#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

/**
 * The class for a dictionary ADT, implemented as either
 * a mulit-way trie or a ternary search tree.
 */
class DictionaryTrie {
  private:
    // Add private members and helper methods here
    class TrieNode {
      public:
        unsigned int frequency;
        unordered_map<char, TrieNode*> map;
        /** Initializes a new TrieNode. */
        TrieNode() : frequency(0) {}

        TrieNode(string word, unsigned int freq) : frequency(freq) {}
    };

    TrieNode* root;

    void deleteAll(TrieNode* node) {
        if (node == nullptr) {
            return;
        } else {
            for (pair<char, TrieNode*> element : node->map) {
                deleteAll(element.second);
            }
            node->map.clear();
        }
    }

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
     *  completions of prefix, with valid words in the dictionary.  */
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
