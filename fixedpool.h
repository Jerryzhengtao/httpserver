#ifndef FIXEDPOOL_H
#define FIXEDPOOL_H
#include <pthread.h>
#include <vector>
#include <queue>
#include "event.h"
#include "task.h"
using namespace std;

/**
 * fixed size thread pool
 * need a thread list 
 * need a task queue
 * create all thread while initialing threadpool
 * every thread take task from task queue
 **/
const int MAX_POOL_SIZE = 1024;
const int MAX_TASK_SUM = 1536;

class Fixedpool
{
private:
    int pool_size;
    int task_queue_size;

    pthread_mutex_t lock;
    pthread_cond_t task_queue_cond;

    int create_pool(int ps, int qs);
    int pool_free();
    static void *worker(void *pool);

public:
    vector<pthread_t> threads;
    queue<Task *> task_queue;
    Fixedpool(const int psize, const int qsize);
    int add_new_task(Task *t);
    ~Fixedpool();
};
#endif
