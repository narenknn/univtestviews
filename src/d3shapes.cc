#include <string>
#include <iostream>
#include <gtest/gtest.h>

#include "nlohmann/json.hpp"
#include "top/main.h"

void
D3shapesViewTest::view_test(nlohmann::json& confj, nlohmann::json& retj)
{
  /* only one answer & question array is 2 */
  ASSERT_TRUE(retj["datastr"].is_object()) << retj.dump();
  ASSERT_TRUE(retj["datastr"]["os"].is_array()) << retj.dump();
  ASSERT_TRUE(retj["datastr"]["height"].is_number()) << retj.dump();
  ASSERT_TRUE(retj["datastr"]["width"].is_number()) << retj.dump();
  ASSERT_TRUE(retj["datastr"]["xticks"].is_number()) << retj.dump();
  ASSERT_TRUE(retj["datastr"]["yticks"].is_number()) << retj.dump();
  ASSERT_TRUE(retj["datastr"]["candot"].is_boolean()) << retj.dump();
  ASSERT_GT(retj["datastr"]["os"].size(), 0) << retj.dump();
  for (auto n = retj["datastr"]["os"].size(); n; n--) {
    ASSERT_TRUE(retj["datastr"]["os"][n-1]["color"].is_string()) << retj.dump();
    ASSERT_TRUE(retj["datastr"]["os"][n-1]["type"].is_string()) << retj.dump();
  }
}
