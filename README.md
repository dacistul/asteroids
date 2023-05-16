2D Game - Asteroids

This is a readme file for the 2D game "Asteroids". The game is developed using various logic headers and object headers. Below, you will find a breakdown of the different components and functionalities of the game.
Logic Headers
Physics

    Position: Handles the position of objects in the game.
    Drag: Controls the drag applied to objects, affecting their movement.
    Angle: Manages the rotation angle of objects.
    Velocity: Determines the speed and direction of objects.

Render

    VBO (Vertex Buffer Object): Handles the storage of vertex data.
    VAO (Vertex Array Object): Manages the configuration of vertex attributes.
    IBO (Index Buffer Object): Stores the indices for indexed rendering.

Collision

    Distance and Normal: Calculates the distance between colliders and the normal vector.
    Collider (general): Obtains the position, skin, normal, and distance between two colliders.
    Disc Collider: Handles the position and skin of a circular collider.
    Window Borders: Defined in the bounding box and uses inverted_collider to contain everything within it.

Object Headers (developed with logic headers)
Ship

    Health: Tracks the health of the player's ship.
    Position: Manages the position of the ship.
    pointTo(direction): Orients the ship towards a specified direction.
    shoot function: Allows the ship to fire projectiles.

Projectile

    Position: Tracks the position of the projectile fired by the ship.

Asteroid

    Color (changes with damage): Manages the color of the asteroid, which changes based on its damage level.
    Position: Handles the position of the asteroid.
    Size: Determines the size of the asteroid.
    Health: Tracks the health of the asteroid.

Object Manager

The Object Manager is responsible for managing the game objects. It provides the following functionality:

    Iterate: Allows iterating through the objects in the manager.
    Push: Adds new objects to the manager.
    Erase: Removes objects from the manager.
    Items: Manages a maximum of 100 asteroids and 100 projectiles.

Main

The main section of the game includes the following components and functionalities:

    Window size: Determines the size of the game window.
    Mouse position: Tracks the position of the mouse.
    Wave Implementation:
        Structure: Defines the structure of a wave in the game.
        Function spawnWave(): Spawns a new wave in the game.
    Player restrictions: The player cannot shoot or move when they die.
    Timer: Increments the wave based on the number of frames.
    Collisions: Handles the collisions between asteroids, the ship and asteroids, projectiles and asteroids, and the frame window and other objects.

Feel free to use this readme file as a reference for understanding the different components and functionalities of the "Asteroids" game.
