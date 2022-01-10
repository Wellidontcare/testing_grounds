import pygame
import numpy as np

SCALING = 10


def draw_grid(screen, grid):
    screen.fill((255, 255, 255))
    h, w = grid.shape
    spacing = screen.get_height() / h
    for y in range(h):
        for x in range(w):
            pos = pygame.Rect((x * spacing, y * spacing), (spacing - 5, spacing - 5))
            image = pygame.Surface((spacing - 1, spacing - 1))
            hue = grid[y, x]
            color = pygame.Color((255, 255, 255))
            color.hsva = ((hue) % 360, 100, 100 if hue > 0 else 0, 100)
            if hue == -1:
                color = (255, 255, 255)
            image.fill(color)
            screen.blit(image, pos)


def dfs(grid, coord, visited, dist=1):
    # print("Drawing ", coord,  "with depth ", dist)
    x, y = coord
    h, w = grid.shape
    if visited[y, x] == 0 and grid[y, x] != 0:
        visited[y, x] = 1
        grid[y, x] = dist
        if x + 1 < w:
            yield from dfs(grid, (x + 1, y), visited, dist + 1)
        if x > 0:
            yield from dfs(grid, (x - 1, y), visited, dist + 1)
        if y + 1 < h:
            yield from dfs(grid, (x, y + 1), visited, dist + 1)
        if y > 0:
            yield from dfs(grid, (x, y - 1), visited, dist + 1)
    yield grid


def bfs(grid, coord):
    visited = set()
    h, w = grid.shape
    queue = []
    x, y = coord
    visited.add(str((x, y)))
    queue.append((x, y, 0))

    while queue:
        node = queue.pop(0)
        if len(queue) > 2 and node[2] != queue[1][2]:
            yield grid
        grid[node[1], node[0]] = node[2]
        x, y, d = node
        neighbours = []
        if x + 1 < w:
            neighbours.append((x + 1, y, d + 1))
        if x > 0:
            neighbours.append((x - 1, y, d + 1))
        if y + 1 < h:
            neighbours.append((x, y + 1, d + 1))
        if y > 0:
            neighbours.append((x, y - 1, d + 1))
        for n in neighbours:
            if str((n[0], n[1])) not in visited and grid[n[1], n[0]] != 0:
                visited = visited | {str((n[0], n[1]))}
                queue.append(n)


def shortest_path(heat_map, grid, origin):
    x, y = origin
    if heat_map[y, x] == 1:
        yield grid
    yield grid
    options = [(1, 0), (0, 1), (0, -1), (-1, 0)]
    h, w = grid.shape
    for o in options:
        xn, yn = x - o[0], y - o[1]
        if xn < 0 or xn >= w or yn < 0 or yn >= h:
            continue
        if heat_map[yn, xn] - heat_map[y, x] == -1:
            grid[yn, xn] = -1
            yield from shortest_path(heat_map, grid, (xn, yn))
            break


if __name__ == "__main__":
    pygame.init()
    screen = pygame.display.set_mode((900, 900))
    clock = pygame.time.Clock()
    FPS = 60

    grid = np.ones(
        (int(screen.get_height() / SCALING), int(screen.get_width() / SCALING))
    )

    while True:
        clock.tick(FPS)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                exit()
            elif event.type == pygame.MOUSEMOTION:
                if event.buttons[0]:
                    x, y = event.pos
                    grid[y // SCALING, x // SCALING] = 0
            elif event.type == pygame.MOUSEBUTTONDOWN:
                y, x = int(event.pos[1] // SCALING), int(event.pos[0] // SCALING)
                if event.button == 3:
                    # for grid in dfs(grid, (x, y),np.zeros_like(grid)):
                    grid[y // SCALING, x // SCALING] = 1
                    draw_grid(screen, grid)
                    pygame.display.flip()
                    for grid in bfs(grid, (x, y)):
                        draw_grid(screen, grid)
                        pygame.display.flip()
                if event.button == 2:
                    for grid_n in shortest_path(grid.copy(), grid.copy(), (x, y)):
                        draw_grid(screen, grid_n)
                        pygame.display.flip()
        draw_grid(screen, grid)
        pygame.display.flip()
