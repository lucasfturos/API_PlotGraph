#include "BarChart/bar_chart.hpp"
#include "DonutChart/donut_chart.hpp"
#include "LineChart/line_chart.hpp"
#include "PieChart/pie_chart.hpp"
#include <memory>
#include <unordered_map>

int main(int argc, char *argv[]) {
    try {
        if (argc < 2) {
            throw std::invalid_argument(
                "Informe as configurações para o gráfico");
        }

        std::unordered_map<std::string, int> optionsGraph{
            {"Linha", 1}, {"Barra", 2},     {"Rosca", 3},
            {"Pizza", 4}, {"Dispersão", 5}, {"Área", 6}};

        auto input = argv[1];
        auto bar = std::make_shared<BarCharts>();
        auto line = std::make_shared<LineChart>();
        auto donut = std::make_shared<DonutChart>();
        auto pie = std::make_shared<PieChart>();
        auto it = optionsGraph.find(input);

        if (it == optionsGraph.end()) {
            throw std::invalid_argument("Opção de gráfico inválida");
        }

        auto opc = it->second;
        switch (opc) {
        case 1:
            line->run();
            break;
        case 2:
            bar->run();
            break;
        case 3:
            donut->run();
            break;
        case 4:
            pie->run();
            break;
        case 5:
            std::cout << "Dispersão logo será implementado!!" << '\n';
            break;
        case 6:
            std::cout << "Área logo será implementado!!" << '\n';
            break;
        default:
            break;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
}
