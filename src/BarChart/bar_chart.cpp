#include "bar_chart.hpp"

void BarCharts::displayBarChart(const std::vector<BarData> &bars) {
    const std::string title = "Gráfico de Barra";
    sf::RenderWindow window(sf::VideoMode(800, 600),
                            sf::String::fromUtf8(title.begin(), title.end()));
    window.setFramerateLimit(60);

    const int margin = 50;
    const int chart_width = 700;
    const int chart_height = 500;
    const int bar_width = chart_width / bars.size();
    const int max_value =
        std::max_element(bars.begin(), bars.end(),
                         [](const BarData &a, const BarData &b) {
                             return a.value < b.value;
                         })
            ->value;

    const std::string legendaY = "Eixo Y";

    sf::Font font;
    if (!font.loadFromFile(filename_font_arial)) {
        throw std::runtime_error("Falha ao carregar a fonte.");
    }

    std::vector<sf::RectangleShape> bar_shapes;
    for (std::size_t i = 0; i < bars.size(); ++i) {
        const BarData &bar = bars[i];
        sf::RectangleShape bar_shape(
            sf::Vector2f(bar_width, static_cast<float>(-chart_height) *
                                        bar.value / max_value));
        bar_shape.setFillColor(bar.color);
        bar_shape.setPosition(margin + i * bar_width, margin + chart_height);
        bar_shapes.push_back(bar_shape);
    }

    std::vector<sf::Text> bar_labels;
    for (std::size_t i = 0; i < bars.size(); ++i) {
        const BarData &bar = bars[i];
        sf::Text label(bar.label, font, 12);
        label.setFillColor(sf::Color::Black);
        label.setPosition(margin + i * bar_width +
                              static_cast<float>(bar_width) / 2 -
                              label.getLocalBounds().width / 2,
                          margin + chart_height + 10);
        bar_labels.push_back(label);
    }

    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(margin, margin + chart_height);
    xAxis[0].color = sf::Color::Black;
    xAxis[1].position =
        sf::Vector2f(margin + chart_width, margin + chart_height);
    xAxis[1].color = sf::Color::Black;

    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(margin, margin);
    yAxis[0].color = sf::Color::Black;
    yAxis[1].position = sf::Vector2f(margin, margin + chart_height);
    yAxis[1].color = sf::Color::Black;

    const int num_horizontal_lines = (max_value / 1) / bars.size();
    // Legenga da grade Y e X
    std::vector<sf::Text> yValueLabel;
    float yLabelSpacing =
        static_cast<float>(chart_height) / (num_horizontal_lines);
    float yValueSpacing = static_cast<float>(max_value) / num_horizontal_lines;
    for (int i = 0; i <= num_horizontal_lines; i++) {
        int yValue = i * yValueSpacing;
        sf::Text value_label(sf::Text(std::to_string(yValue), font, 16));
        value_label.setFillColor(sf::Color::Black);
        value_label.setPosition(margin - value_label.getLocalBounds().width -
                                    10,
                                margin + chart_height - i * yLabelSpacing -
                                    value_label.getLocalBounds().height / 2);
        yValueLabel.push_back(value_label);
    }
    sf::VertexArray horizontal_lines(sf::Lines);
    for (int i = 0; i <= num_horizontal_lines; ++i) {
        int y = margin + i * (chart_height / num_horizontal_lines);
        horizontal_lines.append(
            sf::Vertex(sf::Vector2f(margin, y), sf::Color(200, 200, 200)));
        horizontal_lines.append(sf::Vertex(
            sf::Vector2f(margin + chart_width, y), sf::Color(200, 200, 200)));
    }

    sf::Text yLabel(sf::String::fromUtf8(legendaY.begin(), legendaY.end()),
                    font, 16);
    yLabel.setFillColor(sf::Color::Black);
    yLabel.setRotation(-90);
    yLabel.setPosition(margin - 50,
                       20 + margin + static_cast<float>(chart_height) / 2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        window.draw(horizontal_lines);
        for (const auto &value_label : yValueLabel) {
            window.draw(value_label);
        }
        window.draw(yLabel);
        for (const auto &barShape : bar_shapes) {
            window.draw(barShape);
        }
        for (const auto &barLabel : bar_labels) {
            window.draw(barLabel);
        }
        window.draw(xAxis);
        window.draw(yAxis);

        window.display();
    }
}

void BarCharts::run() {
    std::vector<BarData> bars = {
        {"Barra 1", 5, sf::Color::Red},      {"Barra 2", 20, sf::Color::Green},
        {"Barra 3", 30, sf::Color::Blue},    {"Barra 4", 40, sf::Color::Yellow},
        {"Barra 5", 50, sf::Color::Magenta}, {"Barra 6", 60, sf::Color::Red},
        {"Barra 7", 70, sf::Color::Green},   {"Barra 8", 80, sf::Color::Yellow},
    };

    displayBarChart(bars);
}
