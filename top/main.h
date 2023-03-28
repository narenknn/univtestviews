class ViewTest : public ::testing::Test {
public:
  virtual void view_test(nlohmann::json& retj) = 0;
  typedef void controller_test_f(nlohmann::json& confj, nlohmann::json& retj, bool debug);
  virtual void runtest(const std::string conf, controller_test_f controller_test, bool debug=false);
};

#include "multiinputs.h"
#include "multiinputtable.h"
