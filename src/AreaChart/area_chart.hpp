#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <vector>

class AreaChart {
  private:
    struct DataPoint {
        std::vector<int> values;
        sf::Color color;
    };

    const std::string filename_font_arial = "../font/arial.ttf";
    const std::string filename_font_times = "../font/times.ttf";
    void displayArea(const std::vector<DataPoint> &areas);

  public:
    void run();
};
