#include <string>
#include <iostream>
#include <gtest/gtest.h>

#include "nlohmann/json.hpp"
#include "top/main.h"

void
MultiInputTableViewTest::view_test(nlohmann::json& confj, nlohmann::json& retj)
{
  /* expecting object here having certain keys */
  ASSERT_TRUE(retj.is_object()) << ": Expecting object " << retj.dump();
  ASSERT_TRUE(retj.contains("text")) << retj.dump();
  ASSERT_TRUE(retj.contains("th")) << retj.dump();
  ASSERT_TRUE(retj.contains("htabledata")) << retj.dump();
  ASSERT_TRUE(retj.contains("correct_ans")) << retj.dump();
  ASSERT_GT(retj["htabledata"].size(), 0) << retj["htabledata"].dump();
  ASSERT_EQ(retj["htabledata"].size(), retj["correct_ans"].size()) << retj.dump();
  auto ncol = retj["th"].size();
  ASSERT_GT(ncol, 0) << retj["th"].dump();

  /* table data should be rectangle */
  for(const auto &a: retj["htabledata"]) {
    ASSERT_TRUE(a.is_array()) << ": Expecting array " << a.dump();
    ASSERT_EQ(a.size(), ncol) << a.dump();
  }
  for(const auto &a: retj["correct_ans"]) {
    ASSERT_TRUE(a.is_array()) << ": Expecting array " << a.dump();
    ASSERT_EQ(a.size(), ncol) << a.dump();
  }

  /* when expecting answer, expect '_' in table data */
  for(auto i = retj["correct_ans"].size(); i; i--) {
    for(auto j = retj["correct_ans"][i-1].size(); j; j--) {
      /* both null or both same string, then skip */
      if (retj["correct_ans"][i-1][j-1].is_null() and
          retj["htabledata"][i-1][j-1].is_null())
        continue;
      else if (retj["correct_ans"][i-1][j-1].is_string() and
               retj["htabledata"][i-1][j-1].is_string() and
               (retj["correct_ans"][i-1][j-1].get<std::string>() ==
                retj["htabledata"][i-1][j-1].get<std::string>())) {
        continue;
      }
      if (! retj["correct_ans"][i-1][j-1].is_null())
        ASSERT_EQ(retj["htabledata"][i-1][j-1], "_") << "i:" << (i-1) << " j:" << (j-1) << " retj:" << retj << std::endl;
      else
        ASSERT_TRUE(retj["htabledata"][i-1][j-1].is_string()) << "i:" << (i-1) << " j:" << (j-1) << " retj:" << retj << std::endl;
    }
  }

  /* when '_' in table data, expect answer */
  for(auto i = retj["correct_ans"].size(); i; i--) {
    for(auto j = retj["correct_ans"][i-1].size(); j; j--) {
      /* both null or both same string, then skip */
      if (retj["correct_ans"][i-1][j-1].is_null() and
          retj["htabledata"][i-1][j-1].is_null())
        continue;
      else if (retj["correct_ans"][i-1][j-1].is_string() and
               retj["htabledata"][i-1][j-1].is_string() and
               (retj["correct_ans"][i-1][j-1].get<std::string>() ==
                retj["htabledata"][i-1][j-1].get<std::string>())) {
        continue;
      }
      if ("_" == retj["htabledata"][i-1][j-1].get<std::string>()) {
        ASSERT_TRUE(retj["correct_ans"][i-1][j-1].is_string()) << "i:" << (i-1) << " j:" << (j-1) << " retj:" << retj << std::endl;
      } else
        ASSERT_TRUE(retj["correct_ans"][i-1][j-1].is_null()) << "i:" << (i-1) << " j:" << (j-1) << " retj:" << retj << std::endl;
    }
  }
}
