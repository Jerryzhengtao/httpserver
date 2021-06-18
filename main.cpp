#include <iostream>
#include <unistd.h>
#include "fixedpool.h"
#include "event.h"
using namespace std;
int main()
{

    Task *t1 = new event(1);
    Task *t2 = new event(2);
    Task *t3 = new event(3);
    Task *t4 = new event(4);
    Task *t5 = new event(5);
    Task *t6 = new event(6);
    Task *t7 = new event(7);

    Fixedpool *pool = new Fixedpool(10, 10);

    pool->add_new_task(t1);
    pool->add_new_task(t2);
    pool->add_new_task(t3);
    pool->add_new_task(t4);
    sleep(1);
    pool->add_new_task(t5);
    pool->add_new_task(t6);
    sleep(1);
    pool->add_new_task(t7);

    sleep(10);
    
}