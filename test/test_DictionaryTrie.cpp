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
    ASSERT_EQ(dict.insert("app", 2), true);
    ASSERT_EQ(dict.insert("apple", 3), true);
    vector<string> vec1 = {"apple", "app"};
    vector<string> returnVec = dict.predictCompletions("ap", 10);
    ASSERT_EQ(returnVec, vec1);
}
TEST(DictTrieTests, MORE_TEST) {
    DictionaryTrie dict;
    ASSERT_EQ(dict.insert("annie", 2), true);
    ASSERT_EQ(dict.insert("get", 4), true);
    ASSERT_EQ(dict.insert("an", 6), true);
    ASSERT_EQ(dict.insert("apple", 10), true);
    ASSERT_EQ(dict.insert("and", 15), true);
    ASSERT_EQ(dict.insert("ann", 20), true);
    ASSERT_EQ(dict.insert("sleep", 1), true);
    ASSERT_EQ(dict.insert("in", 1), true);
    ASSERT_EQ(dict.insert("attic", 1), true);
    vector<string> vec1 = {"ann", "and", "an", "annie"};
    vector<string> vec2 = {"ann", "and"};
    ASSERT_EQ(dict.predictCompletions("an", 10), vec1);
    ASSERT_EQ(dict.predictCompletions("an", 2), vec2);
}
