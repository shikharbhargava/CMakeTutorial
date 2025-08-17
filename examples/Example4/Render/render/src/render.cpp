#include "render.h"
#include <opencv2/opencv.hpp>
#include <iostream>

namespace render
{
  void display_images(const std::vector<std::string> &image_paths)
  {
    for (const auto &path : image_paths)
    {
      cv::Mat img = cv::imread(path);
      if (img.empty())
      {
        std::cerr << "Failed to load: " << path << std::endl;
        continue;
      }

#ifdef BLACK_AND_WHITE
      cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
#endif

      cv::imshow("Render", img);
      cv::waitKey(0);
    }
  }
}