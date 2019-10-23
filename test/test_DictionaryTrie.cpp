/**
 * This is test file for DictionaryTrie.
 *
 * Author: Kexin Hong A53311871, Dingqian Zhao A53319585.
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "DictionaryTrie.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/* Empty test */
TEST(DictTrieTests, EMPTY_TEST) {
    DictionaryTrie dict;
    ASSERT_EQ(dict.find("abrakadabra"), false);
}

/* Simple test for insert and find. */
TEST(DictTrieTests, INSERT_FIND_TEST) {
    DictionaryTrie dict;
    ASSERT_EQ(dict.insert("abrakadabra", 10), true);
    ASSERT_EQ(dict.find("abrakadabra"), true);
}

/* PredictCompletions test. */
TEST(DictTrieTests, PREDICT_COMPLETIONS_TEST) {
    DictionaryTrie dict;
    ASSERT_TRUE(dict.insert("app", 2));
    ASSERT_FALSE(dict.insert("app", 2));
    ASSERT_TRUE(dict.insert("apple", 3));
    ASSERT_FALSE(dict.find("truth"));
    ASSERT_TRUE(dict.insert("truth", 5));
    vector<string> vec1 = {"apple", "app"};
    vector<string> returnVec = dict.predictCompletions("ap", 10);
    ASSERT_EQ(returnVec, vec1);
}

// TEST(DictTrieTests, MORE_DATA_TEST) {
//     DictionaryTrie dict;
//     ifstream in;
//     in.open("unique_freq_dict.txt", ios::binary);
//     ASSERT_TRUE(in.is_open());
//     in.seekg(0, ios_base::end);
//     unsigned int len = in.tellg();
//     ASSERT_NE(len, 0);
//     Utils::loadDict(dict, in);
// }
