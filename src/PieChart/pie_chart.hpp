#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <numeric>

class PieChart {
  private:
    struct DataPoint {
        std::string label;
        float value;
        sf::Color color;
    };

    const std::string filename_font_arial = "../font/arial.ttf";
    const std::string filename_font_times = "../../font/times.ttf";
    void displayPieChart(const std::vector<DataPoint> &data);

  public:
    void run();
};
