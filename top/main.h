class ViewTest {
public:
  virtual void view_test(nlohmann::json& retj) = 0;
};

class ControllerTest : public ::testing::Test {
public:
  static const std::unordered_map<std::string, std::unique_ptr<ViewTest> > view_tests;
  typedef void controller_test_f(nlohmann::json& confj, nlohmann::json& retj, bool debug);
  virtual void runtest(const std::string conf, controller_test_f controller_test, uint32_t times=20, bool debug=false);
};

#include "multiinputs.h"
#include "multiinputtable.h"
#include "arrayselect.h"
#include "btnchoice.h"
#include "skillbuilders.h"
