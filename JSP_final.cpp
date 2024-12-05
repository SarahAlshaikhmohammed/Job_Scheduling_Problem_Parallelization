#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <tuple>
#include <omp.h>

// Global variable to accumulate recursive call depth
int recursive_depth = 0;
omp_set_num_threads(10);
// Function to pick the latest available slot recursively
int pick_latest_slot_recursively(int deadline, std::vector<int> &schedule)
{
    #pragma omp atomic
    recursive_depth++;

    if (deadline <= 0)
    {
        #pragma omp atomic
        recursive_depth--;
        return -1; 
    }

    if (schedule[deadline - 1] == -1)
    {
        #pragma omp atomic
        recursive_depth--;
        return deadline - 1; 
    }

    int result = pick_latest_slot_recursively(deadline - 1, schedule);

    #pragma omp atomic
    recursive_depth--;

    return result;
}

// Function to schedule jobs using a greedy algorithm
std::tuple<double, std::string> greedy_schedule(const std::vector<int> &deadlines, const std::vector<double> &profits)
{
    int num_jobs = deadlines.size();
    int max_deadline = std::min(*std::max_element(deadlines.begin(), deadlines.end()), num_jobs);
    std::vector<int> schedule(max_deadline, -1); // Initialize schedule with -1
    double total_profit = 0;

    // Sort jobs by profits in descending order
    std::vector<int> sorted_indices(num_jobs);
    for (int i = 0; i < num_jobs; i++)
    {
        sorted_indices[i] = i;
    }

    std::sort(sorted_indices.begin(), sorted_indices.end(), [&](int a, int b)
              { return profits[a] > profits[b]; });

    #pragma omp parallel for reduction(+:total_profit)
    for (int i = 0; i < sorted_indices.size(); i++)
    {
        int job_idx = sorted_indices[i];
        int slot = pick_latest_slot_recursively(deadlines[job_idx], schedule);

        if (slot != -1)
        {
            #pragma omp critical
            {
                schedule[slot] = job_idx;
            }
            #pragma omp atomic
            total_profit += profits[job_idx];
        }
    }

    // Build the job schedule string
    std::string final_schedule;
    for (int job : schedule)
    {
        if (job != -1)
        {
            final_schedule += "J" + std::to_string(job + 1) + " -> ";
        }
    }

    if (!final_schedule.empty())
    {
        final_schedule.erase(final_schedule.length() - 4); // Remove the trailing " -> "
    }

    return {total_profit, final_schedule};
}

// Main function
void job_sequencing()
{
    recursive_depth = 0; // Reset recursive depth

    std::vector<int> deadlines = {164, 29, 7, 190, 71, 63, 58, 36, 189, 27, 174, 190, 229, 140, 23, 152, 109, 9, 8, 24, 56, 60, 130, 155, 7, 144, 51, 184, 167, 180, 140, 108, 57, 115, 151, 72, 208, 223, 2, 195, 207, 41, 179, 109, 88, 72, 40, 56, 246, 196, 87, 27, 24, 98, 25, 92, 217, 89, 155, 68, 207, 12, 187, 118, 138, 32, 250, 237, 97, 21, 142,
                                  76, 213, 161, 159, 227, 221, 93, 148, 50, 181, 18, 12, 170, 59, 198, 75, 21, 219, 60, 222, 26, 98, 72, 117, 163, 214, 94, 42, 95, 91, 54, 172, 69, 180, 240, 175, 166, 19, 156, 163, 44, 137, 187, 63, 42, 119, 98, 70, 237, 164, 177, 143, 57, 176, 84, 216, 197, 199, 15, 59, 211, 9, 207, 81, 103, 69, 17, 55, 234, 242, 146, 225, 184, 81, 55, 168, 128, 102, 227, 235, 165, 118, 37, 68, 36, 64, 191, 144, 138, 68, 192, 150, 110, 230, 150, 103, 93, 57, 36, 131, 127, 24, 194, 13, 221, 29, 40, 161, 41, 203, 175, 109, 153, 17, 99, 98, 153, 120, 136, 65, 249, 142, 221, 242, 3, 175, 185, 30, 175, 227, 138, 193, 69, 197, 165, 88, 29, 76, 112, 41, 117, 1, 245, 185, 225, 185, 68, 249, 129, 196, 46, 130, 234, 28, 223, 161, 77, 216, 164, 130, 156, 51, 40, 96, 196, 42, 139, 245, 200, 237, 136, 236, 1, 154, 83, 126, 5, 29, 238};
    std::vector<double> profits = {42.67, 98.68, 82.61, 31.55, 31.68, 61.06, 17.09, 75.87, 83.44, 98.02, 57.94, 21.32, 69.38, 95.22, 24.86, 57.49, 64.59, 96.79, 93.6, 77.97, 72.09, 74.17, 45.91, 70.45, 43.61, 90.97, 50.63, 32.31, 15.76, 11.89, 59.85, 62.96, 10.65, 73.71, 15.3, 16.07, 12.83, 39.74, 56.27, 35.06, 53.69, 58.53, 75.1, 89.41, 61.86, 31.87, 52.57, 46.64, 18.49, 69.31, 41.89, 47.0, 87.75, 14.88, 68.81, 68.16, 15.46, 75.54, 82.05, 19.83, 27.24, 58.27, 22.62, 26.51, 51.64, 88.7, 16.78, 82.72, 87.04, 18.81, 68.69, 58.65, 11.33, 18.39, 77.82, 31.27, 46.58, 53.32, 87.82, 91.22, 24.82, 10.19, 45.14, 93.39, 80.66, 35.67, 72.69, 75.75, 80.5, 69.57, 53.8, 27.09, 29.59, 15.26, 76.22, 15.49, 38.22, 14.51, 52.91, 92.74, 57.8, 15.12, 55.7, 86.62, 16.17, 16.12, 87.56, 46.34, 94.74, 61.27, 62.1, 13.58, 17.38, 69.16, 60.87, 38.47, 33.47, 70.28, 38.28, 33.91, 21.78, 68.1, 51.15, 93.61, 94.22, 10.84, 65.9, 60.67, 19.0, 58.39, 55.53, 21.92, 41.41, 16.19, 31.99, 35.65, 49.44, 58.89, 37.23, 98.55, 82.64, 57.6, 70.11, 59.91, 93.86, 19.32, 89.03, 33.8, 90.07, 76.82, 23.99, 35.36, 28.96, 40.86, 71.87, 86.76,
                                   55.49, 32.6, 91.73, 14.57, 67.09, 84.64, 13.97, 40.02, 21.77, 98.18, 24.54, 49.77, 73.51, 60.48, 20.07, 95.05, 72.19, 23.41, 13.24, 43.23, 59.73, 48.68, 13.76, 42.82, 93.98, 97.5, 13.59, 42.2, 71.39, 70.02, 41.83, 60.39, 88.72, 97.65, 77.45, 93.32, 31.31, 24.63, 81.99, 25.93, 47.11, 26.14, 93.2, 80.41, 47.05, 70.29, 76.16, 32.34, 24.33, 73.12, 44.43, 13.49, 52.36, 27.96, 92.66, 41.47, 83.85, 88.42, 30.06, 69.4, 45.86, 35.07, 16.25, 79.6, 41.6, 55.85, 71.16, 85.93, 39.8, 12.48, 88.93, 33.51, 62.25, 98.52, 13.44, 63.69, 41.11, 80.78, 49.28, 98.58, 20.41, 90.96, 27.11, 13.99, 49.25, 56.79, 82.59, 71.82, 94.62, 76.33, 27.73, 48.82, 95.4, 92.87};

    // Perform job sequencing and calculate the total profit and job schedule
    auto [total_profit, schedule] = greedy_schedule(deadlines, profits);

    // Print results
    std::cout << "\nFinal schedule: " << schedule << std::endl;
    std::cout << "Total profit = " << total_profit << std::endl;
}

int main()
{
    job_sequencing();
    return 0;
}
