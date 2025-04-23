# 1D Bayes Filter Localization

This repository implements a 1D Bayes Filter for robot localization using motion and sensor data. The robot operates in a 1D world with various objects (e.g., walls and doors). The filter updates the belief about the robot's position based on its movement and sensor readings.

## Table of Contents

1. [Project Overview](#project-overview)
2. [How to Compile and Run](#how-to-compile-and-run)
3. [Results](#results)
4. [License](#license)

## Project Overview

This project uses a 1D Bayes Filter to localize a robot based on two sources of data:
1. **Motion data**: Updates the belief based on the robot's movement.
2. **Sensor data**: Updates the belief based on sensor readings about the world.

The world is modeled as a cyclic grid where the robot can be in different positions. The robot has a belief distribution representing the probability of being in each position.

## How to Compile and Run

Follow these steps to compile and run the 1D Bayes Filter program:

### Prerequisites

- **CMake**: A tool to build and configure the project.
- **C++ Compiler**: GCC or Clang is recommended.

### Steps

1. **Clone the repository**:

   First, clone this repository to your local machine:

   ```bash
   git clone https://github.com/joaquinoc01/bayes-filter-1d-localization.git
   cd bayes-filter-1d-localization
   ```

2. **Create the build directory**:

   We will create a separate directory for building the project:

   ```bash
   mkdir build
   cd build
   ```

3. **Generate the build files with CMake**:

   Run the following command to generate the necessary build files:

   ```bash
   cmake ..
   ```

4. **Compile the project**:

   Once the build files are generated, compile the project using `make`:

   ```bash
   make
   ```

5. **Run the program**:

   After compilation, you can run the Bayes Filter executable:

   ```bash
   ./bayes_filter
   ```

   The output will show the robot's belief at each step as it updates based on motion and sensor data.

## Results

Here is an example of the output from running the program with some initial settings:

```
Current belief: 0.1 0.4 0.2 0.2 0.1
Current belief: 0.37 0.205 0.21 0.11 0.105
Current belief: 0.606557 0.0840164 0.0860656 0.180328 0.0430328
```

### Explanation:
- The robot starts with a belief where it is most likely at position 1: `0.1 0.4 0.2 0.2 0.1`.
- After the first motion update, the belief changes slightly due to uncertainty in movement: `0.37 0.205 0.21 0.11 0.105`.
- After the sensor update, the belief sharpens to: `0.606557 0.0840164 0.0860656 0.180328 0.0430328`.

We observe this behavior because the robot receives a **sensor reading of a "door"**, and in the world model (e.g., `{"door", "wall", "wall", "door", "wall"}`), doors exist at positions 0 and 3. This sensor measurement increases the probability of the robot being in those locations. Since the belief was already highest near those positions from the motion update, the final result reflects a **sharpened belief peaking at those plausible "door" positions**, especially at index 0.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
