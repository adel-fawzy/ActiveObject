#ifndef _ACTIVE_OBJECT_HPP_
#define _ACTIVE_OBJECT_HPP_

#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>
#include <thread>
#include <atomic>

/*******************************************************************************************************************************************
 **************************************************************** EVENT QUEUE **************************************************************
 ******************************************************************************************************************************************/

class EventQueue final
{
public:
        /*******************************************************************************************************************************************
         ************************************************************** CONSTRUCTOR(S) *************************************************************
         ******************************************************************************************************************************************/
        EventQueue() = default;

        /*******************************************************************************************************************************************
         *************************************************************** DESTRUCTOR ****************************************************************
         ******************************************************************************************************************************************/
        ~EventQueue() = default;

        /*******************************************************************************************************************************************
         **************************************************************** REQUEST(S) ***************************************************************
         ******************************************************************************************************************************************/
        
        /*
         * DESCRIPTION: Pushes events to the queue
         */
        void pushEvent(std::function<void()> newEvent)
        {
                std::lock_guard<std::mutex> lock(_mutex); // Wait for access to the queue
                _queue.push(newEvent);
                _condition.notify_one();
        }

        /*
         * DESCRIPTION: Pops the first event in the queue and returns it
         */
        std::function<void()> popEvent()
        {
                std::unique_lock<std::mutex> lock(_mutex);
                if(_queue.empty())
                {
                        // Sleep until another thread notifies that a new event is pushed
                        _condition.wait(lock, [this]{ return !_queue.empty(); });
                }

                // Return the first event in the queue and pop it
                std::function<void()> event = std::move(_queue.front());
                _queue.pop();
                return event;
        }

private:
        /*******************************************************************************************************************************************
         ********************************************************* PRIVATE DATA MEMBER(S) **********************************************************
         ******************************************************************************************************************************************/

        /* 
         * DESCRIPTION: Queue container that holds events of type 'T'
         */
        std::queue<std::function<void()>> _queue;

        /* 
         * DESCRIPTION: Protects '_queue'
         */
        std::mutex _mutex;

        /*
         * DESCRIPTION: The function 'pushEvent' uses this condition variable whenever it pushes a new event onto '_queue' in order to notify the function
         * 'popEvent' that a new event has been pushed.
         */
        std::condition_variable _condition;
};

/*******************************************************************************************************************************************
 *************************************************************** ACTIVE OBJECT *************************************************************
 ******************************************************************************************************************************************/

class ActiveObject
{
    /*******************************************************************************************************************************************
     ************************************************************** CONSTRUCTOR(S) *************************************************************
     ******************************************************************************************************************************************/

public:

    ActiveObject() :
		_thread(&ActiveObject::run, this),
		_stop(false) {}

    /*******************************************************************************************************************************************
     *************************************************************** DESTRUCTOR ****************************************************************
     ******************************************************************************************************************************************/

public:

	virtual ~ActiveObject()
	{
		addEvent<bool>([this]() -> bool {
			_stop.store(true);
			return _stop.load();
		});
		_thread.join();
	}

	/********************************************************************************************************************************************
         *********************************************************** DELETED OPERATION(S) ***********************************************************
         *******************************************************************************************************************************************/

public:

	ActiveObject(ActiveObject const& obj) = delete; // Delete copy constructor
	ActiveObject(ActiveObject const&& obj) = delete; // Delete move constructor
	ActiveObject& operator=(ActiveObject& obj) = delete; // Delete copy assignment operator
	ActiveObject& operator=(ActiveObject&& obj) = delete; // Delete move assignment operator

	/********************************************************************************************************************************************
         ****************************************************** PROTECTED MEMBER FUNCTIONS(S) *******************************************************
         *******************************************************************************************************************************************/

protected:

        /*
	 * DESCRIPTION: Adds an event to the event loop and then waits for that particular event to be handled and then return its response. Note
         * that this function is a blocking function.
	 */
	template<typename T>
	T addEvent(std::function<T()> eventHandler)
	{
		std::promise<T> promise;
		std::future<T> future_response = promise.get_future();
		_queue.pushEvent([&promise, &eventHandler](){
			promise.set_value(eventHandler());
		});
		return future_response.get();
	}

        /*
	 * DESCRIPTION: Adds an event to the event loop.
	 */
	template<typename T>
	void addEvent(std::function<T()> eventHandler, std::function<void(T)> callback)
	{
		_queue.pushEvent([=](){
			callback(eventHandler());
		});
	}

	/********************************************************************************************************************************************
         ******************************************************* PRIVATE MEMBER FUNCTIONS(S) ********************************************************
         *******************************************************************************************************************************************/

private:

        /*
	 * DESCRIPTION: Event loop.
	 */
	void run()
	{
                while(!_stop.load())
                {
                        _queue.popEvent()(); // Pop the event and execute it
                }
	}

	/*******************************************************************************************************************************************
         ********************************************************* PRIVATE DATA MEMBER(S) **********************************************************
         ******************************************************************************************************************************************/

private:

	/*
	 * DESCRIPTION: Manages the event loop thread.
	 */
	std::thread _thread;
	
	/*
	 * DESCRIPTION: Holds the events of the event loop.
	 */
	EventQueue _queue;
	
	/*
	 * DESCRIPTION: TRUE by default. Set to FALSE so that the event loop exits.
	 */
	std::atomic<bool> _stop;
};

#endif