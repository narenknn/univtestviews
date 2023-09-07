#include <string>
#include <iostream>
#include <gtest/gtest.h>

#include "nlohmann/json.hpp"
#include "top/main.h"

void
TextInputViewTest::view_test(nlohmann::json& retj)
{
  ASSERT_TRUE(retj.is_object()) << ": Expecting object " << retj.dump();
  ASSERT_TRUE(retj.contains("text")) << retj.dump();
  ASSERT_TRUE(retj.contains("textinput")) << retj.dump();
  ASSERT_TRUE(retj.contains("correct_ans")) << retj.dump();
  ASSERT_TRUE(retj["text"].is_string()) << retj.dump();
  ASSERT_TRUE(retj["textinput"].is_array()) << retj.dump();
  ASSERT_TRUE(retj["correct_ans"].is_array()) << retj.dump();
  ASSERT_GT(retj["textinput"].size(), 0) << retj.dump();
  ASSERT_EQ(retj["textinput"].size(), retj["correct_ans"].size()) << retj.dump();
  for (auto i=retj["textinput"].size(); i; i--) {
    ASSERT_TRUE(retj["textinput"][i-1].is_string()) << retj["textinput"][i-1].dump();
    /* ans can be null or expected string */
    if (retj["correct_ans"][i-1].is_null()) continue;
    ASSERT_TRUE(retj["correct_ans"][i-1].is_string()) << retj["correct_ans"][i-1].dump();
    ASSERT_EQ(retj["textinput"][i-1], "_") << retj["textinput"][i-1].dump();
  }
}
