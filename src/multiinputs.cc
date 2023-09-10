#include <string>
#include <iostream>
#include <vector>
#include <gtest/gtest.h>

#include "nlohmann/json.hpp"
#include "top/main.h"

void
MultiInputsViewTest::view_test(nlohmann::json& confj, nlohmann::json& retj)
{
  ASSERT_TRUE(retj.is_object()) << ": Expecting object " << retj.dump();
  ASSERT_TRUE(retj.contains("text")) << retj.dump();
  ASSERT_TRUE(retj.contains("correct_ans")) << retj.dump();
  ASSERT_TRUE(retj["text"].is_string()) << retj.dump();
  ASSERT_TRUE(retj["correct_ans"].is_array()) << retj.dump();
  ASSERT_TRUE(retj.contains("multiinput") or retj.contains("textinput")) << retj.dump();

  /* check */
  const std::vector<std::string> inputs{"multiinput", "textinput"};
  for (const auto &inp: inputs) {
    if (! retj.contains(inp)) continue;
    ASSERT_TRUE(retj[inp].is_array()) << retj.dump();
    ASSERT_GT(retj[inp].size(), 0) << retj.dump();
    ASSERT_EQ(retj[inp].size(), retj["correct_ans"].size()) << retj.dump();
    for (auto &mi: retj[inp])
      ASSERT_TRUE(mi.is_array()) << mi.dump();
    for (auto &ca: retj["correct_ans"])
      ASSERT_TRUE(ca.is_array()) << ca.dump();
    for (auto i=retj[inp].size(); i; i--) {
      ASSERT_EQ(retj[inp][i-1].size(), retj["correct_ans"][i-1].size()) << retj.dump();
      for (auto j=retj[inp][i-1].size(); j; j--) {
        ASSERT_TRUE(retj[inp][i-1][j-1].is_string()) << retj.dump();
        if ("_" == retj[inp][i-1][j-1].get<std::string>()) {
          ASSERT_TRUE(retj["correct_ans"][i-1][j-1].is_string()) << retj.dump();
        }
        if (retj["correct_ans"][i-1][j-1].is_null()) {
          ASSERT_TRUE(retj[inp][i-1][j-1].is_string()) << retj.dump();
          ASSERT_NE(retj[inp][i-1][j-1].get<std::string>(), "_") << retj.dump();
        }
      }
    }
  }
}
