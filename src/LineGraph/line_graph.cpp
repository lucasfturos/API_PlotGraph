#include "line_graph.hpp"

void LineGraph::displayLine(const std::vector<int> &fitnessValues) {
    const std::string title = "Gráfico de Linha";
    sf::RenderWindow window(sf::VideoMode(800, 600),
                            sf::String::fromUtf8(title.begin(), title.end()));
    window.setFramerateLimit(60);

    const int margin = 50;
    const int graphWidth = 700;
    const int graphHeight = 500;
    int maxValue =
        *std::max_element(fitnessValues.begin(), fitnessValues.end());
    std::string legendaX = "Eixo X";
    std::string legendaY = "Eixo Y";

    // Configurações do eixo x
    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(margin, margin + graphHeight);
    xAxis[0].color = sf::Color::Black;
    xAxis[1].position = sf::Vector2f(margin + graphWidth, margin + graphHeight);
    xAxis[1].color = sf::Color::Black;

    // Configurações do eixo y
    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(margin, margin);
    yAxis[0].color = sf::Color::Black;
    yAxis[1].position = sf::Vector2f(margin, margin + graphHeight);
    yAxis[1].color = sf::Color::Black;

    // Desenho do gráfico
    sf::VertexArray graph(sf::LineStrip, fitnessValues.size());
    for (std::size_t i = 0; i < fitnessValues.size(); ++i) {
        graph[i].position = sf::Vector2f(
            margin + i * (graphWidth / (fitnessValues.size() - 1)),
            margin + graphHeight - (fitnessValues[i] * graphHeight / maxValue));
        graph[i].color = sf::Color::Black;
    }

    // Adicionar legendas e números nos eixos
    sf::Font font;
    if (!font.loadFromFile(filename_font_arial)) {
        std::cerr << "Falha ao carregar a fonte.\n";
        return;
    }

    sf::Text xLabel(sf::String::fromUtf8(legendaX.begin(), legendaX.end()),
                    font, 16);
    xLabel.setFillColor(sf::Color::Black);
    xLabel.setPosition(margin + graphWidth - xLabel.getLocalBounds().width,
                       margin + graphHeight + 10);

    // Desenhar rótulo do eixo Y
    sf::Text yLabel(sf::String::fromUtf8(legendaY.begin(), legendaY.end()),
                    font, 16);
    yLabel.setFillColor(sf::Color::Black);
    yLabel.setRotation(-90); // Rotaciona o texto em -90 graus
    yLabel.setPosition(margin - 30, margin + graphHeight);
    sf::Text yMaxLabel(std::to_string(*std::max_element(fitnessValues.begin(),
                                                        fitnessValues.end())),
                       font, 16);
    yMaxLabel.setFillColor(sf::Color::Black);
    yMaxLabel.setPosition(margin - yMaxLabel.getLocalBounds().width - 10,
                          margin);

    sf::VertexArray horizontalLines(sf::Lines);
    for (int i = 0; i <= fitnessValues.size() - 1; ++i) {
        int y = margin + i * (graphHeight / fitnessValues.size() - 1);
        horizontalLines.append(
            sf::Vertex(sf::Vector2f(margin, y), sf::Color(200, 200, 200)));
        horizontalLines.append(sf::Vertex(sf::Vector2f(margin + graphWidth, y),
                                          sf::Color(200, 200, 200)));
    }

    // Desenhar barras laterais
    const int barWidth = 20;
    const int barSpacing = 10;
    const int numBars = 5;
    const int barHeight = graphHeight / numBars;
    const int barMaxValue =
        *std::max_element(fitnessValues.begin(), fitnessValues.end());

    for (int i = 0; i <= numBars; ++i) {
        sf::RectangleShape bar(sf::Vector2f(barWidth, barHeight));
        bar.setFillColor(sf::Color::Black);
        bar.setPosition(margin + graphWidth + barSpacing,
                        margin + i * barHeight);
        window.draw(bar);

        sf::Text barLabel(
            std::to_string((barMaxValue / numBars) * (numBars - i)), font, 12);
        barLabel.setFillColor(sf::Color::Black);
        barLabel.setPosition(margin + graphWidth + barSpacing + barWidth + 5,
                             margin + i * barHeight -
                                 barLabel.getLocalBounds().height / 2);
        window.draw(barLabel);
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
        window.draw(horizontalLines);
        window.draw(graph);
        window.draw(xLabel);
        window.draw(yLabel);
        window.draw(yMaxLabel);
        window.display();
    }
}

void LineGraph::run() {
    std::vector<int> fitnessValues = {0, 20, 20, 10, 50, 60, 70, 100, 60, 70};
    displayLine(fitnessValues);
}
