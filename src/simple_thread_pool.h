#pragma once

#include <thread>
#include <vector>
#include <condition_variable>
#include <mutex>
#include <deque>

class SimpleThreadPool {
public:
    SimpleThreadPool(size_t nthreads);
    ~SimpleThreadPool();

    bool AddTask(const std::function<bool()>& task);

private:
    std::vector<std::thread>            _workers;
    std::deque<std::function<void()> >  _tasks;

    std::mutex                          _queue_mutex;
    std::condition_variable             _condition;
    bool                                _stop;
};

SimpleThreadPool::SimpleThreadPool(size_t nthreads)
    : _stop(false) {
    for(size_t i = 0; i < nthreads; ++i) {
        _workers.emplace_back(
                [this] {
                    for (;;) {
                        std::function<void()> task;

                        {
                            std::unique_lock<std::mutex> lock(_queue_mutex);
                            _condition.wait(lock,
                                    [this] { return _stop || !this->_tasks.empty(); });
                            if (_stop && _tasks.empty()) {
                                return;
                            }
                            task = std::move(_tasks.front());
                            _tasks.pop_front();
                        }

                        task();
                    }
                }
        );
    }
}

SimpleThreadPool::~SimpleThreadPool() {
    {
        std::unique_lock<std::mutex> lock(_queue_mutex);
        _stop = true;
    }
    _condition.notify_all();
    for(std::thread &worker: _workers)
        worker.join();
}

bool SimpleThreadPool::AddTask(const std::function<bool()>& task) {
    std::unique_lock<std::mutex> lock(_queue_mutex);

    if (_stop) return false;

    _tasks.emplace_back(task);

    _condition.notify_one();
    return true;
}