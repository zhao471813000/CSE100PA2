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
    vector<string> vec = {"apple", "app"};
    vector<string> returnVec = dict.predictCompletions("ap", 10);
    ASSERT_EQ(returnVec, vec);
}

TEST(DictTrieTests, MORE_TEST) {
    DictionaryTrie dict;
    ASSERT_EQ(dict.insert("vice versa", 2), true);
    ASSERT_EQ(dict.insert("vice president", 4), true);
    ASSERT_EQ(dict.insert("vice admiral", 4), true);
    ASSERT_EQ(dict.insert("vice", 1), true);

    vector<string> vec1 = {"vice", "vice admiral", "vice president"};
    vector<string> returnVec1 = dict.predictCompletions("vice", 3);
    ASSERT_EQ(returnVec1, vec1);

    vector<string> vec2 = {"vice admiral", "vice president", "vice versa"};
    vector<string> returnVec2 = dict.predictCompletions("vice ", 3);
    ASSERT_EQ(returnVec2, vec2);

    vector<string> vec3 = {"vice admiral"};
    vector<string> returnVec3 = dict.predictCompletions("vice a", 3);
    ASSERT_EQ(returnVec3, vec3);

    vector<string> vec4 = {};
    vector<string> returnVec4 = dict.predictCompletions("apple", 3);
    ASSERT_EQ(returnVec4, vec4);
}
TEST(DictTrieTests, PREDICTUNDERSCORES1_TEST) {
    DictionaryTrie dict;
    vector<string> vecempty = {};
    ASSERT_EQ(dict.predictUnderscores("ap_", 6), vecempty);
    dict.insert("app", 2);
    dict.insert("apb", 3);
    dict.insert("apc", 34);
    dict.insert("apg", 1);
    dict.insert("apf", 9);
    dict.insert("apr", 7);

    dict.insert("apefd", 4);
    dict.insert("apdxz", 6);
    dict.insert("apvds", 10);
    dict.insert("apsxf", 26);
    dict.insert("apxdf", 30);
    dict.insert("apubj", 76);
    ASSERT_EQ(dict.predictUnderscores("", 6), vecempty);
    vector<string> vec6 = dict.predictUnderscores("ap_", 6);
    vector<string> returnvec6 = {"apc", "apf", "apr", "apb", "app", "apg"};
    ASSERT_EQ(returnvec6, vec6);
    vector<string> vec7 = dict.predictUnderscores("_p___", 6);
    vector<string> returnvec7 = {"apubj", "apxdf", "apsxf",
                                 "apvds", "apdxz", "apefd"};
    ASSERT_EQ(returnvec7, vec7);
}

TEST(DictTrieTests, SAME_FREQ_TEST) {
    DictionaryTrie dict;
    dict.insert("a", 1);
    dict.insert("ab", 2);
    dict.insert("abnormal", 2);
    dict.insert("absolute", 2);
    dict.insert("acne", 2);
    dict.insert("best", 2);
    vector<string> vec = dict.predictCompletions("a", 6);
    vector<string> returnvec = {"a", "ab", "abnormal", "absolute", "acne"};
    ASSERT_EQ(returnvec, vec);

    vector<string> vec1 = dict.predictUnderscores("ab______", 6);
    vector<string> returnvec1 = {"abnormal", "absolute"};
    ASSERT_EQ(returnvec1, vec1);
}
