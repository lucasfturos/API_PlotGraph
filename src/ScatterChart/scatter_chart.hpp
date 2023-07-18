#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

class ScatterChart {
  private:
    struct DataPoint {
        std::vector<float> values;
        sf::Color color;
    };

    const std::string filename_font_arial = "../font/arial.ttf";
    const std::string filename_font_times = "../font/times.ttf";

    std::vector<DataPoint> generateData(int num_points, int num_values);
    void displayScatter(const std::vector<DataPoint> &scatters, int pression);

  public:
    void run();
};
