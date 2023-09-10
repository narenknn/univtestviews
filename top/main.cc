#include <string>
#include <iostream>
#include <gtest/gtest.h>

#include "nlohmann/json.hpp"
#include "top/main.h"

extern std::string
genmain(std::string s_config);

extern std::string
checkmain(std::string s_config, std::string ques, std::string ans);

std::unordered_map<std::string, std::shared_ptr<ViewTest> > ControllerTest::view_tests
{
  {"ArraySelectViewTest", std::make_shared<ArraySelectViewTest>()},
  {"BtnChoiceViewTest", std::make_shared<BtnChoiceViewTest>()},
  {"MultiInputsViewTest", std::make_shared<MultiInputsViewTest>()},
  {"MultiInputTableViewTest", std::make_shared<MultiInputTableViewTest>()},
  {"SkillBuildersViewTest", std::make_shared<SkillBuildersViewTest>()},
};

void
ControllerTest::runtest(const std::string conf, controller_test_f controller_test, uint32_t times, bool debug)
{
  /* should be a json */
  for (; times; times--) {
    auto confj = nlohmann::json::parse(conf);
    std::string ret1 = genmain(conf);
    if (debug) {
      ASSERT_TRUE(false) << ret1;
    }
    ASSERT_TRUE(nlohmann::json::accept(ret1)) << "genmain() didnt return a valid JSON!";
    auto retj = nlohmann::json::parse(ret1);
    auto vname {confj["test"].get<std::string>()};
    if ((0 == vname.length()) || (view_tests.end() == view_tests.find(vname))) {
      ASSERT_TRUE(false) << "Couldnt find the view for conf : " << conf;
    } else
      view_tests[vname]->view_test(confj, retj);
    controller_test(confj, retj, debug);
  }
}

int
main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
