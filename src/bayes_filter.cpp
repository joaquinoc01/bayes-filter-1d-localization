#include <iostream>
#include <vector>
#include <numeric>

#include "bayes_filter.hpp"

BayesFilter::BayesFilter(int world_size, float sensor_noise, float motion_noise)
    : world_size(world_size), sensor_noise(sensor_noise), motion_noise(motion_noise) {

    belief = {0.1, 0.4, 0.2, 0.2, 0.1};  // Non uniform belief at the start

    world = {"door", "wall", "wall", "door", "wall"}; // Initialize world objects
}

void BayesFilter::normalizeBelief(std::vector<float>& vec){
    float total{std::accumulate(vec.begin(), vec.end(), 0.0f)};
    for (auto& v : vec)
    {
        v /= total;
    }
}

void BayesFilter::printBelief() const
{
    std::cout << "Current belief: ";
    for (float b:belief)
    {
        std::cout << b << " ";
    }
    std::cout << std::endl;
}

void BayesFilter::updateBeliefWithMotion()
{
    // Probabilities
    float p_left{motion_noise/2};
    float p_stay{motion_noise/2};
    float p_right{1 - motion_noise};

    // Auxiliar vector
    std::vector<float> new_belief(world_size, 0.0f);

    for (int i = 0; i<world_size; i++)
    {
        // new_belief[i] = P(move_left) * belief[i-1] + P(stay) * belief[i] + P(move_right) * belief[i+1]
        // Assuming a cyclic world, we wrap at the end and at the beginning to use probabilities from the other ends
        new_belief[i] = p_left * belief[(i - 1 + world_size) % world_size] + p_stay * belief[i] + p_right * belief[(i + 1) % world_size];
    }

    normalizeBelief(new_belief);
    belief = std::move(new_belief);
}

void BayesFilter::updateBeliefWithSensor(const std::string& measurement)
{
    // Probabilities
    float p_high{1 - sensor_noise};
    float p_low{sensor_noise};

    // Auxiliar vector
    std::vector<float> new_belief(world_size, 0.0f);

    for (int i = 0; i<world_size ; i++)
    {
        if(world[i] == measurement)
            new_belief[i] = belief[i] * p_high;
        else
            new_belief[i] = belief[i] * p_low;
    }
    normalizeBelief(new_belief);
    belief = std::move(new_belief);
}

int main()
{
    // Simulate a sequence of movements and sensor readings

    // Create a BayesFilter with world size, motion noise and sensor noise
    BayesFilter filter(5, 0.2f, 0.1f);

    // Print initial belief (uniform)
    filter.printBelief();

    // Simulate motion update
    filter.updateBeliefWithMotion();
    filter.printBelief();

    //Simulate sensor update
    filter.updateBeliefWithSensor("door");
    filter.printBelief();

    return 0;
}