#ifndef CORE_CONCURRENCY_QUEUE_H
#define CORE_CONCURRENCY_QUEUE_H

#include <mutex>
#include <condition_variable>
#include <queue>


namespace Core
{
	template <typename T>
	class ConcurrencyQueue
	{
	public:
        void push(T&& item) {
            {
                std::lock_guard<std::mutex> lock(_mutex);
                _queue.push(item);
            }

            _notifyer.notify_one();
        }

        T& front() {
            std::unique_lock<std::mutex> lock(_mutex);
            _notifyer.wait(lock, [&] { return !_queue.empty(); });
            return _queue.front();
        }

        void pop() {
            std::lock_guard<std::mutex> lock(_mutex);
            _queue.pop();
        }

	private:
		std::mutex _mutex;
		std::condition_variable _notifyer;
		std::queue<T> _queue;
	};

}
#endif
