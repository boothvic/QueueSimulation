//bank.cpp -- ATM simulation using the Queue interface
#include <iostream>
#include <cstdlib> //for rand() and srand()
#include <ctime> //for time()
#include "queue.h"

const int MIN_PRE_HR = 60;

bool newcustomer(double);

int main()
{
    using std::cin;
    using std::cout;
    using std::endl;
    using std::ios_base;
    std::srand(std::time(0)); //random initializing of rand()

    cout << "Case Study: Bank of Heather Automatic Teller\n";
    cout << "Enter maximum size of queue: ";
    int qs;
    cin >> qs;
    Queue line(qs);

    cout << "Enter the number of simulation hours: ";
    int hours;
    cin >> hours;
    long cyclelimit = MIN_PRE_HR * hours;
    
    cout << "Enter the average number of customers per hour: ";
    double perhour;
    cin >> perhour;
    double min_per_cust;
    min_per_cust = MIN_PRE_HR / perhour;

    Item temp;
    long turnaways = 0;
    long customers = 0;
    long served = 0;
    long sum_line = 0;
    int wait_time = 0;
    long line_wait = 0;

    //running the simulation
    for (int cycle = 0; cycle < cyclelimit; ++cycle){
        if (newcustomer(min_per_cust)){
            if (line.isfull())
                ++turnaways;
            else{
                ++customers;
                temp.set(cycle); //cycle = time of arrive
                line.enqueue(temp);
            }
        }

        if (wait_time <= 0 && !line.isempty()){
            line.dequeue(temp);
            wait_time = temp.ptime();
            line_wait += cycle - temp.when();
            ++served;
        }

        if (wait_time > 0)
            --wait_time;
        sum_line += line.queuecount();
    }

    //reporting results
    if (customers > 0){
        cout << "customer accepted: " << customers << endl;
        cout << " customer served: " << served << endl;
        cout << "   turnaways: " << turnaways << endl;
        cout << "average queue size: ";
        cout.precision(2);
        cout.setf(ios_base::fixed, ios_base::floatfield);
        cout << (double)sum_line / cyclelimit << endl;
        cout << " average wait time: "
            << (double)line_wait / served << " minutes\n";
    }
    else
        cout << "No customer!\n";
    cout << "Done!\n";

    return 0;
}

//x = average time, in minutes, berween customers
//return value is true if customer shows up this minute
bool newcustomer(double x)
{
    return (std::rand() * x / RAND_MAX < 1);
}
