#ifndef TASK_H
#define TASK_H

class Task
{
    friend class Fixedpool;
public:
     ~Task();

protected:
    virtual void run() = 0;
};

#endif