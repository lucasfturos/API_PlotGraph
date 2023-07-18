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

    sf::VertexArray horizontal_lines(sf::Lines);
    for (int i = 0; i <= 10; ++i) {
        int y = margin + i * (chart_height / 10);
        horizontal_lines.append(
            sf::Vertex(sf::Vector2f(margin, y), sf::Color(200, 200, 200)));
        horizontal_lines.append(sf::Vertex(
            sf::Vector2f(margin + chart_width, y), sf::Color(200, 200, 200)));
    }

    sf::Text yLabel(sf::String::fromUtf8(legendaY.begin(), legendaY.end()),
                    font, 16);
    yLabel.setFillColor(sf::Color::Black);
    yLabel.setRotation(-90);
    yLabel.setPosition(margin - 30, margin + chart_height - 10);

    sf::Text yMaxLabel(std::to_string(max_value), font, 16);
    yMaxLabel.setFillColor(sf::Color::Black);
    yMaxLabel.setPosition(margin - yMaxLabel.getLocalBounds().width - 10,
                          margin - yMaxLabel.getLocalBounds().height / 2);

    sf::Text yMinLabel(std::to_string(0), font, 16);
    yMinLabel.setFillColor(sf::Color::Black);
    yMinLabel.setPosition(margin - yMinLabel.getLocalBounds().width - 10,
                          margin + chart_height -
                              yMinLabel.getLocalBounds().height / 2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        window.draw(xAxis);
        window.draw(yAxis);
        window.draw(horizontal_lines);
        window.draw(yLabel);
        window.draw(yMaxLabel);
        window.draw(yMinLabel);

        for (const auto &barShape : bar_shapes) {
            window.draw(barShape);
        }

        for (const auto &barLabel : bar_labels) {
            window.draw(barLabel);
        }

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
