#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class ScatterChart {
  private:
    struct DataPoint {
        std::vector<float> values;
        sf::Color color;
    };

    const std::string filename_font_arial = "../font/arial.ttf";
    const std::string filename_font_times = "../font/times.ttf";
    void displayScatter(const std::vector<DataPoint> &scatters);

  public:
    void run();
};
