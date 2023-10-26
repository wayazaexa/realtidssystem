/**
 * @file scheduler_rr.cpp
 * @author Joakim Englund (joakimenglund@protonmail.com)
 * @brief This program will calculate wait time and turnaround time for tasks
 *          as well as average wait time and average turnaround time.
 *          I'm choosing to accomplish this by creating a round robin scheduler simulation.
 * @version 0.3
 * @date 2023-10-24
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <iomanip>
#include "task.hh"

/**
 * @brief Helper function for incoming_tasks.sort().
 *          Compares two object of class Task and returns true if the arrival time
 *          of the first is less than the arrival time of the second.
 *
 * @param &first
 * @param &second
 * @return bool
 */
bool compare_at(const std::shared_ptr<Task> &first, const std::shared_ptr<Task> &second)
{
    return first->get_at() < second->get_at();
}

/**
 * @brief Helper function for task_list.sort().
 *          Compares two object of class Task and returns true if the id
 *          of the first is less than the id of the second.
 *
 * @param &first
 * @param &second
 * @return bool
 */
bool compare_id(const std::shared_ptr<Task> &first, const std::shared_ptr<Task> &second)
{
    return first->get_id() < second->get_id();
}

/**
 * @brief This function handles user input at the start of the run.
 *          Only exists to make main() look cleaner.
 *
 * @param &incoming_tasks - list of pointers to tasks
 * @param &tasks - number of tasks
 * @param &quantum - quantum for the tasks
 */
void data_input(std::list<std::shared_ptr<Task>> &incoming_tasks, uint16_t &tasks, uint16_t &quantum)
{
    std::cout << "Enter number of tasks: ";
    std::cin >> tasks;
    std::cout << "Enter time quantum: ";
    std::cin >> quantum;
    std::cout << "\nEnter the arrival time and burst time of each task: \n";

    for (int i = 0; i < tasks;)
    {
        // Temporary variables for task data
        uint16_t tmp_id;
        uint16_t tmp_at;
        uint16_t tmp_bt;

        tmp_id = ++i;
        std::cin >> tmp_at;
        std::cin >> tmp_bt;
        Task::CreateTask(incoming_tasks, tmp_id, tmp_at, tmp_bt);
    }
    // Sort the list of incoming tasks before we're done
    incoming_tasks.sort(compare_at);
}

/**
 * @brief This function handles output of the processed data to be presented to the user.
 *
 * @param &task_list - list of pointers to tasks
 * @param num_tasks - number of tasks
 */
void data_output(std::list<std::shared_ptr<Task>> &task_list, uint16_t num_tasks)
{
    task_list.sort(compare_id);
    uint16_t tot_tat = 0;
    uint16_t tot_wt = 0;
    std::cout << "\n\nData: \n";

    for (const auto &task : task_list)
    {
        tot_tat += task->get_wt() + task->get_bt();
        tot_wt += task->get_wt();
        std::cout << "Process " << task->get_id() << ". Waiting time: " << task->get_wt() << ", Turnaround time: " << task->get_wt() + task->get_bt() << "\n";
    }

    std::cout << std::fixed << std::setprecision(2) << "\n\n";
    std::cout << "Average wait time: " << static_cast<double>(tot_wt) / num_tasks << "\n";
    std::cout << "Average turnaround time: " << static_cast<double>(tot_tat) / num_tasks << "\n\n";
}

/**
 * @brief Set up the different task lists for the upcoming tick by checking for
 *          newly arrived tasks and running task that finished
 * 
 * @param &curr_time - current time
 * @param &running_task 
 * @param &incoming_tasks - 
 * @param &ready_queue 
 * @param &completed_tasks 
 * @param &quantum 
 * @param &remaining_quantum 
 */
void setup_lists(uint16_t &curr_time, std::shared_ptr<Task> &running_task, std::list<std::shared_ptr<Task>> &incoming_tasks,
                 std::list<std::shared_ptr<Task>> &ready_queue, std::list<std::shared_ptr<Task>> &completed_tasks, const uint16_t &quantum, uint16_t &remaining_quantum)
{
    // Check the incoming_tasks for newly arrived tasks
    while (!incoming_tasks.empty() && incoming_tasks.front()->get_at() <= curr_time) // == should work fine, but just in case
    {
        // Move newly arrived task to the ready queue and remove it from incoming tasks
        ready_queue.push_back(incoming_tasks.front());
        incoming_tasks.pop_front();
    }

    // Check if we have a running task who's not allowed to be here anymore and move it to the ready queue
    if (running_task != nullptr)
    {
        // Check if the running task has finished
        if (running_task->get_rem_bt() == 0)
        {
            completed_tasks.push_back(running_task);
        }
        else if (remaining_quantum == 0) // Check if the running task has reached the end of its allocated time slot
        {
            ready_queue.push_back(running_task);
        }
        else
        {
            return;
        }
        running_task = nullptr;      // Reset running_task for the upcoming tick
        remaining_quantum = quantum; // Reset remaining quantum for next task
    }
}

bool scheduler(uint16_t &curr_time, std::shared_ptr<Task> &running_task, std::list<std::shared_ptr<Task>> &incoming_tasks,
               std::list<std::shared_ptr<Task>> &ready_queue, std::list<std::shared_ptr<Task>> &completed_tasks, const uint16_t &quantum, uint16_t &remaining_quantum)
{
    // Make sure all the lists are updated for this tick
    setup_lists(curr_time, running_task, incoming_tasks, ready_queue, completed_tasks, quantum, remaining_quantum);

    // Check if we still have a running task
    if (running_task != nullptr)
    {
        // This simulates letting the task run for one tick
        running_task->dec_rem_bt();
        --remaining_quantum;

        // Update wait_time for tasks in ready_queue
        for (const auto &task : ready_queue)
        {
            task->inc_wt();
        }
    }
    else if (!ready_queue.empty()) // No running task, and ready queue is not empty
    {
        // Move task from ready queue to running
        running_task = ready_queue.front();
        ready_queue.pop_front();

        // This simulates letting the task run for one tick
        running_task->dec_rem_bt();
        --remaining_quantum;

        // Update wait_time for tasks in ready_queue
        for (const auto &task : ready_queue)
        {
            task->inc_wt();
        }
/*
        // Check if the running task has finished
        if (running_task->get_rem_bt() == 0)
        {
            completed_tasks.push_back(running_task);
            running_task = nullptr;
            remaining_quantum = quantum; // Reset remaining quantum for next process
        }
        else if (remaining_quantum == 0) // Check if the running task has reached the end of its allocated time slot
        {
            incoming_tasks.push_front(running_task);
            running_task = nullptr;
            remaining_quantum = quantum; // Reset remaining quantum for next process
        }*/
    }
    else // No running task, nothing in the ready queue - idling processor
    {
        // std::cout << "No running task, nothing in the ready queue - idling processor\n";
        if (incoming_tasks.empty()) // If we're idling and the list of incoming tasks is empty - we're done.
        {
            curr_time++;
            return true; // Signal that we're done
        }
    }

    // Update tick-counter
    ++curr_time;
    // std::cout << "In scheduler, curr_time: " << curr_time << "\n";

    return false; // Signal that we're not done
}

/**
 * @brief Main function. Sets everything up and calls the other functions.
 *
 * @return int
 */
int main(void)
{
    // Input data and current time
    uint16_t num_tasks;
    uint16_t quantum;
    uint16_t current_time = 0;
    // Lists of tasks
    std::list<std::shared_ptr<Task>> incoming_tasks;
    std::list<std::shared_ptr<Task>> ready_queue;
    std::list<std::shared_ptr<Task>> completed_tasks;
    // Running task
    std::shared_ptr<Task> running_task = nullptr;

    // Request and handle user input
    data_input(incoming_tasks, num_tasks, quantum);
    uint16_t remaining_quantum = quantum;

    while (!scheduler(current_time, running_task, incoming_tasks, ready_queue, completed_tasks, quantum, remaining_quantum))
    {
    }
    // std::cout << "Current time: " << current_time << "\n";
    //  Output data
    data_output(completed_tasks, num_tasks);

    return 0;
}
