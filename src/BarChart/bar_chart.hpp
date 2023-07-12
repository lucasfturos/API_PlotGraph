#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class BarCharts {
  private:
    const std::string filename = "../font/arial.ttf";
    struct BarData {
        std::string label;
        int value;
        sf::Color color;
    };

    void displayBarChart(const std::vector<BarData> &bars);

  public:
    void run();
};
