def dfs(m, x, y, color, path):
    if m[x][y] == color and len(path) > 0:
        path.append((x, y))
        return path
    path_copy = path.copy()
    path_copy.append((x, y))
    newCoords = [(x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1)]
    for newX, newY in newCoords:
        if not (newX, newY) in path and min(newX, newY) >= 0 and \
            max(newX, newY) < len(m) and \
            (m[newX][newY] == 0 or m[newX][newY] == color):
            result = dfs(m, newX, newY, color, path_copy)
            if result:
                yield result
    return None

def path_exists(m, i):
    path = find_paths(m, i)
    if not path is None:
        return True
    else:
        return False

def find_paths(m, color):
    foundColor = False
    for i in range(len(m)):
        for j in range(len(m)):
            if m[i][j] == color:
              x = i
              y = j
              return dfs(m, x, y, color, [])
    return None


def play(m):
    color = 1
    while color < len(m):
      paths = find_paths(m, color)
      for path in paths:
          for (x, y) in path:
            m[x][y] = color
          isBlocked = False
          i = 1
          while i < len(m) and not isBlocked:
              if i != color and not path_exists(m, i):
                  isBlocked = True
              i += 1
          if isBlocked:
              for (x, y) in path[1:-1]:
                  m[x][y] = 0
          else:
              color += 1
                  

def main():
    m = [[1, 0, 0, 0, 0],
              [2, 3, 0, 3, 1],
              [0, 4, 0, 0, 0],
              [0, 0, 0, 2, 4],
              [5, 0, 0, 0, 5]]
    play(m)

if __name__ == "__main__":
    main()
