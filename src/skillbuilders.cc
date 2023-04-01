#include <string>
#include <iostream>
#include <gtest/gtest.h>

#include "nlohmann/json.hpp"
#include "top/main.h"

void
SkillBuildersViewTest::view_test(nlohmann::json& retj)
{
  /* only one answer & question array is 2 */
  ASSERT_EQ(retj["multiinput"][0].size(), 2) << retj.dump();
  ASSERT_EQ(retj["correct_ans"][0].size(), 2) << retj.dump();
}
