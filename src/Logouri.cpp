#include "Logouri.h"
#include "Stats.h"
#include <SFML/Graphics.hpp>
#include <optional>
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <random>
#include <functional>
#include <cmath>
#include <cstdio>
#include <string>

namespace Gui {

namespace {

const Echipa* gasesteEchipaDupaNume(const std::vector<Echipa>& echipe, const std::string& nume) {
    for (const auto& e : echipe)
        if (e.getNume() == nume)
            return &e;
    return nullptr;
}

void deseneazaLogo(sf::RenderWindow& window, const sf::Texture& tex,
                   float centerX, float topY, float zona) {
    sf::Sprite sprite(tex);
    const auto dim = tex.getSize();
    const float scara = zona / static_cast<float>(std::max(dim.x, dim.y));
    sprite.setScale({scara, scara});
    const float w = static_cast<float>(dim.x) * scara;
    sprite.setPosition({centerX - w / 2.0f, topY});
    window.draw(sprite);
}

void deseneazaTextCentrat(sf::RenderWindow& window, const sf::Font& font,
                          const std::string& sir, unsigned int marime,
                          float centerX, float topY, sf::Color culoare) {
    sf::Text text(font, sir, marime);
    text.setFillColor(culoare);
    const sf::FloatRect b = text.getLocalBounds();
    text.setPosition({centerX - b.size.x / 2.0f, topY});
    window.draw(text);
}

}  // namespace

// cppcheck-suppress unusedFunction
void afiseazaLogos(const std::vector<Echipa>& echipe, const std::string& titlu) {
    const unsigned int latime = 960;
    const unsigned int inaltime = 800;
    sf::RenderWindow window(sf::VideoMode({latime, inaltime}), titlu);
    window.setFramerateLimit(60);

    sf::Font font;
    const bool areFont = font.openFromFile("assets/fonts/Mulish-Regular.ttf");
    if (!areFont)
        std::cerr << "[GUI] Nu am gasit assets/fonts/Mulish-Regular.ttf; afisez doar logo-urile.\n";

    std::vector<sf::Texture> texturi;
    std::vector<bool> areLogo;
    texturi.reserve(echipe.size());
    areLogo.reserve(echipe.size());
    for (const auto& echipa : echipe) {
        sf::Texture tex;
        const bool ok = tex.loadFromFile(echipa.getLogoPath());
        texturi.push_back(std::move(tex));
        areLogo.push_back(ok);
    }

    const int coloane = 6;
    const float celula = 150.0f;
    const float margine = 20.0f;
    const float zonaLogo = celula - 2 * margine;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color(28, 28, 38));

        for (std::size_t i = 0; i < echipe.size(); ++i) {
            const int col = static_cast<int>(i) % coloane;
            const int rand = static_cast<int>(i) / coloane;
            const float x = margine + static_cast<float>(col) * celula;
            const float y = margine + static_cast<float>(rand) * celula;
            const float centruX = x + zonaLogo / 2.0f;

            if (areLogo[i])
                deseneazaLogo(window, texturi[i], centruX, y, zonaLogo);

            if (areFont)
                deseneazaTextCentrat(window, font, echipe[i].getNume(), 13,
                                     centruX, y + zonaLogo + 6.0f, sf::Color(220, 220, 230));
        }

        window.display();
    }
}

// cppcheck-suppress unusedFunction
void afiseazaCampioana(const std::vector<Echipa>& echipe, const std::string& an) {
    const auto rez = Stats::simulatePlayoff(echipe);

    const Echipa* est = gasesteEchipaDupaNume(echipe, rez.campioanaEast);
    const Echipa* vest = gasesteEchipaDupaNume(echipe, rez.campioanaWest);
    const Echipa* campioana = gasesteEchipaDupaNume(echipe, rez.campioanaFinals);

    // scoruri finale: campioana castiga la 3-14 puncte (reproductibil pe an)
    std::mt19937 rng(static_cast<unsigned int>(std::hash<std::string>{}(an)));
    std::uniform_int_distribution<int> distScor(100, 120);
    std::uniform_int_distribution<int> distMarja(3, 14);
    const int scorCampFinal = distScor(rng);
    const int scorAdvFinal = scorCampFinal - distMarja(rng);

    const bool estCampion = (est != nullptr && est == campioana);
    const bool vestCampion = (vest != nullptr && vest == campioana);
    const int targetEst = estCampion ? scorCampFinal : scorAdvFinal;
    const int targetVest = vestCampion ? scorCampFinal : scorAdvFinal;

    const unsigned int latime = 960;
    const unsigned int inaltime = 720;
    sf::RenderWindow window(sf::VideoMode({latime, inaltime}), "Finala NBA " + an);
    window.setFramerateLimit(60);

    sf::Font font;
    const bool areFont = font.openFromFile("assets/fonts/Mulish-Regular.ttf");

    sf::Texture texEst, texVest;
    const bool okEst = (est != nullptr) && texEst.loadFromFile(est->getLogoPath());
    const bool okVest = (vest != nullptr) && texVest.loadFromFile(vest->getLogoPath());

    const sf::Color auriu(255, 215, 0);
    const sf::Color alb(230, 230, 235);

    const float durata = 8.0f;  // secunde reale pentru tot meciul (fast forward)
    sf::Clock ceas;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float t = ceas.getElapsedTime().asSeconds() / durata;
        if (t > 1.0f) t = 1.0f;
        const bool gata = (t >= 1.0f);

        const int scorEst = static_cast<int>(std::round(static_cast<float>(targetEst) * t));
        const int scorVest = static_cast<int>(std::round(static_cast<float>(targetVest) * t));

        const float minRamase = 48.0f * (1.0f - t);
        const int mm = static_cast<int>(minRamase);
        const int ss = static_cast<int>((minRamase - static_cast<float>(mm)) * 60.0f);

        window.clear(sf::Color(20, 22, 32));

        if (areFont)
            deseneazaTextCentrat(window, font, "Finala NBA " + an, 30, 480.0f, 26.0f, alb);

        // in timpul meciului aratam ambele logo-uri sus
        if (okEst)  deseneazaLogo(window, texEst, 290.0f, 90.0f, 150.0f);
        if (okVest) deseneazaLogo(window, texVest, 670.0f, 90.0f, 150.0f);

        if (areFont) {
            if (est)  deseneazaTextCentrat(window, font, est->getNume(), 15, 290.0f, 248.0f,
                                           (estCampion && gata) ? auriu : alb);
            if (vest) deseneazaTextCentrat(window, font, vest->getNume(), 15, 670.0f, 248.0f,
                                           (vestCampion && gata) ? auriu : alb);

            deseneazaTextCentrat(window, font, std::to_string(scorEst), 46, 290.0f, 285.0f,
                                 (estCampion && gata) ? auriu : alb);
            deseneazaTextCentrat(window, font, std::to_string(scorVest), 46, 670.0f, 285.0f,
                                 (vestCampion && gata) ? auriu : alb);

            if (gata) {
                deseneazaTextCentrat(window, font, "FINAL", 34, 480.0f, 295.0f, auriu);
            } else {
                char buf[8];
                std::snprintf(buf, sizeof(buf), "%02d:%02d", mm, ss);
                deseneazaTextCentrat(window, font, buf, 34, 480.0f, 295.0f, alb);
            }
        }

        // la final: logo-ul MARE al campioanei in centru + numele
        if (gata == true) {
            if (estCampion && okEst)
                deseneazaLogo(window, texEst, 480.0f, 345.0f, 170.0f);
            else if (vestCampion && okVest)
                deseneazaLogo(window, texVest, 480.0f, 345.0f, 170.0f);

            if (areFont && campioana)
                deseneazaTextCentrat(window, font, "CAMPIOANA NBA: " + campioana->getNume(),
                                     26, 480.0f, 530.0f, auriu);
        }

        window.display();
    }
}
}
