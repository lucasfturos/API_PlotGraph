#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class BarCharts {
  private:
    struct BarData {
        std::string label;
        int value;
        sf::Color color;
    };

    const std::string filename_font_arial = "../font/arial.ttf";
    const std::string filename_font_times = "../../font/times.ttf";
    void displayBarChart(const std::vector<BarData> &bars);

  public:
    void run();
};
