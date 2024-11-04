# Cub3D

## Project Overview

Cub3D is a 3D raycasting engine inspired by classic games like *Wolfenstein 3D*. The project aims to recreate the fundamental mechanics of raycasting to render a 3D environment based on a 2D map, showcasing both the principles of computer graphics and game development.

## Framework

The core concept of Cub3D revolves around the raycasting algorithm, which simulates the way light rays interact with objects in a virtual environment. The primary objective is to translate a 2D grid representation of a game map into a 3D perspective view, allowing players to navigate through the environment as if they were physically present.

## Key Features

- **Raycasting**: The project employs a raycasting technique to project rays from the player's viewpoint into the scene. Each ray checks for intersections with walls and calculates the distance to these walls to determine the height of the vertical lines displayed on the screen.

- **Texturing**: Walls in the environment are textured to enhance visual realism. The project utilizes texture mapping techniques to apply images to the walls based on the ray's angle and distance, creating a more immersive experience.

- **Player Movement**: The engine supports basic player movement controls, allowing users to navigate through the environment using keyboard inputs. Movement is handled in a manner that mimics traditional FPS controls.

## Implementation Details

Cub3D is structured around modular components that work together to create the raycasting engine. Below are the primary components of the implementation:

### 1. Raycasting Algorithm

- **Ray Initialization**: For each vertical slice of the screen, a ray is initialized at the player's position and angle.
- **Wall Intersection**: Each ray travels through the scene, checking for intersections with walls. The distance to the nearest wall is calculated, and based on this distance, the height of the wall slice is determined.
- **Rendering**: The vertical line corresponding to the ray's intersection point is rendered on the screen, creating the illusion of depth.

### 2. Texturing System

Cub3D implements a texturing system to map images onto the walls:

- **Texture Loading**: Textures are loaded at the beginning of the program and stored in a format that allows quick access during rendering.
- **Mapping Calculation**: The engine calculates texture coordinates based on the angle of the ray and the distance to the wall to ensure accurate texturing.

### 3. Input Handling

Player input is handled using an event loop that captures keyboard events:

- **Movement**: The player's position is updated based on input keys for forward, backward, and lateral movements.
- **Rotation**: The camera angle can be adjusted by rotating left or right, allowing for a more dynamic viewing experience.

### 4. Rendering Loop

The main rendering loop continuously updates the screen:

- **Frame Rate Control**: The loop runs at a consistent frame rate to ensure smooth visuals.
- **Scene Updates**: Each iteration updates the player's position, checks for collisions, and redraws the scene.

## Contributors
- [@iurilandolt](https://github.com/iurilandolt)
- [@goncalo1021pt](https://github.com/goncalo1021pt)
