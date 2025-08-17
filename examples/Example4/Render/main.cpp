#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "render.h"
#include "ArgParser.h"

int main(int argc, char **argv)
{
  std::string inputPath;
  try
  {
    parser.addOption("input", 'i', Arguments::ArgTypes::FILE, "Input images json file.", true, true);
    parser.parse(argc, argv);
    inputPath = parser.get<std::string>("input");
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << std::endl;
    parser.printHelp();
    return 1;
  }

  std::ifstream file(inputPath);
  if (!file.is_open())
  {
    std::cerr << "Could not open file: " << argv[1] << std::endl;
    return 1;
  }

  nlohmann::json j;
  file >> j;

  std::vector<std::string> image_paths = j["images"].get<std::vector<std::string>>();

  render::display_images(image_paths);

  return 0;
}