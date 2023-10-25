/**
 * @file process.hh
 * @author Joakim Englund (joakimenglund@protonmail.com)
 * @brief Header-file for the Process-class
 * @version 0.1
 * @date 2023-10-24
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef PROCESS_HH_
#define PROCESS_HH_
#include <memory>
#include <list>

/**
 * @brief The Process class.
 *          All constructors are private to ensure they're not used.
 *          All Process-objects are instead created via another member function
 *          where I use smart pointers.
 *          And yes, I'm doing this to brush up on smart pointers, because
 *          it's been a while.
 *
 */
class Process
{
private:
    // The stored data might change once I start processing the inputs.
    uint16_t id;
    uint16_t arrival_time;
    uint16_t burst_time;
    // uint16_t wait_time;
    // uint16_t turnaround_time;

    /**
     * @brief Default constructor a new Process object (unused at the time).
     *
     */
    Process() {}

    /**
     * @brief Construct a new Process object
     *
     * @param p_id
     * @param p_at
     * @param p_bt
     */
    Process(uint16_t p_id, uint16_t p_at, uint16_t p_bt)
    {
        this->id = p_id;
        this->arrival_time = p_at;
        this->burst_time = p_bt;
    }

    /**
     * @brief Copy constructor of a Process object (unused at the time)
     *
     * @param p
     */
    Process(const Process &p)
    {
        this->id = p.id;
        this->arrival_time = p.arrival_time;
        this->burst_time = p.burst_time;
    }

public:
    /**
     * @brief Get the id object
     *
     * @return uint16_t
     */
    uint16_t get_id() { return this->id; }
    /**
     * @brief Get the at object
     *
     * @return uint16_t
     */
    uint16_t get_at() { return this->arrival_time; }
    /**
     * @brief Get the bt object
     *
     * @return uint16_t
     */
    uint16_t get_bt() { return this->burst_time; }

    /**
     * @brief Create a Process object
     *
     * @param p_list
     * @param p_id
     * @param p_at
     * @param p_bt
     * @return std::shared_ptr<Process>
     */
    static std::shared_ptr<Process> CreateProcess(std::list<std::shared_ptr<Process>> &p_list, uint16_t p_id, uint16_t p_at, uint16_t p_bt)
    {
        std::shared_ptr<Process> p(new Process(p_id, p_at, p_bt));
        p_list.push_back(p);
        return p;
    }
};
#endif
