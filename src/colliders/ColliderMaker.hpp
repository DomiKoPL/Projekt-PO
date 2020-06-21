#pragma once
#include "ConvexColliders.hpp"
#include <string>
#include <vector>

class ColliderMaker {
private:
    template <typename T>
    static std::vector<std::vector<sf::Vector2<T>>> triangulate_by_ear_clipping(std::vector<sf::Vector2<T>> polygon);

    template <typename T>
    static std::vector<std::vector<sf::Vector2<T>>> hertel_mehlhorn(std::vector<sf::Vector2<T>> polygon);

    template <typename T>
    static bool is_convex(sf::Vector2<T> p1, sf::Vector2<T> p2, sf::Vector2<T> p3);

    template <typename T>
    static sf::Vector2<T> normalize(sf::Vector2<T> p);

    template <typename T>
    static bool is_reflex(sf::Vector2<T> p1, sf::Vector2<T> p2, sf::Vector2<T> p3);

    template <typename T>
    static bool is_inside(sf::Vector2<T> p1, sf::Vector2<T> p2, sf::Vector2<T> p3, sf::Vector2<T> p);
    
    static void decrease(std::vector<std::vector<char>>& img);
    static void make_border(std::vector<std::vector<char>>& img);
    static void draw(std::vector<std::vector<char>>& img);
    static std::vector<std::vector<sf::Vector2f>> get_parts(std::vector<std::vector<char>>& img);
public:
    static ConvexColliders* make_collider(sf::Image image, unsigned int decrease = 3);
};

// Hertel-Mehlhorn algorithm
// http://www.dma.fi.upm.es/recursos/aplicaciones/geometria_computacional_y_grafos/web/piezas_convexas/algoritmo_i.html