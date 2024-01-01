#include <string>
#include <iostream>
#include <gtest/gtest.h>

#include "nlohmann/json.hpp"
#include "top/main.h"

void
D3OnlyViewTest::view_test(nlohmann::json& confj, nlohmann::json& retj)
{
  /* only one answer & question array is 2 */
  ASSERT_TRUE(retj["datastr"].is_object()) << retj.dump();
  ASSERT_GT(retj["datastr"]["width"].get<uint32_t>(), 0) << retj.dump();
  ASSERT_GT(retj["datastr"]["height"].get<uint32_t>(), 0) << retj.dump();
  ASSERT_TRUE(retj["datastr"]["correct_ans"].is_array()) << retj.dump();
}
