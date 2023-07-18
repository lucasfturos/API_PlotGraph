#include "line_chart.hpp"

void LineChart::displayLine(const std::vector<DataPoint> &lines) {
    const std::string title = "Gráfico de Linha";
    sf::RenderWindow window(sf::VideoMode(800, 600),
                            sf::String::fromUtf8(title.begin(), title.end()));
    window.setFramerateLimit(60);

    const int margin = 50;
    const int chart_width = 700;
    const int chart_height = 480;
    int max_value = 0;

    for (const auto &line : lines) {
        int line_max_value =
            *std::max_element(line.values.begin(), line.values.end());
        if (line_max_value > max_value) {
            max_value = line_max_value;
        }
    }
    const int num_vertical_lines = (max_value / 5) / lines.size();
    const int num_horizontal_lines =
        (max_value / 5) /
        lines.size(); // Alterar o 5 para uma variável de precisão
    std::string legendaX = "Eixo X";
    std::string legendaY = "Eixo Y";

    // Configurações do eixo X
    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(margin, margin + chart_height);
    xAxis[0].color = sf::Color::Black;
    xAxis[1].position =
        sf::Vector2f(margin + chart_width, margin + chart_height);
    xAxis[1].color = sf::Color::Black;

    // Configurações do eixo y
    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(margin, margin);
    yAxis[0].color = sf::Color::Black;
    yAxis[1].position = sf::Vector2f(margin, margin + chart_height);
    yAxis[1].color = sf::Color::Black;

    // Adiciona a fonte para as legendas e números nos eixos
    sf::Font font;
    if (!font.loadFromFile(filename_font_arial)) {
        throw std::runtime_error("Falha ao carregar a fonte.");
    }

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

    std::vector<sf::Text> xValueLabel;
    float xLabelSpacing = static_cast<float>(chart_width) / num_vertical_lines;
    float xValueSpacing = static_cast<float>(max_value) / num_vertical_lines;
    for (int i = 1; i <= num_vertical_lines; i++) {
        int xValue = i * xValueSpacing;
        sf::Text value_label(sf::Text(std::to_string(xValue), font, 16));
        value_label.setFillColor(sf::Color::Black);
        value_label.setPosition(margin + i * xLabelSpacing -
                                    value_label.getLocalBounds().width / 2,
                                margin + chart_height + 10);
        xValueLabel.push_back(value_label);
    }

    // Legenda dos Eixos X e Y
    sf::Text xLabel(sf::String::fromUtf8(legendaX.begin(), legendaX.end()),
                    font, 16);
    xLabel.setFillColor(sf::Color::Black);
    xLabel.setPosition(40 + static_cast<float>(chart_width) / 2,
                       margin + chart_height + 30);

    sf::Text yLabel(sf::String::fromUtf8(legendaY.begin(), legendaY.end()),
                    font, 16);
    yLabel.setFillColor(sf::Color::Black);
    yLabel.setRotation(-90);
    yLabel.setPosition(margin - 50,
                       20 + margin + static_cast<float>(chart_height) / 2);

    sf::VertexArray horizontal_lines(sf::Lines);
    for (int i = 0; i <= num_horizontal_lines; ++i) {
        int y = margin + i * yLabelSpacing;
        horizontal_lines.append(
            sf::Vertex(sf::Vector2f(margin, y), sf::Color(200, 200, 200)));
        horizontal_lines.append(sf::Vertex(
            sf::Vector2f(margin + chart_width, y), sf::Color(200, 200, 200)));
    }

    // Desenhar linhas
    std::vector<sf::VertexArray> line_segments;
    for (const auto &line : lines) {
        sf::VertexArray line_segment(sf::LineStrip, line.values.size());
        for (std::size_t i = 0; i < line.values.size(); ++i) {
            sf::Vertex vx;
            line_segment[i].position =
                sf::Vector2f(margin + i * (static_cast<float>(chart_width) /
                                           (line.values.size() - 1)),
                             margin + chart_height -
                                 (static_cast<float>(line.values[i]) *
                                  chart_height / max_value));
            line_segment[i].color = line.color;
        }
        line_segments.push_back(line_segment);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        for (const auto &value_label : yValueLabel) {
            window.draw(value_label);
        }
        for (const auto &value_label : xValueLabel) {
            window.draw(value_label);
        }
        window.draw(horizontal_lines);
        for (const auto &line_segment : line_segments) {
            window.draw(line_segment);
        }
        window.draw(xLabel);
        window.draw(yLabel);
        window.draw(xAxis);
        window.draw(yAxis);

        window.display();
    }
}

void LineChart::run() {
    std::vector<DataPoint> lines = {
        {{10, 30, 40, 20, 50, 40, 30, 60, 50}, sf::Color::Red},
        {{50, 30, 40, 60, 20, 50, 60, 80, 70}, sf::Color::Blue},
        {{20, 20, 10, 50, 60, 70, 100, 60, 70}, sf::Color::Black}};

    displayLine(lines);
}
