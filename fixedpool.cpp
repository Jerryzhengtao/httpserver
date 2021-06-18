#include <iostream>
#include <malloc.h>
#include "fixedpool.h"
using namespace std;


void *Fixedpool::worker(void *p)
{
    Fixedpool *pool = (Fixedpool *)p;

    while (pool != nullptr)
    {
        if (pthread_mutex_lock(&pool->lock) == 0)
        {
            while (pool->task_queue.empty())
            {
                cout << "thread" << pthread_self() << "are waiting" << endl;
                pthread_cond_wait(&pool->task_queue_cond, &pool->lock);
            }
            Task *t = nullptr;
            t = pool->task_queue.front();
            pool->task_queue.pop();
            pthread_mutex_unlock(&pool->lock);
            t->run();
        }
    }

    return (void *)0;
}

int Fixedpool::create_pool(int ps, int qs)
{
    pool_size = ps;
    task_queue_size = qs;

    pthread_mutex_init(&lock, nullptr);
    pthread_cond_init(&task_queue_cond, nullptr);

    for (int i = 0; i < qs; i++)
    {
        pthread_t tid = 0;
        if (pthread_create(&tid, nullptr, worker, (void *)this) < 0)
        {
            continue;
        }

        threads.push_back(tid);
    }
    cout << "create " << threads.size() << " threads" << endl;
    return threads.size();
}

int Fixedpool::pool_free()
{
    return 0;
}

Fixedpool::Fixedpool(int psize, int qsize)
{
    if ((psize <= 0 || psize > MAX_POOL_SIZE) || (qsize <= 0 || qsize > MAX_TASK_SUM))
    {
        cout << "size must be positive" << endl;
    }
    else
    {
        create_pool(psize, qsize);
    }
}

int Fixedpool::add_new_task(Task *t)
{
    int ret = -1;
    if (t != nullptr && pthread_mutex_lock(&lock) == 0)
    {
        if (task_queue.size() < task_queue_size)
        {
            task_queue.push(t);
            pthread_mutex_unlock(&lock);
            pthread_cond_signal(&task_queue_cond);
            ret = 0;
        }
    }
    return ret;
}
