#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class LineGraph {
  private:
    const std::string filename = "../font/arial.ttf";
    void displayLine(const std::vector<int> &fitnessValues);

  public:
    void run();
};
