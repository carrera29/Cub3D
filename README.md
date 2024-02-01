# cub3d - RayCasting - ✅Grade 105/100

#### Grade rating
- ✅ = Okay project
- ⭐ = Outstanding project

## Introduction

cub3d is a graphic design project inspired by Wolfenstein 3D, the first true "First Person Shooter" in the history of video games. Developed by Id Software, with John Carmack and John Romero at the helm, Wolfenstein 3D paved the way for iconic games like Doom, Duke Nukem 3D, and Quake. This project aims to explore the practical applications of mathematics through the implementation of a basic RayCaster using the miniLibX library, a tiny and limited graphics library provided by 42 campus which allows you to do basic screen rendering programming.

## Background

RayCasting is a rendering technique used to simulate 3D environments in 2D space. It traces the path of rays from the viewer's perspective to create a 3D-like illusion. In this project, cub3d implements a simplified RayCaster to render a maze-like environment.

## Features

- Smooth window management, allowing tasks like changing windows and minimizing.
- Display of different wall textures based on the direction (North, South, East, West) they are facing.
- Customizable floor and ceiling colors.
- Intuitive controls:
  - Left and right arrow keys for looking left and right in the maze.
  - W, A, S, and D keys for moving the point of view through the maze.
  - ESC key and clicking the red cross on the window frame to close the window and exit the program cleanly.
- Scene description file parsing:
  - Map composed of only six characters: 0 for an empty space, 1 for a wall, and N, S, E, or W for the player's start position and spawning orientation.
  - The map must be closed/surrounded by walls, or the program returns an error.
  - Elements in the file can be in any order, except for the map that has to be at the end of file.
  - Each type of information is separated by one or more spaces.
  - Support for various textures, floor and ceiling colors.
### Example of a .cub file
```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111

```

## Bonus Features

- Wall collisions.
- Minimap system.
- Doors that can open and close.
- Rotation of the point of view with the mouse.

## How to Compile and Execute

1. **Clone the Repository:**
   ```sh
   git clone <repository-url>
   cd cub3d
   ```

2. **Compile:**
   Depending on your OS use:
   ```
   make linux-dep
   ```
   ```
   make mac-dep
   ```
   and finally use:
   ```
   make
   ```
   
4. **Execute:**
   ```
   ./cub3d path/to/scene.cub
   ```

   Replace `path/to/scene.cub` with the path to your scene description file.

## Error Handling

If any misconfiguration is encountered in the scene description file, the program will exit with an error message. For example:
```
./cub3d path/to/invalid_scene.cub
```
Output:
```
Error
Invalid configuration: [error message]
```

*This project was developed as part of a programming curriculum. It demonstrates the application of basic algorithms, mathematics, and graphic design concepts.*
