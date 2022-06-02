#ifndef sema_hh
#define sema_hh
#include <mutex>
#include <condition_variable>
using namespace std;
 
class Semaphore
{
public:
    Semaphore(long count = 0) : count(count) {}
    //V操作，唤醒
    void signal()
    {
        unique_lock<mutex> unique(mt);
        ++count;
        if (count <= 0)
            cond.notify_one();
    }
    //P操作，阻塞
    void wait()
    {
        unique_lock<mutex> unique(mt);
        --count;
        if (count < 0)
            cond.wait(unique);
    }
    
private:
    mutex mt;
    condition_variable cond;
    long count;
};
#endif