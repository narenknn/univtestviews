#include <string>
#include <iostream>
#include <gtest/gtest.h>

#include "nlohmann/json.hpp"
#include "main.h"

void
MultiInputsViewTest::view_test(nlohmann::json& retj)
{
  ASSERT_TRUE(retj.is_object()) << ": Expecting object " << retj.dump();
  ASSERT_TRUE(retj.contains("text")) << retj.dump();
  ASSERT_TRUE(retj.contains("multiinput")) << retj.dump();
  ASSERT_TRUE(retj.contains("correct_ans")) << retj.dump();
  ASSERT_TRUE(retj["text"].is_string()) << retj.dump();
  ASSERT_TRUE(retj["multiinput"].is_array()) << retj.dump();
  ASSERT_TRUE(retj["correct_ans"].is_array()) << retj.dump();
  ASSERT_GT(retj["multiinput"].size(), 0) << retj.dump();
  ASSERT_EQ(retj["multiinput"].size(), retj["correct_ans"].size()) << retj.dump();
  for (auto &mi: retj["multiinput"])
    ASSERT_TRUE(mi.is_array()) << mi.dump();
  for (auto &ca: retj["correct_ans"])
    ASSERT_TRUE(ca.is_array()) << ca.dump();
  for (auto i=retj["multiinput"].size(); i; i--) {
    ASSERT_EQ(retj["multiinput"][i-1].size(), retj["correct_ans"][i-1].size()) << retj.dump();
    for (auto j=retj["multiinput"][i-1].size(); j; j--) {
      ASSERT_TRUE(retj["multiinput"][i-1][j-1].is_string()) << retj.dump();
      if ("_" == retj["multiinput"][i-1][j-1].get<std::string>()) {
        ASSERT_TRUE(retj["correct_ans"][i-1][j-1].is_string()) << retj.dump();
      }
      if (retj["correct_ans"][i-1][j-1].is_null()) {
        ASSERT_TRUE(retj["multiinput"][i-1][j-1].is_string()) << retj.dump();
        ASSERT_NE(retj["multiinput"][i-1][j-1].get<std::string>(), "_") << retj.dump();
      }
    }
  }
}
