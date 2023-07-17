#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class LineChart {
  private:
    struct DataPoint {
        std::vector<int> values;
        sf::Color color;
    };

    const std::string filename_font_arial = "../font/arial.ttf";
    const std::string filename_font_times = "../font/times.ttf";
    void displayLine(const std::vector<DataPoint> &lines);

  public:
    void run();
};
