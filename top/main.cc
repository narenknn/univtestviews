#include <string>
#include <iostream>
#include <gtest/gtest.h>

#include "nlohmann/json.hpp"
#include "top/main.h"

extern std::string
genmain(std::string s_config);

void
ViewTest::runtest(const std::string conf, controller_test_f controller_test, bool debug)
{
  /* should be a json */
  for (auto i=20; i; i--) {
    auto confj = nlohmann::json::parse(conf);
    std::string ret1 = genmain(conf);
    if (debug) {
      ASSERT_TRUE(false) << ret1;
    }
    ASSERT_TRUE(nlohmann::json::accept(ret1));
    // auto retj = nlohmann::json::parse(ret1);
    // view_test(retj);
    // controller_test(confj, retj, debug);
  }
}

int
main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
