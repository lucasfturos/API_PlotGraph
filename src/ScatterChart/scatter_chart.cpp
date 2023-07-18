#include "scatter_chart.hpp"

void ScatterChart::displayScatter(const std::vector<DataPoint> &scatters,
                                  int pression) {
    const std::string title = "Gráfico de Dispersão";
    sf::RenderWindow window(sf::VideoMode(800, 600),
                            sf::String::fromUtf8(title.begin(), title.end()));
    window.setFramerateLimit(60);

    const int margin = 60;
    const int chart_width = 700;
    const int chart_height = 480;
    int max_value = 0;

    for (const auto &scatter : scatters) {
        int scatter_max_value =
            *std::max_element(scatter.values.begin(), scatter.values.end());
        if (scatter_max_value > max_value) {
            max_value = scatter_max_value;
        }
    }

    const int num_vertical_lines = (max_value / pression) / scatters.size();
    const int num_horizontal_lines = (max_value / pression) / scatters.size();

    // Adiciona a fonte para as legendas e números nos eixos
    sf::Font font;
    if (!font.loadFromFile(filename_font_arial)) {
        throw std::runtime_error("Falha ao carregar a fonte.");
    }

    // Configurações do eixo X
    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(margin, margin + chart_height);
    xAxis[0].color = sf::Color::Black;
    xAxis[1].position =
        sf::Vector2f(margin + chart_width, margin + chart_height);
    xAxis[1].color = sf::Color::Black;

    // Configurações do eixo Y esquerdo
    sf::VertexArray yAxis_left(sf::Lines, 2);
    yAxis_left[0].position = sf::Vector2f(margin, margin);
    yAxis_left[0].color = sf::Color::Black;
    yAxis_left[1].position = sf::Vector2f(margin, margin + chart_height);
    yAxis_left[1].color = sf::Color::Black;
    // Configurações do eixo Y direito
    sf::VertexArray yAxis_right(sf::Lines, 2);
    yAxis_right[0].position = sf::Vector2f(margin + chart_width, margin);
    yAxis_right[0].color = sf::Color::Black;
    yAxis_right[1].position =
        sf::Vector2f(margin + chart_width, margin + chart_height);
    yAxis_right[1].color = sf::Color::Black;

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
    std::string legendaX = "Eixo X";
    std::string legendaY = "Eixo Y";
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

    // Grade vertical e horizontal
    sf::VertexArray horizontal_lines(sf::Lines);
    for (int i = 0; i <= num_horizontal_lines; ++i) {
        int y = margin + i * yLabelSpacing;
        horizontal_lines.append(
            sf::Vertex(sf::Vector2f(margin, y), sf::Color(200, 200, 200)));
        horizontal_lines.append(sf::Vertex(
            sf::Vector2f(margin + chart_width, y), sf::Color(200, 200, 200)));
    }

    sf::VertexArray vertical_lines(sf::Lines);
    for (int i = 0; i <= num_vertical_lines; ++i) {
        int x =
            margin + i * (static_cast<float>(chart_width) / num_vertical_lines);
        vertical_lines.append(
            sf::Vertex(sf::Vector2f(x, margin), sf::Color(200, 200, 200)));
        vertical_lines.append(sf::Vertex(sf::Vector2f(x, margin + chart_height),
                                         sf::Color(200, 200, 200)));
    }

    // Desenha os pontos do gráfico
    std::vector<sf::CircleShape> circles;
    for (const auto &scatter : scatters) {
        for (std::size_t i = 0; i < scatter.values.size(); ++i) {
            float x = margin + i * (static_cast<float>(chart_width) /
                                    (scatter.values.size() - 1));
            float y = margin + chart_height -
                      scatter.values[i] *
                          (static_cast<float>(chart_height) / max_value);

            sf::CircleShape circle(3.f);
            circle.setFillColor(scatter.color);
            circle.setPosition(x - circle.getRadius(), y - circle.getRadius());

            circles.push_back(circle);
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        window.draw(xLabel);
        window.draw(yLabel);
        window.draw(vertical_lines);
        window.draw(horizontal_lines);

        for (const auto &circle : circles) {
            window.draw(circle);
        }

        for (const auto &value_label : yValueLabel) {
            window.draw(value_label);
        }
        for (const auto &value_label : xValueLabel) {
            window.draw(value_label);
        }
        window.draw(xAxis);
        window.draw(yAxis_left);
        window.draw(yAxis_right);

        window.display();
    }
}

void ScatterChart::run() {
    std::vector<DataPoint> scatter;
    auto seed =
        std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_real_distribution<float> dis(0.f, 101.f);

    std::vector<float> values1;
    for (int i = 0; i < 100; ++i) {
        values1.push_back(dis(gen));
    }
    scatter.push_back({values1, sf::Color::Red});

    std::vector<float> values2;
    for (int i = 0; i < 100; ++i) {
        values2.push_back(dis(gen));
    }
    scatter.push_back({values2, sf::Color::Cyan});

    std::vector<float> values3;
    for (int i = 0; i < 100; ++i) {
        values3.push_back(dis(gen));
    }
    scatter.push_back({values3, sf::Color::Magenta});

    std::vector<float> values4;
    for (int i = 0; i < 100; ++i) {
        values4.push_back(dis(gen));
    }
    scatter.push_back({values4, sf::Color::Blue});

    displayScatter(scatter, 100 / 20);
}

