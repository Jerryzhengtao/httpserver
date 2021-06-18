#ifndef EVENT_H
#define EVENT_H

#include "task.h"

class event : public Task
{
private:
    int i;

public:
    event(int i);

protected:
    void run();
};

#endif