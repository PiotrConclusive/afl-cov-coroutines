#include <coroutine>
#include <iostream>
#include <stdexcept>
#include <thread>
 
auto switch_to_new_thread(std::jthread& out)
{
    struct awaitable
    {
        std::jthread* p_out;
        bool await_ready() { 
		std::cout << "await_ready" << std::endl;
		return false; 
	}
        void await_suspend(std::coroutine_handle<> h)
        {
	    std::cout << "await_suspend" << std::endl;
            std::jthread& out = *p_out;
            if (out.joinable())
                throw std::runtime_error("Output jthread parameter not empty");
            out = std::jthread([h] { h.resume(); });
            std::cout << "New thread ID: " << out.get_id() << '\n'; // this is OK
        }
        void await_resume() {
		std::cout << "await_resume" << std::endl;
	}
    };
    return awaitable{&out};
}
 
struct task
{
    struct promise_type
    {
        task get_return_object() { 
		std::cout << "get_return_object"  << std::endl;
		return {}; 
	}
        std::suspend_never initial_suspend() { 
		std::cout << "initial_suspend" << std::endl;
		return {}; 
	}
        std::suspend_never final_suspend() noexcept { 
		std::cout << "final_suspend" << std::endl;
		return {}; 
	}
        void return_void() {}
        void unhandled_exception() {}
    };
};
 
task resuming_on_new_thread(std::jthread& out)
{
    std::cout << "Coroutine started on thread: " << std::this_thread::get_id() << '\n';
    co_await switch_to_new_thread(out);
    std::cout << "Coroutine resumed on thread: " << std::this_thread::get_id() << '\n';
}
 
int main()
{
    std::jthread out;
    resuming_on_new_thread(out);
}
