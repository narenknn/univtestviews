#include <string>
#include <random>
#include <stdexcept>

#include <boost/algorithm/string.hpp>

#include "nlohmann/json.hpp"
#include "top/genmain.h"

const std::vector<std::string> Genmain::htmlColors { "HotPink", "DeepPink", "PaleVioletRed", "MediumVioletRed", "LightSalmon", "Salmon", "DarkSalmon", "LightCoral", "IndianRed", "Crimson", "FireBrick", "DarkRed", "Red", "OrangeRed", "Tomato", "Coral", "DarkOrange", "Orange", "DarkKhaki", "Gold", "BurlyWood", "Tan", "RosyBrown", "SandyBrown", "Goldenrod", "DarkGoldenrod", "Peru", "Chocolate", "SaddleBrown", "Sienna", "Brown", "Maroon", "DarkOliveGreen", "Olive", "OliveDrab", "YellowGreen", "LimeGreen", "DarkSeaGreen", "MediumSeaGreen", "SeaGreen", "ForestGreen", "Green", "DarkGreen", "MediumAquamarine", "Turquoise", "MediumTurquoise", "DarkTurquoise", "LightSeaGreen", "CadetBlue", "DarkCyan", "Teal", "DeepSkyBlue", "DodgerBlue", "CornflowerBlue", "SteelBlue", "RoyalBlue", "Blue", "MediumBlue", "DarkBlue", "Navy", "MidnightBlue", "Violet", "Orchid", "Fuchsia", "Magenta", "MediumOrchid", "MediumPurple", "BlueViolet", "DarkViolet", "DarkOrchid", "DarkMagenta", "Purple", "Indigo", "DarkSlateBlue", "RebeccaPurple", "SlateBlue", "MediumSlateBlue", "Gray", "DimGray", "LightSlateGray", "SlateGray", "DarkSlateGray", "Black" };
const std::vector<std::string> Genmain::htmlBackgroundColors { "LightYellow", "LemonChiffon", "LightGoldenrodYellow", "PapayaWhip", "Cornsilk", "BlanchedAlmond", "Bisque", "NavajoWhite", "lightcyan", "White", "Snow", "Honeydew", "MintCream", "Azure", "AliceBlue", "GhostWhite", "WhiteSmoke", "Seashell", "Beige", "OldLace", "FloralWhite", "Ivory", "AntiqueWhite", "Linen", "LavenderBlush", "MistyRose" };
const std::vector<std::string> Genmain::symbols {"symbolCircle", "symbolCross", "symbolDiamond", "symbolSquare", "symbolStar", "symbolTriangle", "symbolWye"};

std::unique_ptr<std::unordered_map<std::string, GenMod *> > all_mods;

std::string
genmain(std::string s_config)
{
  nlohmann::json config = nlohmann::json::parse(s_config);
  std::vector<std::string> cn_arr;
  GenMod* comp;

  /* get the comp */
  boost::algorithm::split(cn_arr, config["controller"].get<std::string>(), boost::is_any_of("-"));
  if (all_mods->find(cn_arr[0]) == all_mods->end())
    goto genmain_return;

  /* */
  comp = (*all_mods)[cn_arr[0]];
  if (config.contains("seed")) {
    comp->seed(config["seed"].get<std::uint32_t>());
  }
  return comp->gen(cn_arr[1], config);

 genmain_return:
  return "{\"text\":\"Wrong setup, test was not generated!\"}";
}

std::string
checkmain(std::string s_config, std::string s_question, std::string s_ans)
{
  nlohmann::json config = nlohmann::json::parse(s_config);
  nlohmann::json question = nlohmann::json::parse(s_question);
  nlohmann::json ans = nlohmann::json::parse(s_ans);
  std::vector<std::string> cn_arr;
  GenMod* comp;

  /* get the comp */
  boost::algorithm::split(cn_arr, config["controller"].get<std::string>(), boost::is_any_of("-"));
  if (all_mods->find(cn_arr[0]) == all_mods->end())
    goto checkmain_return;

  /* */
  comp = (*all_mods)[cn_arr[0]];
  return comp->check(cn_arr[1], config, question, ans);

 checkmain_return:
  return "{\"text\":\"Wrong setup, check was not done!\"}";
}


std::string
GenMod::gen(const std::string cname, nlohmann::json& config)
{
  /* */
  nlohmann::json ret;

  for (uint32_t ui=0; ui<4; ui++) {
    try {
      if (controllers.find(cname) != controllers.end())
        controllers[cname]->gen(ret, rand, config);
    } catch(std::runtime_error& e) {
      continue;
    }
  }

  return ret.dump();
}

std::string
GenMod::check(const std::string cname, nlohmann::json& config, nlohmann::json& question, nlohmann::json& ans)
{
  /* */
  nlohmann::json ret;

  ret["result"] = false;
  if (controllers.find(cname) != controllers.end())
    controllers[cname]->check(ret, config, question, ans);

  return ret.dump();
}

namespace MathsChecks {

  void
  check_multiarray(nlohmann::json& ret, nlohmann::json& config, nlohmann::json& q, nlohmann::json& ans)
  {
    ret["result"] = true;
    for(auto i = q["correct_ans"].size(); i; i--) {
      for(auto j = q["correct_ans"][i-1].size(); j; j--) {
        if (! q["correct_ans"][i-1][j-1].is_null())
          if (q["correct_ans"][i-1][j-1].is_string() && ans["ans"][i-1][j-1].is_string()) {
            if (q["correct_ans"][i-1][j-1].get<std::string>() != ans["ans"][i-1][j-1].get<std::string>())
              ret["result"] = false;
          } else if (q["correct_ans"][i-1][j-1].is_boolean() && ans["ans"][i-1][j-1].is_boolean()) {
            if (q["correct_ans"][i-1][j-1].get<bool>() != ans["ans"][i-1][j-1].get<bool>())
              ret["result"] = false;
          } else if (q["correct_ans"][i-1][j-1].is_number() && ans["ans"][i-1][j-1].is_number()) {
            if (q["correct_ans"][i-1][j-1].get<float>() != ans["ans"][i-1][j-1].get<float>())
              ret["result"] = false;
          } else if (q["correct_ans"][i-1][j-1].is_null() && ans["ans"][i-1][j-1].is_null()) {
          } else
            ret["result"] = false;
      }
    }
  }

}

