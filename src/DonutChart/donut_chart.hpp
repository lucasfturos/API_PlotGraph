#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

class DonutChart {
  private:
    struct DataPoint {
        std::string label;
        float value;
        sf::Color color;
    };

    const std::string filename_font_arial = "../font/arial.ttf";
    const std::string filename_font_times = "../../font/times.ttf";
    void displayDonutChart(const std::vector<DataPoint> &data);

  public:
    void run();
};
