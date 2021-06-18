#include "event.h"
#include <iostream>
#include <unistd.h>
using namespace std;
event::event(int a)
{
    i = a;
}
void event::run()
{
    for (int j = 0; j < 15; j++)
    {
        sleep(0.5);
        cout << pthread_self() << " are running task  " << i << "  " << j << endl;
    }
}