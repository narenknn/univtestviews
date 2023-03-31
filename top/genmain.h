class RandGenerator {
public:
  std::mt19937 rng;
  std::uniform_int_distribution<uint32_t> uint_dist;

  RandGenerator(uint32_t seed) {
    rng.seed(seed);
  }
  uint32_t get() {
    return uint_dist(rng);
  }
  uint32_t get_range(uint32_t min, uint32_t max) {
    uint32_t r = get() + min;
    return r % max;
  }
  uint32_t get_digits(uint32_t min, uint32_t max) {
    uint32_t min_div = 1, max_div = 1, r = get();
    for (; min; min--) min_div *= 10;
    for (; max; max--) max_div *= 10;
    auto min_val = r % min_div;
    auto max_val = r % max_div;
    return (max_val < min_val) ? min_val : max_val;
  }
};

class Controller {
public:
  virtual void gen(nlohmann::json& ret, std::shared_ptr<RandGenerator> rand, nlohmann::json& config) = 0;
  virtual void check(nlohmann::json& ret, nlohmann::json& config, nlohmann::json& question, nlohmann::json& ans) = 0;
  virtual ~Controller() {}
};

class GenMod {
public:
  static std::unordered_map<std::string, GenMod *> all_mods;
  std::unordered_map<std::string, std::unique_ptr<Controller> > controllers;
  std::shared_ptr<RandGenerator> rand;

  GenMod(const std::string cname, std::uint32_t seed = std::random_device{}()) :
    rand(std::make_shared<RandGenerator> (seed))
  {
    all_mods.emplace(cname, this);
  }

  void seed(uint32_t sv)
  {
    rand->rng.seed(sv);
  }

  virtual std::string gen(const std::string cname, nlohmann::json& config);
  virtual std::string check(const std::string cname, nlohmann::json& config, nlohmann::json& question, nlohmann::json& ans);
};

namespace Genmain {

  extern const std::vector<std::string> htmlColors;
  extern const std::vector<std::string> htmlBackgroundColors;
  extern const std::vector<std::string> symbols;

  static const std::string __className__(const std::string& prettyFunction)
  {
    size_t colons = prettyFunction.rfind("::");
    if (colons == std::string::npos)
      return "::";
    return prettyFunction.substr(0, colons);
  }

}

#define __CLASS_NAME__ Genmain::__className__(__PRETTY_FUNCTION__)
