# Computer Graphics - Boids Simulation

Numerous video games and physical simulation systems involve the planning and coordination of group movement. In this work, we developed a program that models a flock of virtual birds ("boids") navigating in a three-dimensional space.

## Compile and Run

This work compiles and runs on Linux and Mac OS X. It was tested on Ubuntu Linux 10.04 and Mac OS X 10.7.2.

To compile on Linux, it is necessary to install the libraries for development in X11 and OpenGL (GL, GLU, GLUT). On Ubuntu Linux, simply install the `freeglut3-dev` package, which contains all these dependencies. It is also necessary to install the C++ compiler, available in the "g++" package. Such packages can be easily installed using the following commands:

```
# apt-get install freeglut3-dev
# apt-get install g++
```

To compile on Mac OS X, you need to install the C/C++ compilers, the make tool, and the X11 environment. Compilers and tools are automatically installed during Xcode installation (version 4.2.1 tested). The X11 environment can be found on the Mac OS X Leopard/Snow Leopard installation DVD, and is already installed by default on Mac OS X Lion.

Once the environment is configured, compile and run the program by invoking the `make` command within the `src` directory.

## Simulation Instructions

The simulation starts with just the leader boid, who performs a continuous circular movement around the tower. Boids can be created by the user, which will follow the leader boid and form a pack.

To add boids to the game, use the `+` key on your keyboard. Add as many boids as you want. The `-` key randomly removes a boid from the game.

The `1` and `2` keys switch between possible viewing modes.

The `P` key pauses or unpauses the simulation. The `Q` key exits the simulation and closes the program.

## Specification

Each boid is an independent entity, which has a position in space and an associated velocity vector. The movement of the flock follows a basic set of elements:

- **Separation**: each goat must maintain a certain minimum separation distance between itself and neighboring goats (or other obstacles that may be present in the scenario).
- **Cohesion**: The boids must remain united in the herd. In the presence of obstacles, they may even separate to avoid the obstacles, but must regroup once the obstacles are overcome (assuming the obstacle is not too large).
- **Alignment**: Boids tend to move in the same direction and at the same speed as neighboring boids.

The above set of constraints defines the nature of movement at a local level, but does not define the collective movement of the group. To do so, the program must implement a special boid that represents the objective, that is, the group, as a whole, tends to fly in the direction of this objective-boid. Both the boids and the objective-boid must be initialized with rich values, and the velocity vector of the objective-boid must be controlled by the user through keyboard (or mouse) commands. Remember to adjust the direction and magnitude of the velocity vector of each boid, in order to maintain the group.

1. There must be a reasonably large defined world, with a “floor” that can be modeled by a horizontal plane. In the center of this world there must be a cone-shaped tower.
2. There must be at least 3 distinct viewing modes: the first with the eye positioned at the top of the tower in the center of the world, the second behind the flock, at a fixed distance, and the third perpendicular to the vector that represents the flock's speed , and parallel to the plane of the floor. In all three modes, the viewing direction is from the eye to the center of the flock (midpoint of each boid's positions) with the normal pointing perpendicular to the ground plane.
3. The world must be illuminated, being able to use the standard OpenGL global model.
4. Each boid must be drawn as a three-dimensional polyhedron. It could be something
simple, like the 5 pyramids displayed below.
5. The number of boids must be able to vary according to user commands, for example
For example, pressing the “+” key should create a new boid randomly (near
group) and the “-” key randomly eliminates a boid from the group.
6. The boids must have lively movements corresponding to the flapping of the wings. That
can be implemented by adding a state to each boid, which corresponds to the position of the wing. Each boid has its own state independent of the others.

![A Boid](https://github.com/felipead/boids/blob/main/doc/boid.png "A Boid")

## Bonus Points

1. **Obstacles**: in addition to the ground and the viewing tower, other objects can be added to the scene (suggestions being spheres and cones, whose intersection algorithms with rays are given in the course notes) and the boids must avoid collisions with these obstacles including violating other factors determining group behavior. The objective-boid is a ghost, and passes through obstacles.
2. **Shadows**: It is not necessary to project a shadow from one boid to another, but just a simple parallel projection of the boids on the ground. More sophisticated models may have more extra points
3. **Fog**: functionality added by keyboard command, which can be enabled and disabled during execution
4. **Pause mode**: activated by the keyboard to simulate the oxen freezing the image (oxen can be added and removed during the pause). Also add debug mode. Including step-by-step execution mode with printout for debugging.
5. **Reshape**: allow resizing of the viewport.
6. **Banking**: an object in space is subject to rotations in 3 basic axes. Assuming the orthonormal basis where X points forward (relative to the object), Z upwards (relative to the world) and Y is the vector product of , and makes the object point up when it goes up and down when it goes down. The rotation around Z is called yaw, and basically makes the object point in the direction (sideways) in which it flies. The rotation in X is called row, and the act of executing this rotation is called banking. The row angle is related to the rate of the curve (second derivative of the trajectory). Calculating a smooth row angle can be tricky, so pay attention.
