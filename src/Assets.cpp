#include <filesystem>
#include <string>
#include "Assets.h"

namespace fs = std::filesystem;

 
std::string Assets::get_path(std::string relative){

  std::string root_path="/home/sdemingo/src/c++/lander";
  
  return root_path + "/assets/"+relative;
}
