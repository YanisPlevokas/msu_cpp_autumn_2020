#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>

class ThreadPool
{
public:
	using Task = std::function<void ()>;

    explicit ThreadPool(size_t poolSize): poolSize(poolSize), alive(true)
    {
        for (size_t i = 0; i < poolSize; i++)
        {
            threads_.emplace_back([this]()
            {
                while (true)
                {
                    std::unique_lock<std::mutex> lock(mutex_variable);
                    if (!queue_.empty())
                    {
                        auto problem = std::move(queue_.front());
                        queue_.pop();
                        lock.unlock();
                        problem();
                    }
                    else
                    {
                        if (alive)
                        	working.wait(lock);
                        else
                        	return;
                    }
                }
            }
            );
        }
    }

	~ThreadPool()
    {
        alive = false;
        working.notify_all();
        for(size_t i = 0; i < poolSize; i++)
        {
            threads_[i].join();
        }
    }

   
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>
    {
        auto problem = std::make_shared<std::packaged_task<decltype(func(args...))()>> (std::bind(func, args...));
        auto ff = [problem](){ (*problem)();};
        {
            std::unique_lock<std::mutex> lock(mutex_variable);
            queue_.emplace(ff);
        }
        working.notify_one();
        return problem->get_future();
    }
private:
    size_t poolSize;
    std::condition_variable working;
    std::queue<Task> queue_;
    std::vector<std::thread> threads_;
    std::mutex mutex_variable;
    std::atomic<bool> alive;
};