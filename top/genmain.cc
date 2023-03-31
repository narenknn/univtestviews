#include <string>
#include <random>

#include <boost/algorithm/string.hpp>

#include "nlohmann/json.hpp"
#include "top/genmain.h"

std::unordered_map<std::string, GenMod *> GenMod::all_mods;

const std::vector<std::string> Genmain::htmlColors { "HotPink", "DeepPink", "PaleVioletRed", "MediumVioletRed", "LightSalmon", "Salmon", "DarkSalmon", "LightCoral", "IndianRed", "Crimson", "FireBrick", "DarkRed", "Red", "OrangeRed", "Tomato", "Coral", "DarkOrange", "Orange", "DarkKhaki", "Gold", "BurlyWood", "Tan", "RosyBrown", "SandyBrown", "Goldenrod", "DarkGoldenrod", "Peru", "Chocolate", "SaddleBrown", "Sienna", "Brown", "Maroon", "DarkOliveGreen", "Olive", "OliveDrab", "YellowGreen", "LimeGreen", "DarkSeaGreen", "MediumSeaGreen", "SeaGreen", "ForestGreen", "Green", "DarkGreen", "MediumAquamarine", "Turquoise", "MediumTurquoise", "DarkTurquoise", "LightSeaGreen", "CadetBlue", "DarkCyan", "Teal", "DeepSkyBlue", "DodgerBlue", "CornflowerBlue", "SteelBlue", "RoyalBlue", "Blue", "MediumBlue", "DarkBlue", "Navy", "MidnightBlue", "Violet", "Orchid", "Fuchsia", "Magenta", "MediumOrchid", "MediumPurple", "BlueViolet", "DarkViolet", "DarkOrchid", "DarkMagenta", "Purple", "Indigo", "DarkSlateBlue", "RebeccaPurple", "SlateBlue", "MediumSlateBlue", "Gray", "DimGray", "LightSlateGray", "SlateGray", "DarkSlateGray", "Black" };
const std::vector<std::string> Genmain::htmlBackgroundColors { "LightYellow", "LemonChiffon", "LightGoldenrodYellow", "PapayaWhip", "Cornsilk", "BlanchedAlmond", "Bisque", "NavajoWhite", "lightcyan", "White", "Snow", "Honeydew", "MintCream", "Azure", "AliceBlue", "GhostWhite", "WhiteSmoke", "Seashell", "Beige", "OldLace", "FloralWhite", "Ivory", "AntiqueWhite", "Linen", "LavenderBlush", "MistyRose" };
const std::vector<std::string> Genmain::symbols {"symbolCircle", "symbolCross", "symbolDiamond", "symbolSquare", "symbolStar", "symbolTriangle", "symbolWye"};

#include <iostream>

std::string
genmain(std::string s_config)
{
  nlohmann::json config = nlohmann::json::parse(s_config);
  std::vector<std::string> cn_arr;
  GenMod* comp;

  /* get the comp */
  boost::algorithm::split(cn_arr, config["controller"].get<std::string>(), boost::is_any_of("-"));
  if (GenMod::all_mods.find(cn_arr[0]) == GenMod::all_mods.end())
    goto genmain_return;

  /* */
  std::cout << "abcd\n";
  for (auto &it: GenMod::all_mods) {
    std::cout << cn_arr[0] << "--" << it.first << "\n";
  }
  comp = GenMod::all_mods[cn_arr[0]];
  if (config.contains("seed")) {
    comp->seed(config["seed"].get<std::uint32_t>());
  }
  return comp->gen(cn_arr[1], config);

 genmain_return:
  return "{text: 'Wrong setup, test was not generated!'}";
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
  if (GenMod::all_mods.find(cn_arr[0]) == GenMod::all_mods.end())
    goto checkmain_return;

  /* */
  comp = GenMod::all_mods[cn_arr[0]];
  return comp->check(cn_arr[1], config, question, ans);

 checkmain_return:
  return "{text: 'Wrong setup, test was not generated!'}";
}


std::string
GenMod::gen(const std::string cname, nlohmann::json& config)
{
  /* */
  nlohmann::json ret;

  if (controllers.find(cname) != controllers.end())
    controllers[cname]->gen(ret, rand, config);

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
