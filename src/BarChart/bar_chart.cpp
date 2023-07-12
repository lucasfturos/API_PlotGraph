#include "bar_chart.hpp"

void BarCharts::displayBarChart(const std::vector<BarData> &bars) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Gráfico de Barras");
    window.setFramerateLimit(60);

    const int margin = 50;
    const int chartWidth = 700;
    const int chartHeight = 500;

    const int barWidth = chartWidth / bars.size();
    const int maxValue =
        std::max_element(bars.begin(), bars.end(),
                         [](const BarData &a, const BarData &b) {
                             return a.value < b.value;
                         })
            ->value;

    sf::Font font;
    if (!font.loadFromFile(filename)) {
        std::cerr << "Falha ao carregar a fonte.\n";
        return;
    }

    std::vector<sf::RectangleShape> barShapes;
    for (std::size_t i = 0; i < bars.size(); ++i) {
        const BarData &bar = bars[i];
        sf::RectangleShape barShape(
            sf::Vector2f(barWidth, -chartHeight * bar.value / maxValue));
        barShape.setFillColor(bar.color);
        barShape.setPosition(margin + i * barWidth, margin + chartHeight);
        barShapes.push_back(barShape);
    }

    std::vector<sf::Text> barLabels;
    for (std::size_t i = 0; i < bars.size(); ++i) {
        const BarData &bar = bars[i];
        sf::Text label(bar.label, font, 12);
        label.setFillColor(sf::Color::Black);
        label.setPosition(margin + i * barWidth + barWidth / 2 -
                              label.getLocalBounds().width / 2,
                          margin + chartHeight + 10);
        barLabels.push_back(label);
    }

    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(margin, margin + chartHeight);
    xAxis[0].color = sf::Color::Black;
    xAxis[1].position = sf::Vector2f(margin + chartWidth, margin + chartHeight);
    xAxis[1].color = sf::Color::Black;

    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(margin, margin);
    yAxis[0].color = sf::Color::Black;
    yAxis[1].position = sf::Vector2f(margin, margin + chartHeight);
    yAxis[1].color = sf::Color::Black;

    sf::VertexArray horizontalLines(sf::Lines);
    for (int i = 0; i <= 10; ++i) {
        int y = margin + i * (chartHeight / 10);
        horizontalLines.append(
            sf::Vertex(sf::Vector2f(margin, y), sf::Color(200, 200, 200)));
        horizontalLines.append(sf::Vertex(sf::Vector2f(margin + chartWidth, y),
                                          sf::Color(200, 200, 200)));
    }

    sf::Text yLabel("Valores", font, 16);
    yLabel.setFillColor(sf::Color::Black);
    yLabel.setRotation(-90);
    yLabel.setPosition(margin - 30, margin + chartHeight - 10);

    sf::Text yMaxLabel(std::to_string(maxValue), font, 16);
    yMaxLabel.setFillColor(sf::Color::Black);
    yMaxLabel.setPosition(margin - yMaxLabel.getLocalBounds().width - 10,
                          margin - yMaxLabel.getLocalBounds().height / 2);

    sf::Text yMinLabel(std::to_string(0), font, 16);
    yMinLabel.setFillColor(sf::Color::Black);
    yMinLabel.setPosition(margin - yMinLabel.getLocalBounds().width - 10,
                          margin + chartHeight -
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
        window.draw(horizontalLines);
        window.draw(yLabel);
        window.draw(yMaxLabel);
        window.draw(yMinLabel);

        for (const auto &barShape : barShapes) {
            window.draw(barShape);
        }

        for (const auto &barLabel : barLabels) {
            window.draw(barLabel);
        }

        window.display();
    }
}

void BarCharts::run() {
    std::vector<BarData> bars = {
        {"Barra 1", 5, sf::Color::Red},
        {"Barra 2", 20, sf::Color::Green},
        {"Barra 3", 30, sf::Color::Blue},
        {"Barra 4", 40, sf::Color::Yellow},
        {"Barra 5", 50, sf::Color::Magenta},
        {"Barra 6", 60, sf::Color::Red},
        {"Barra 7", 70, sf::Color::Green},
        {"Barra 8", 80, sf::Color::Yellow},
        {"Barra 9", 400, sf::Color::Magenta},
    };

    displayBarChart(bars);
}
