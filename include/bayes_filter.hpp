#pragma once

#include <vector>

class BayesFilter {
public:
    // Constructor
    BayesFilter(int world_size, float sensor_noise, float motion_noise);

    // Method to update belief with motion, it is assumed that the robot moves 1 unit
    void updateBeliefWithMotion();

    // Method to update belief with sensor readings
    void updateBeliefWithSensor(const std::string& measurement);

    // Method to normalize the belief
    void normalizeBelief(std::vector<float>& vec);

    // Method to print the current belief
    void printBelief() const;

private:
    // Member variables
    int world_size_; // Size of the world (1D grid)
    float sensor_noise_; // Noise in the sensor readings (for updates)
    float motion_noise_; // Noise in the motion model (for predictions)
    std::vector<float> belief_; // Current belief state (probability distribution)
    std::vector<std::string> world_;
};