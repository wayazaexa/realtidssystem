#include <iostream>
#include <vector>
#include <limits>
#include "process.hh"

int main (void)
{
    int processes;
    int quantum;
    std::vector<process> process_list;

    std::cout << "Enter number of processes: ";
    std::cin >> processes;
    std::cout << "Enter time quantum: ";
    std::cin >> quantum;
    std::cout << "Enter the arrival time and burst time of each process: \n";
    process p_tmp;
    for (int i = 0; i < processes;)
    {
        p_tmp.id = ++i;
        std::cin >> p_tmp.arrival_time;
        std::cin >> p_tmp.burst_time;
        process_list.push_back(p_tmp);
    }

    std::cout << "Data: \n";
    for (auto it = process_list.begin(); it < process_list.end(); it++)
    {
        std::cout << "p" << (*it).id << ": " << (*it).arrival_time << ", " << (*it).burst_time << "\n";
    }
    std::cout << "\n";
    
    return 0;
}