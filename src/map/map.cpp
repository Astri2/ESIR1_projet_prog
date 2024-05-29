//
// Created by tomch on 28/05/2024.
//
#include <fstream>
#include <iostream>

#include <cstring> // memset 0
#include <vector>

#include "map.h"
#include "config.h"
#include "cluster.h"
#include "entity/entity.h"
#include "entity/cow.h"
#include "entity/tomato_crop.h"
#include "entity/wheat_crop.h"
#include "game/game.h"

camera map::cam;
player* map::p;

std::vector<cluster> map::clusters;
static unsigned int nb_clusters_x, nb_clusters_y;

static std::vector<cluster const*> get_cluster_to_blit(const camera& camera);

struct csv_line
{
    enum class entity_type
    {
        tile,
        player_spawn,
    } type;

    float x, y;
};

csv_line read_csv_line(const char* line)
{
    char* after;

    csv_line::entity_type type = (csv_line::entity_type)strtoul(line, &after, 10);
    if (after == line)
    {
        std::cerr << "could not read entity type, currently at : " << line << std::endl;
    }
    line = after;

    double x = std::strtod(line, &after);
    if (line == after)
    {
        std::cerr << "could not read x position, currently at : " << line << std::endl;
    }
    line = after;

    double y = std::strtod(line, &after);
    if (after == line)
    {
        std::cerr << "could not read y position, currently at : " << line << std::endl;
    }

    return csv_line{
        type,
        static_cast<float>(x), static_cast<float>(y)
    };
}

void map::load_wsv(const char* file)
{
    std::ifstream input_file(file);

    constexpr uint16_t cw = config::map::cluster_width;
    constexpr uint16_t ch = config::map::cluster_height;

    char buffer[2048] = {0};
    input_file.getline(buffer, 2048);

    char *start = buffer, *after = start;

    // read width
    unsigned long width = strtoul(start, &after, 10);
    if (after == start)
    {
        std::cerr << "could not read width, currently at : " << start << std::endl;
    }
    start = after;

    // read height
    unsigned long height = strtoul(start, &after, 10);
    if (after == start)
    {
        std::cerr << "could not read height, currently at : " << start << std::endl;
    }

    nb_clusters_x = std::ceil((float)width / cw);
    nb_clusters_y = std::ceil((float)height / ch);
    for (unsigned int y = 0; y < nb_clusters_y; y++)
    {
        for (unsigned int x = 0; x < nb_clusters_x; x++)
        {
            clusters.push_back(cluster({
                static_cast<float>(y * ch), static_cast<float>((x + 1) * cw), static_cast<float>((y + 1) * ch),
                static_cast<float>(x * cw)
            }));
        }
    }

    for (; input_file.getline(buffer, 2048);)
    {
        csv_line line = read_csv_line(buffer);
        uint32_t idx = map::find_cluster_idx({{line.x, line.y}});

        switch (line.type)
        {
        case csv_line::entity_type::tile:
            {
                clusters[idx].background.push_back(new sprite({{line.x, line.y}},
                                                              {{config::map::tile_width, config::map::tile_height}},
                                                              {{0, 0}}, {{16, 16}}, "../resources/tiles/water.png"));
            }
            break;

        case csv_line::entity_type::player_spawn:
            {
                // init player
                p = new player({{line.x, line.y}}, {{48.0f, 48.0f}}, 100, 100);
                health_bar* h = new health_bar({10, config::window::height - 25}, {123, 21}, {0, 2}, {89, 16},
                                               "../resources/bars.png", p);
                game::ui_components.push_back(h);
                game::ui_components.push_back(new food_bar({10, config::window::height - 50}, {123, 21}, {0, 1},
                                                           {89, 16}, "../resources/bars.png", p));

                clusters[idx].foreground.insert(p);
                float offset_x = line.x - static_cast<float>(config::viewport::width) / 2.0f, offset_y = line.y -
                          static_cast<float>(config::viewport::height) / 2.0f;
                cam = camera({{offset_x, offset_y}}, {
                                 {
                                     static_cast<float>(config::viewport::width),
                                     static_cast<float>(config::viewport::height)
                                 }
                             }, .8f, 2.f, p);
            }
            break;

        default:
            {
                std::cerr << "unknown entity type in map !" << std::endl;
            }
            break;
        }
    }

    vec2<float> pos = {{1000, 1000}};

    uint32_t idx = map::find_cluster_idx(pos);
    cow* m_cow = new cow(pos, {{32.0f, 32.0f}}, 100);
    clusters[idx].foreground.insert(m_cow);
    clusters[idx].collidables.insert(m_cow);
    clusters[idx].interactibles.insert(m_cow);

    vec2<float> pos2 = {{1055, 1055}};

    uint32_t idx2 = map::find_cluster_idx(pos2);
    tomato_crop* m_tomato_crop = new tomato_crop(pos2, {{16.0f, 16.0f}});
    clusters[idx2].foreground.insert(m_tomato_crop);
    clusters[idx2].interactibles.insert(m_tomato_crop);


    vec2<float> pos3 = {{1020, 1055}};

    uint32_t idx3 = map::find_cluster_idx(pos3);
    wheat_crop* m_wheat_crop = new wheat_crop(pos3, {{16.0f, 16.0f}});
    clusters[idx3].foreground.insert(m_wheat_crop);
    clusters[idx3].interactibles.insert(m_wheat_crop);
}

void map::draw()
{
    std::vector<const cluster*> cs = get_cluster_to_blit(cam);
    for (const cluster* c : cs)
    {
        for (sprite* e : c->background)
        {
            e->draw(cam);
        }
    }
    for (const cluster* c : cs)
    {
        for (sprite* e : c->foreground)
        {
            e->draw(cam);
        }
    }
}

void map::update(float dt)
{
    std::vector<const cluster*> cs = get_cluster_to_blit(cam);
    for (const cluster* c : cs)
    {
        for (entity* e : c->background)
        {
            e->update(dt);
        }

        auto foreground_copy(c->foreground);
        for (entity* e : foreground_copy)
        {
            e->update(dt);
        }
    }
    cam.update();
}

// protected utilities

uint32_t map::find_cluster_idx(const vec2<float>& position)
{
    return ((int)position.y / config::map::cluster_height) * nb_clusters_x + ((int)position.x /
        config::map::cluster_width);
}

std::vector<cluster*> map::get_surrounding_clusters(uint32_t cluster_idx)
{
    std::vector<cluster*> res;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            uint32_t idx = cluster_idx + i * nb_clusters_x + j;
            // assuming negatives values aren't to negatives, could use boolean logic in for boundaries instead
            if (idx < nb_clusters_x * nb_clusters_y)
                res.push_back(&map::clusters[idx]);
        }
    }
    return res;
}

std::vector<cluster const*> get_cluster_to_blit(const camera& camera)
{
    // computes the rectangle of clusters that should be blit, given the top_left and bottom_right clusters
    const uint32_t top_left_cluster_idx = map::find_cluster_idx({camera.get_outer_range().top_left()});
    const uint32_t bottom_right_cluster_idx = map::find_cluster_idx({camera.get_outer_range().bottom_right()});
    const uint32_t dx = (bottom_right_cluster_idx - top_left_cluster_idx) % nb_clusters_x;
    const uint32_t dy = (bottom_right_cluster_idx - top_left_cluster_idx) / nb_clusters_x;

    std::vector<cluster const*> res;
    for (uint32_t i = 0; i < dy; i++)
    {
        for (uint32_t j = 0; j < dx; j++)
        {
            uint32_t idx = top_left_cluster_idx + i * nb_clusters_x + j;
            res.emplace_back(&map::clusters[idx]);
        }
    }
    return res;
}

interactible* map::perceive(player* user, std::vector<cluster*> clusters)
{
    interactible* nearest = nullptr;
    float nearest_dist = 0.0f;

    for (cluster* c : clusters)
    {
        for (interactible* objet : c->interactibles)
        {
            const float shared_dist = physics::shared_distance(user->get_interact_zone(), objet->get_interact_zone());

            if (shared_dist > nearest_dist)
            {
                nearest = objet;
                nearest_dist = shared_dist;
            }
        }
    }

    return nearest;
}
