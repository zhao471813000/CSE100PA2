/**
 * This file implements an DictionaryTrie, realizing a autocompleter and a
 * wildcard completer. Priority queue is used in this PA to store the words with
 * frequencies.
 * @source: Algorithms, 4th Edition by Robert Sedgewick and Kevin Wayne
 * @source: Discussion slides of CSE100.
 * The source of the algorithm of the wildcard prediction is from the slides of
 * discussion of CSE100 at UCSD, and the textbook Algorithms, 4th Edition by
 * Robert Sedgewick and Kevin Wayne.
 *
 * Author: Kexin Hong A53311871, Dingqian Zhao A53319585.
 */
#include "DictionaryTrie.hpp"
#include <algorithm>
#include <iostream>

/* Use priority_queue of type "<pair<int, string>>"" defined as "my_queue" in
 * hpp file to sort the word according to freq from top to low.*/

/** Initializes a new DictionaryTrie. */
DictionaryTrie::DictionaryTrie() : root(nullptr) {}

/** Insert a word with its frequency into the DictionaryTrie.
 *  Return true if the word was inserted successfully,
 *  or false if given string is empty or already inserted.
 */
bool DictionaryTrie::insert(string word, unsigned int freq) {
    if (word.empty()) {
        return false;
    }
    if (root == nullptr) {
        root = new TrieNode();
    }
    TrieNode* curr = root;
    for (int i = 0; i < word.length(); i++) {
        if (curr->map.find(word[i]) == curr->map.end()) {
            // current char has not been inserted into trie node yet.
            curr->map[word[i]] = new TrieNode();
        }  // let curr point to the next node
        curr = curr->map[word[i]];
    }
    if (curr->frequency != 0) {  // given string already inserted
        return false;
    } else {
        curr->frequency = freq;
        updateMax(word, freq);
        return true;
    }
}

void DictionaryTrie::updateMax(string word, unsigned int freq) {
    TrieNode* curr = root;
    for (int i = 0; i < word.length(); i++) {
        if (curr->maxBelow < freq) {
            curr->maxBelow = freq;
        }
        curr = curr->map[word[i]];
    }
}

/** Return true if the words in the DictionaryTrie and
 *  false otherwise. */
bool DictionaryTrie::find(string word) const {
    if (word.empty() || root == nullptr) {
        return false;
    }
    TrieNode* curr = root;
    for (int i = 0; i < word.length(); i++) {
        if (curr->map.find(word[i]) == curr->map.end()) {
            return false;
        }
        curr = curr->map[word[i]];
    }
    return curr->frequency != 0;
}

/** Return a vector holding up to numCompletions of the most frequent
 * completions of prefix, and the completions must be valid words in the
 * dictionary. These completions should be listed from most to least frequent.
 * If there are fewer than numCompletions legal completions, this method should
 * return a vector with as many completions as possible. If no completions
 * exist, the nthe fucntion should return a vector of size 0.
 */
vector<string> DictionaryTrie::predictCompletions(string prefix,
                                                  unsigned int numCompletions) {
    if (numCompletions == 0 || root == nullptr || prefix.empty()) {
        return {};
    }
    TrieNode* curr = root;
    for (int i = 0; i < prefix.length(); i++) {
        if (curr->map.find(prefix[i]) == curr->map.end()) {
            return {};
        }
        curr = curr->map[prefix[i]];
    }  // curr points to prefix node

    my_min_queue wordQueue;

    collect(prefix, wordQueue, curr, prefix, numCompletions);
    return popVectorReverse(wordQueue, numCompletions);
}

/** Helper function for predictCompletions.
 *  Returns a priority queue of pairs of frequency and word.
 */
void DictionaryTrie::collect(string s, my_min_queue& q, TrieNode* node,
                             string prefix, int num) {
    if (node == nullptr) return;
    if (node->frequency != 0) {
        if (q.size() < num) {
            if (s == prefix) {
                q.push(make_pair(numeric_limits<unsigned int>::max(), s));
            } else {
                q.push(make_pair(node->frequency, s));
            }
        } else {
            if (q.top().first < node->frequency) {
                q.pop();
                q.push(make_pair(node->frequency, s));
            }
        }
    }
    if (q.size() == num && node->maxBelow < q.top().first) {
        return;  // only prune when queue is full
    }
    for (pair<char, TrieNode*> element : node->map) {
        s.push_back(element.first);
        collect(s, q, element.second, prefix, num);
        s.pop_back();
    }
}

/** Return a vector of strings from PQ.
 */
vector<string> DictionaryTrie::popVector(my_max_queue& q, int num) {
    vector<string> vec;
    int numWord = q.size();
    for (int i = 0; i < min(num, numWord); i++) {
        pair<int, string> p = q.top();
        q.pop();
        vec.push_back(p.second);
    }
    return vec;
}

vector<string> DictionaryTrie::popVectorReverse(my_min_queue& q, int num) {
    vector<string> vec;
    int numWord = q.size();
    for (int i = 0; i < min(num, numWord); i++) {
        pair<int, string> p = q.top();
        q.pop();
        vec.push_back(p.second);
    }
    reverse(vec.begin(), vec.end());
    return vec;
}

/** Allow multiple wildcard prediction in your autocompleter.
 *  Return a vector holding up to numCompletions of the most frequent valid
 *  completions of pattern.
 */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
    if ((numCompletions == 0) || root == nullptr || pattern.empty()) {
        return {};
    }
    my_max_queue wordQueue;
    string s = "";
    collectUnderscore(root, s, pattern, wordQueue);
    return popVector(wordQueue, numCompletions);
}

/** Helper function for predictUnderscores.
 *  Recursively add the string that satisfy the pattern to the PQ with
 *  backtracking.
 */
void DictionaryTrie::collectUnderscore(TrieNode* n, string s, string pattern,
                                       my_max_queue& q) {
    if (n == nullptr) return;

    if (s.length() == pattern.length()) {
        if (n->frequency != 0) {
            q.push(make_pair(n->frequency, s));
        } else {
            return;
        }
    }
    char c = pattern[s.length()];
    if (c == '_') {
        for (pair<char, TrieNode*> element : n->map) {
            s.push_back(element.first);
            collectUnderscore(element.second, s, pattern, q);
            s.pop_back();
        }
    } else {
        s.push_back(c);
        collectUnderscore(n->map[c], s, pattern, q);
        s.pop_back();
    }
}

/** Destructor to avoid memory leaks. */
DictionaryTrie::~DictionaryTrie() { deleteAll(root); }

/** Helper funciton for destructor. */
void DictionaryTrie::deleteAll(TrieNode* node) {
    if (node == nullptr) {
        return;
    }
    for (pair<char, TrieNode*> element : node->map) {
        deleteAll(element.second);
    }
    delete node;
}
