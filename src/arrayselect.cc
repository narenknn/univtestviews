#include <string>
#include <iostream>
#include <gtest/gtest.h>

#include "nlohmann/json.hpp"
#include "top/main.h"

void
ArraySelectViewTest::view_test(nlohmann::json& confj, nlohmann::json& retj)
{
  /* only one answer & question array is 2 */
  ASSERT_TRUE(retj["datastr"].is_object()) << retj.dump();
  ASSERT_TRUE(retj["datastr"]["size"].is_number()) << retj.dump();
  auto n = retj["datastr"]["size"].get<uint32_t>();
  if (retj["datastr"].contains("fill")) {
    ASSERT_EQ(retj["datastr"]["fill"].size(), n*n) << retj.dump();
    for (auto &v: retj["datastr"]["fill"])
      ASSERT_TRUE(v.is_boolean()) << retj.dump();
  }
  if (retj.contains("status_answer")) {
    ASSERT_EQ(retj["status_answer"].size(), n*n) << retj.dump();
    for (auto &v: retj["status_answer"])
      ASSERT_TRUE(v.is_boolean()) << retj.dump();
  }
}
