#define _XOPEN_SOURCE 700

#include "../src/control.h"
#include "test.h"

enum move update(struct car *car);

enum floortype get_type(struct map *map, char cell, int i, int j)
{
    enum floortype type = BLOCK;

    switch (cell)
    {
        case 's':
            map->start.x = i + 0.5f;
            map->start.y = j + 0.5f;
        case 'r':
            type = ROAD;
            break;
        case 'f':
            type = FINISH;
            break;
        case 'g':
            type = GRASS;
            break;
        default:
            break;
    }

    return type;
}

void load_map(struct map *map, FILE *file)
{
    char *line = NULL;
    long int size = 0;
    size_t cap = 0;
    int j = 0;

    while ((size = getline(&line, &cap, file)) > 0)
    {
        for (int i = 0; i < size; i++)
        {
            enum floortype type = get_type(map, line[i], i, j);
            map_set_floor(map, type, i, j);
        }
        j++;
        free(line);
        line = NULL;
    }
}

struct map *read_map(char *filename)
{
    FILE *file = fopen(filename, "r");
    char *line = NULL;
    long int size = 0;
    size_t cap = 0;
    int size_x = 0;
    int size_y = 0;

    while ((size = getline(&line, &cap, file)) > 0)
    {
        if (size > size_x)
            size_x = size;
        size_y++;
        free(line);
        line = NULL;
    }
    if (size_x > 0)
        --size_x;

    rewind(file);

    struct map *map = map_new(size_x, size_y, 0.0f, 0.0f);

    load_map(map, file);

    fclose(file);
    return map;
}

int main(int argc, char **argv)
{
    if (argc != 2)
      {
	printf("arguments: %s path_to_map.frc\n", argv[0]);
        return 1;
      }

    struct map *map = read_map(argv[1]);
    struct car *car = car_new(map);

    car->direction.x = 0.0f;
    car->direction.y = -1.0f;
    car->direction_angle = 3.0f / 2.0f * M_PI;

    unsigned step = 0;
    enum status state = NONE;

    do {
        step++;
        state = car_move(car, update(car));
    } while (state == NONE);

    car_delete(car);
    map_delete(map);

    if (state == END)
        printf("Map finished in %d steps!\n", step);
    else
        printf("Crash after %d steps!\n", step);

    return 0;
}
