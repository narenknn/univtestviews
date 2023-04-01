#include <string>
#include <iostream>
#include <gtest/gtest.h>

#include "nlohmann/json.hpp"
#include "top/main.h"

void
BtnChoiceViewTest::view_test(nlohmann::json& retj)
{
  /* only one answer & question array is 2 */
  ASSERT_TRUE(retj["btnchoice"].is_array()) << retj.dump();
  ASSERT_GT(retj["btnchoice"].size(), 0) << retj.dump();
  ASSERT_TRUE(retj["correct_ans"].is_array()) << retj.dump();
  for (auto &a: retj["correct_ans"]) {
    ASSERT_TRUE(a.is_number()) << retj.dump();
    ASSERT_LT(a.get<uint32_t>(), retj["btnchoice"].size()) << retj.dump();
  }
}
