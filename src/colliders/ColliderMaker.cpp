#include "ColliderMaker.hpp"
#include <iostream>
#include <assert.h>
#include <math.h>

template <typename T>
using Point = sf::Vector2<T>;

template <typename T>
using Poly = std::vector<Point<T>>;

template <typename T>
struct PartitionVertex {
    bool is_active, is_convex, is_ear;
    Point<T> p;
    double angle;
    PartitionVertex<T> *prev, *next;
};

template <typename T>
std::vector<Poly<T>> ColliderMaker::triangulate_by_ear_clipping(Poly<T> polygon) {
    assert(polygon.size() >= 3u);

    if(polygon.size() == 3u) {
        return {polygon};
    }
    
    int vertices_cnt = polygon.size();
    std::vector<PartitionVertex<T>> vertices(vertices_cnt);

    for(int i = 0; i < vertices_cnt; i++) {
        vertices[i].is_active = true;
        vertices[i].p = polygon[i];

        if(i == vertices_cnt - 1) {
            vertices[i].next = &(vertices[0]);
        } else {
            vertices[i].next = &(vertices[i + 1]);
        }

        if(i == 0) {
            vertices[i].prev = &(vertices[vertices_cnt - 1]);
        } else {
            vertices[i].prev = &(vertices[i - 1]);
        }
    }

    auto update_vertex = [&](PartitionVertex<T> *vertex) {
        PartitionVertex<T> *prev = vertex->prev, *next = vertex->next;
        vertex->is_convex = ColliderMaker::is_convex(prev->p, vertex->p, next->p);
        auto v1 = ColliderMaker::normalize(prev->p - vertex->p);
        auto v3 = ColliderMaker::normalize(next->p - vertex->p);
        vertex->angle = v1.x * v3.x + v1.y * v3.y;
        
        if(vertex->is_convex) {
            vertex->is_ear = true;
            for(auto&v : vertices) {
                if(v.p == vertex->p or v.p == prev->p or v.p == next->p) {
                    continue;
                }
                
                if(ColliderMaker::is_inside(prev->p, vertex->p, next->p, v.p)) {
                    vertex->is_ear = false;
                    break;
                }
            }
        } else {
            vertex->is_ear = false;
        }
    };

    for(int i = 0; i < vertices_cnt; i++) {
        update_vertex(&vertices[i]);
    }

    bool ear_found = false;
    PartitionVertex<T> *ear = nullptr;
    
    std::vector<Poly<T>> triangles;

    for(int i = 0; i < vertices_cnt - 3; i++) {
        ear_found = false;
        for(int j = 0; j < vertices_cnt; j++) {
            if(not vertices[j].is_active) continue;
            if(not vertices[j].is_ear) continue;
            if(not ear_found) {
                ear_found = true;
                ear = &(vertices[j]);
            } else if(vertices[j].angle > ear->angle) {
                ear = &(vertices[j]);
            }
        }


        if(not ear_found) {
            // assert(ear_found);
            std::cerr << "ERROR\n";
            std::cerr << triangles.size() << "\n";
            return triangles;
        }

        triangles.push_back({ear->prev->p, ear->p, ear->next->p});

        ear->is_active = false;
        ear->prev->next = ear->next;
        ear->next->prev = ear->prev;

        if(i == vertices_cnt - 4) break;

        update_vertex(ear->prev);
        update_vertex(ear->next);
    }

    for(int i = 0; i < vertices_cnt; i++) {
        if(vertices[i].is_active) {
            triangles.push_back({vertices[i].prev->p, vertices[i].p, vertices[i].next->p});
            break;
        }
    }

    return triangles;
}


template <typename T>
std::vector<Poly<T>> ColliderMaker::hertel_mehlhorn(Poly<T> polygon) {
    // check if poly is already convex
    int vertices_cnt = polygon.size();
    bool convex = true;
    for(int i = 0; i < vertices_cnt; i++) {
        int l = i - 1;
        if(i == 0) l = vertices_cnt - 1;
        int r = i + 1;
        if(i == vertices_cnt - 1) r = 0;
        if(ColliderMaker::is_reflex(polygon[l], polygon[i], polygon[r])) {
            convex = false;
            break;
        }
    }

    if(convex) {
        return {polygon};
    }
    
    auto triangles = ColliderMaker::triangulate_by_ear_clipping(polygon);
    
    auto it1 = triangles.begin(), it2 = triangles.begin();
    Poly<T> *poly1, *poly2;

    for(it1 = triangles.begin(); it1 != triangles.end(); it1++) {
        poly1 = &(*it1);
        
        for(int i = 0; i < int(poly1->size()); i++) {
            auto d1 = poly1->at(i);
            int j = (i + 1) % int(poly1->size());
            auto d2 = poly1->at(j);
            bool is_diagonal = false;
        
            int ii, jj;
            for(it2 = std::next(it1); it2 != triangles.end(); it2++) {
                poly2 = &(*it2);
                for(ii = 0; ii < int(poly2->size()); ii++) {
                    if(d2 != poly2->at(ii)) continue;
                    jj = (ii + 1) % int(poly2->size());
                    if(d1 != poly2->at(jj)) continue;
                    is_diagonal = true;
                    break;
                }
                if(is_diagonal) break;
            }
            
            if(not is_diagonal) continue;

            auto p2 = poly1->at(i);
            int l = i - 1;
            if(i == 0) l = int(poly1->size()) - 1;
            auto p1 = poly1->at(l);
            int r = jj + 1;
            if(jj == int(poly2->size()) - 1) r = 0;
            auto p3 = poly2->at(r);

            if(not ColliderMaker::is_convex(p1, p2, p3)) {
                continue;
            }
            p2 = poly1->at(j);
            r = j + 1;
            if(j == int(poly1->size()) - 1) r = 0;
            p3 = poly1->at(r);
            l = ii - 1;
            if(ii == 0) l = int(poly2->size()) - 1;
            p1 = poly2->at(l);
            if(not ColliderMaker::is_convex(p1, p2, p3)) {
                continue;
            }

            Poly<T> new_poly;
            new_poly.reserve(poly1->size() + poly2->size() - 2);
            for(int k = j; k != i; k = (k + 1) % int(poly1->size())) {
                new_poly.push_back(poly1->at(k));
            }

            for(int k = jj; k != ii; k = (k + 1) % int(poly2->size())) {
                new_poly.push_back(poly2->at(k));
            }

            triangles.erase(it2);
            *it1 = new_poly;
            poly1 = &(*it1);
            i = -1;
            continue;
        }
    }

    return triangles;
}

template <typename T>
bool ColliderMaker::is_convex(sf::Vector2<T> p1, sf::Vector2<T> p2, sf::Vector2<T> p3) {
    auto tmp = (p3.y - p1.y) * (p2.x - p1.x) - (p3.x - p1.x) * (p2.y - p1.y);
    return tmp > 0;
}

template <typename T>
sf::Vector2<T> ColliderMaker::normalize(sf::Vector2<T> p) {
    auto len = T(std::sqrt(p.x * p.x + p.y * p.y));
    if(len != 0) {
        return p / len;
    }
    return p;
}

template <typename T>
bool ColliderMaker::is_reflex(sf::Vector2<T> p1, sf::Vector2<T> p2, sf::Vector2<T> p3) {
    auto tmp = (p3.y - p1.y) * (p2.x - p1.x) - (p3.x - p1.x) * (p2.y - p1.y);
    return tmp < 0;
}

template <typename T>
bool ColliderMaker::is_inside(sf::Vector2<T> p1, sf::Vector2<T> p2, sf::Vector2<T> p3, sf::Vector2<T> p) {
    if(is_convex(p1, p, p2)) return false;
    if(is_convex(p2, p, p3)) return false;
    if(is_convex(p3, p, p1)) return false;
    return true;
}

int DX[4] = {1, -1, 0, 0};
int DY[4] = {0, 0, 1, -1};

void ColliderMaker::decrease(std::vector<std::vector<char>>& img) {
    auto img2 = img;
    for(int y = 0; y < int(img.size()); y++) {
        for(int x = 0; x < int(img[0].size()); x++) {
            if(img[y][x] == 1) {
                img2[y][x] = 1;
                for(int d = 0; d < 4; d++) {
                    int nx = x + DX[d], ny = y + DY[d];
                    if(nx >= 0 and nx < int(img[0].size()) and ny >= 0 and ny < int(img.size())) {
                        if(img[ny][nx] == 0) {
                            img2[y][x] = 0;
                        }
                    } else {
                        img2[y][x] = 0;
                    }
                }
            } else {
                img2[y][x] = 0;
            }
        }
    }
    img = img2;
}

void ColliderMaker::make_border(std::vector<std::vector<char>>& img) {
    auto img2 = img;
    for(int y = 0; y < int(img.size()); y++) {
        for(int x = 0; x < int(img[0].size()); x++) {
            if(img[y][x] == 1) {
                img2[y][x] = 0;
                for(int d = 0; d < 4; d++) {
                    int nx = x + DX[d], ny = y + DY[d];
                    if(nx >= 0 and nx < int(img[0].size()) and ny >= 0 and ny < int(img.size())) {
                        if(img[ny][nx] == 0) {
                            img2[y][x] = 1;
                        }
                    } else {
                        img2[y][x] = 1;
                    }
                }
            } else {
                img2[y][x] = 0;
            }
        }
    }
    img = img2;
}

void ColliderMaker::draw(std::vector<std::vector<char>>& img) {
    for(int y = 0; y < int(img.size()); y++) {
        for(int x = 0; x < int(img[0].size()); x++) {
            if(img[y][x] == 0) {
                std::cerr << " ";
            } else {
                std::cerr << "x";
            }
        }
        std::cerr << "\n";
    }
    // std::system("sleep 1");
}

std::vector<std::vector<sf::Vector2f>> ColliderMaker::get_parts(std::vector<std::vector<char>>& img) {
    int h = img.size(), w = img[0].size();
    std::vector<std::vector<char>> vis(h, std::vector<char>(w, 0));
    
    auto get_part = [&](int x, int y) {
        std::vector<sf::Vector2f> part;
        
        std::function<void(int, int, int)> dfs = [&](int x, int y, int dir) {
            if(vis[y][x]) return;
            vis[y][x] = 1;
            part.push_back(sf::Vector2f(x, y));

            static int DX[8] = {-1,-1,0,1,1,1,0,-1};
            static int DY[8] = {0, 1,1, 1,0,-1,-1,-1};

            for(int d = 0; d < 8; d++) {
                int nx = x + DX[(d + dir + 8) % 8], ny = y + DY[(d + dir + 8) % 8];
                if(nx >= 0 and nx < w and ny >= 0 and ny < h) {
                    if(img[ny][nx] == 1) {
                        dfs(nx, ny, -d);
                    }
                }
            }
        };

        dfs(x, y, 0);

        decltype(part) res;

        auto on_line = [&](sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p) {
            auto d1 = p1 - p2;
            auto d2 = p1 - p;
            return d1.x * d2.y == d1.y * d2.x;
        };

        for(auto& p : part) {
            while(res.size() >= 2u and on_line(res[int(res.size()) - 2], res.back(), p)) {
                res.pop_back();
            }
            res.push_back(p);
        }

        if(res.size() >= 3u) {
            if(on_line(res[int(res.size()) - 2], res.back(), res[0])) {
                res.pop_back();
            }
        }

        if(res.size() >= 3u) {
            if(on_line(res.back(), res[0], res[1])) {
                res.erase(res.begin());
            }
        }

        std::reverse(res.begin(), res.end());

        return res;
    };

    std::vector<std::vector<sf::Vector2f>> parts;

    for(int y = 0; y < h; y++) {
        for(int x = 0; x < w; x++) {
            if(img[y][x] == 1 and not vis[y][x]) {
                parts.push_back(get_part(x, y));
            }
        }
    }

    for(int y = 0; y < h; y++) {
        for(int x = 0; x < w; x++) {
            img[y][x] = 0;
        }
    }

    for(auto& part : parts) {
        for(auto& p : part) {
            img[p.y][p.x] = 1;
        }
    }

    return parts;
}

ConvexColliders* ColliderMaker::make_collider(sf::Image image, unsigned int decrease) {
    auto[w, h] = image.getSize();
    std::vector<std::vector<char>> img(h, std::vector<char>(w));

    for(int y = 0; y < int(h); y++) {
        for(int x = 0; x < int(w); x++) {
            auto p = image.getPixel(x, y);
            if(p.a == 0) {
                img[y][x] = 0;
            } else {
                img[y][x] = 1;
            }
        }
    }

    while(decrease--) {
        ColliderMaker::decrease(img);
    }

    ColliderMaker::make_border(img);

    auto parts = ColliderMaker::get_parts(img);

    ConvexColliders* collider = new ConvexColliders();

    for(auto& part : parts) {
        auto triangles = ColliderMaker::hertel_mehlhorn(part);
        for(auto& triangle : triangles) {
            collider->add_collider(triangle, {0, 0}, {0, 0});
        }
    }

    return collider;
}