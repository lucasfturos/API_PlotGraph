#include "line_graph.hpp"

void LineGraph::displayLine(const std::vector<DataPoint> &lines) {
    const std::string title = "Gráfico de Linha";
    sf::RenderWindow window(sf::VideoMode(800, 600),
                            sf::String::fromUtf8(title.begin(), title.end()));
    window.setFramerateLimit(60);

    const int margin = 50;
    const int graph_width = 700;
    const int graph_height = 500;
    int max_value = 0;

    for (const auto &line : lines) {
        int line_max_value =
            *std::max_element(line.values.begin(), line.values.end());
        if (line_max_value > max_value) {
            max_value = line_max_value;
        }
    }

    std::string legendaX = "Eixo X";
    std::string legendaY = "Eixo Y";

    // Configurações do eixo x
    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(margin, margin + graph_height);
    xAxis[0].color = sf::Color::Black;
    xAxis[1].position =
        sf::Vector2f(margin + graph_width, margin + graph_height);
    xAxis[1].color = sf::Color::Black;

    // Configurações do eixo y
    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(margin, margin);
    yAxis[0].color = sf::Color::Black;
    yAxis[1].position = sf::Vector2f(margin, margin + graph_height);
    yAxis[1].color = sf::Color::Black;

    // Adiciona a fonte para as legendas e números nos eixos
    sf::Font font;
    if (!font.loadFromFile(filename_font_arial)) {
        std::cerr << "Falha ao carregar a fonte.\n";
        return;
    }

    sf::Text xLabel(sf::String::fromUtf8(legendaX.begin(), legendaX.end()),
                    font, 16);
    xLabel.setFillColor(sf::Color::Black);
    xLabel.setPosition(margin + graph_width - xLabel.getLocalBounds().width,
                       margin + graph_height + 10);

    // Desenha legenda do eixo Y
    sf::Text yLabel(sf::String::fromUtf8(legendaY.begin(), legendaY.end()),
                    font, 16);
    yLabel.setFillColor(sf::Color::Black);
    yLabel.setRotation(-90);
    yLabel.setPosition(margin - 30, margin + graph_height);
    sf::Text yMaxLabel(std::to_string(max_value), font, 16);
    yMaxLabel.setFillColor(sf::Color::Black);
    yMaxLabel.setPosition(margin - yMaxLabel.getLocalBounds().width - 10,
                          margin);

    sf::VertexArray horizontal_lines(sf::Lines);
    const int num_horizontal_lines = 5;

    for (int i = 0; i <= num_horizontal_lines; ++i) {
        int y = margin + i * (graph_height / num_horizontal_lines);
        horizontal_lines.append(
            sf::Vertex(sf::Vector2f(margin, y), sf::Color(200, 200, 200)));
        horizontal_lines.append(sf::Vertex(
            sf::Vector2f(margin + graph_width, y), sf::Color(200, 200, 200)));
    }

    // Desenhar linhas
    std::vector<sf::VertexArray> line_segments;
    for (const auto &line : lines) {
        sf::VertexArray line_segment(sf::LineStrip, line.values.size());
        for (std::size_t i = 0; i < line.values.size(); ++i) {
            sf::Vertex vx;
            line_segment[i].position =
                sf::Vector2f(margin + i * (static_cast<float>(graph_width) /
                                           (line.values.size() - 1)),
                             margin + graph_height -
                                 (static_cast<float>(line.values[i]) *
                                  graph_height / max_value));
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

        window.draw(xAxis);
        window.draw(yAxis);
        window.draw(horizontal_lines);
        for (const auto &line_segment : line_segments) {
            window.draw(line_segment);
        }
        window.draw(xLabel);
        window.draw(yLabel);
        window.draw(yMaxLabel);
        window.display();
    }
}

void LineGraph::run() {
    std::vector<DataPoint> lines = {
        {{10, 30, 40, 20, 50, 40, 30, 60, 50}, sf::Color::Red},
        {{50, 30, 40, 60, 20, 50, 60, 80, 70}, sf::Color::Blue},
        {{20, 20, 10, 50, 60, 70, 100, 60, 70}, sf::Color::Black}};

    displayLine(lines);
}
