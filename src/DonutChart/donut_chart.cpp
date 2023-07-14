#include "donut_chart.hpp"
#include <string>

void DonutChart::displayDonutChart(const std::vector<DataPoint> &data) {
    const std::string title = "Gráfico de Rosquinha";
    sf::RenderWindow window(sf::VideoMode(800, 600),
                            sf::String::fromUtf8(title.begin(), title.end()));
    window.setFramerateLimit(60);

    const int centerX = 400;
    const int centerY = 300;
    const int radius = 200;
    const int donut_radius = 100;
    const float total_value = std::accumulate(
        data.begin(), data.end(), 0.f,
        [](float sum, const DataPoint &dp) { return sum + dp.value; });

    float start_angle = 0.f;
    float end_angle = 0.f;

    const std::string info_legenda = "Legenda:";

    sf::Font font;
    if (!font.loadFromFile(filename_font_arial)) {
        std::cerr << "Falha ao carregar a fonte.\n";
        return;
    }

    // Legenda lateral
    sf::Text legend_title(
        sf::String::fromUtf8(info_legenda.begin(), info_legenda.end()), font,
        16);
    legend_title.setFillColor(sf::Color::Black);
    legend_title.setPosition(20, 20);

    const int legend_size = 20;
    const int legend_spacing = 10;
    const int legend_text_Offset = legend_size + 5;

    std::vector<sf::RectangleShape> legend_rectangles;
    std::vector<sf::Text> legend_labels;

    for (std::size_t i = 0; i < data.size(); ++i) {
        const auto &dp = data[i];

        sf::RectangleShape rectangle(sf::Vector2f(legend_size, legend_size));
        rectangle.setFillColor(dp.color);
        rectangle.setPosition(20, 50 + i * (legend_size + legend_spacing));

        const int pression = 1 + 1; // Substituir 1 por variável de precisão
        const std::string legenda_value =
            ": " +
            std::to_string(dp.value).substr(
                0, std::to_string(dp.value).find(".") + pression) +
            "%";

        sf::Text label(dp.label + legenda_value, font, 16);
        label.setFillColor(sf::Color::Black);
        label.setPosition(20 + legend_text_Offset,
                          50 + i * (legend_size + legend_spacing) +
                              (legend_size - label.getLocalBounds().height) /
                                  2.f);

        legend_rectangles.push_back(rectangle);
        legend_labels.push_back(label);
    }

    // Desenha circulo externo
    std::vector<sf::VertexArray> arcs;
    for (const auto &dp : data) {
        end_angle = start_angle + (dp.value / total_value) * 360.f;

        sf::VertexArray arc(sf::TriangleFan);
        arc.append(sf::Vertex(sf::Vector2f(centerX, centerY), dp.color));

        for (float angle = start_angle; angle <= end_angle; angle += 1.f) {
            float radians = angle * M_PI / 180.f;
            float x = centerX + radius * std::cos(radians);
            float y = centerY + radius * std::sin(radians);

            arc.append(sf::Vertex(sf::Vector2f(x, y), dp.color));
        }

        arcs.push_back(arc);

        start_angle = end_angle;
    }

    // Desenha circulo interno
    sf::CircleShape inner_circle(donut_radius);
    inner_circle.setFillColor(sf::Color::White);
    inner_circle.setPosition(centerX - donut_radius, centerY - donut_radius);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        for (const auto arc : arcs) {
            window.draw(arc);
        }

        window.draw(inner_circle);

        window.draw(legend_title);
        for (const auto &rectangle : legend_rectangles) {
            window.draw(rectangle);
        }

        for (const auto &label : legend_labels) {
            window.draw(label);
        }

        window.display();
    }
}

void DonutChart::run() {
    std::vector<DataPoint> data = {
        {"Segmento 1", 30.f, sf::Color::Red},
        {"Segmento 2", 20.f, sf::Color::Green},
        {"Segmento 3", 15.f, sf::Color::Blue},
        {"Segmento 4", 10.f, sf::Color::Yellow},
        {"Segmento 5", 25.f, sf::Color::Magenta},
    };

    displayDonutChart(data);
}
