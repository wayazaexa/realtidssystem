/**
 * @file task.hh
 * @author Joakim Englund (joakimenglund@protonmail.com)
 * @brief Header-file for the Task-class
 * @version 0.1
 * @date 2023-10-24
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef TASK_HH_
#define TASK_HH_
#include <memory>
#include <list>

/**
 * @brief The Task class.
 *          All constructors are private to ensure they're not used.
 *          All Task-objects are instead created via another member function
 *          where I use smart pointers.
 *          And yes, I'm doing this to brush up on smart pointers, because
 *          it's been a while.
 *
 */
class Task
{
private:
    uint16_t id;
    uint16_t arrival_time;
    uint16_t burst_time;
    uint16_t remaining_burst_time;
    uint16_t wait_time;
    // uint16_t turnaround_time;

    /**
     * @brief Default constructor a new Task object (unused at the time).
     *
     */
    Task() {}

    /**
     * @brief Construct a new Task object
     *
     * @param p_id
     * @param p_at
     * @param p_bt
     */
    Task(uint16_t p_id, uint16_t p_at, uint16_t p_bt)
    {
        this->id = p_id;
        this->arrival_time = p_at;
        this->burst_time = p_bt;
        this->remaining_burst_time = p_bt;
        this->wait_time = 0;
    }

    /**
     * @brief Copy constructor of a Task object (unused at the time)
     *
     * @param p
     */
    Task(const Task &p)
    {
        this->id = p.id;
        this->arrival_time = p.arrival_time;
        this->burst_time = p.burst_time;
        this->remaining_burst_time = p.remaining_burst_time;
        this->wait_time = p.wait_time;
    }

public:
    /**
     * @brief Get id
     *
     * @return uint16_t
     */
    uint16_t get_id() { return this->id; }

    /**
     * @brief Get arrival_time
     *
     * @return uint16_t
     */
    uint16_t get_at() { return this->arrival_time; }

    /**
     * @brief Get burst_time
     *
     * @return uint16_t
     */
    uint16_t get_bt() { return this->burst_time; }

    /**
     * @brief Get remaining_burst_time
     *
     * @return uint16_t
     */
    uint16_t get_rem_bt() { return this->remaining_burst_time; }

    /**
     * @brief Get the wt object
     *
     * @return uint16_t
     */
    uint16_t get_wt() { return this->wait_time; }

    /**
     * @brief Decrease remaining_burst_time
     *
     */
    void dec_rem_bt() { --(this->remaining_burst_time); }

    /**
     * @brief Increment wait_time
     *
     */
    void inc_wt() { ++(this->wait_time); }

    /**
     * @brief Create a Task object
     *
     * @param p_list
     * @param p_id
     * @param p_at
     * @param p_bt
     * @return std::shared_ptr<Task>
     */
    static std::shared_ptr<Task> CreateTask(std::list<std::shared_ptr<Task>> &p_list, uint16_t p_id, uint16_t p_at, uint16_t p_bt)
    {
        std::shared_ptr<Task> p(new Task(p_id, p_at, p_bt));
        p_list.push_back(p);
        return p;
    }
};
#endif
