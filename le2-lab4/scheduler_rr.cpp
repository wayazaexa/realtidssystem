/**
 * @file scheduler_rr.cpp
 * @author Joakim Englund (joakimenglund@protonmail.com)
 * @brief This program will calculate wait time and turnaround time for tasks
 *          (I just realised I called them processes instead of tasks, TODO: rename everything),
 *          as well as average wait time and average turnaround time.
 *          I'm choosing to accomplish this by creating a round robin scheduler simulation.
 * @version 0.1
 * @date 2023-10-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <queue>
#include <iostream>
#include "process.hh"

/**
 * @brief TODO: his will be where the magic happens.
 *          This is where I'll simulate each tick and calculate what is going to happen based off of that.
 *          Will probably end up being inside a loop until ready_queue is empty and there are no running task.
 * 
 * @param curr_time 
 */
void tick(uint16_t &curr_time)
{
    ;
}

/**
 * @brief Helper function for process_list.sort().
 *          Compares two object of class Process and returns true if the arrival time
 *          of the first is less than the arrival time of the second.
 *
 * @param first
 * @param second
 * @return bool
 */
bool compare_at(const std::shared_ptr<Process> &first, const std::shared_ptr<Process> &second)
{
    return first->get_at() < second->get_at();
}

/**
 * @brief This function handles user input at the start of the run.
 *          Only exists to make main() look cleaner.
 *
 * @param process_list
 * @param processes
 * @param quantum
 */
void data_input(std::list<std::shared_ptr<Process>> &process_list, uint16_t &processes, uint16_t &quantum)
{
    std::cout << "Enter number of processes: ";
    std::cin >> processes;
    std::cout << "Enter time quantum: ";
    std::cin >> quantum;
    std::cout << "\nEnter the arrival time and burst time of each process: \n";
    for (int i = 0; i < processes;)
    {
        // Temporary variables for process data
        uint16_t tmp_id;
        uint16_t tmp_at;
        uint16_t tmp_bt;

        tmp_id = ++i;
        std::cin >> tmp_at;
        std::cin >> tmp_bt;
        Process::CreateProcess(process_list, tmp_id, tmp_at, tmp_bt);
    }
    process_list.sort(compare_at);
}

/**
 * @brief This function handles output of the processed data to be presented to the user.
 *          Currently it only prints the sorted list of the tasks. TODO: Fix that!
 * 
 * @param process_list 
 */
void data_output(std::list<std::shared_ptr<Process>> &process_list)
{
    std::cout << "\n\nData: \n";
    for (const auto &process : process_list)
    {
        std::cout << "p" << process->get_id() << ": " << process->get_at() << ", " << process->get_bt() << "\n";
    }
    std::cout << "\n";
}

/**
 * @brief Main function. Sets everything up and calls the other functions.
 *
 * @return int
 */
int main(void)
{
    // Input data and current time
    uint16_t processes;
    uint16_t quantum;
    uint16_t current_time = 0;
    // List and queue of processes
    std::list<std::shared_ptr<Process>> process_list; // shared_ptr or unique_ptr?
    std::queue<std::shared_ptr<Process>> ready_queue; // -"-

    // Request and handle user input
    data_input(process_list, processes, quantum);

    // Simulate ticks in ms
    tick(current_time);

    // Output data
    data_output(process_list);

    return 0;
}
