
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <vector>
#include <mutex>
#include <cstdlib>

//This minimum compiler version to compile this solution is c++20

using std::cout;
using std::endl;

const size_t CPUThreadNum = std::thread::hardware_concurrency(); // The device's maximum thread capacity
std::mutex mtx;

class ExpensiveObject {
public:
    ExpensiveObject() = default;

    void doSomething() {
        std::unique_lock<std::mutex> lock(mtx);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        cout << "ExpensiveObject is doing something" << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        lock.unlock();
    }
    ~ExpensiveObject() = default;
};

class LazyInitialization {
private:
    ExpensiveObject* object = nullptr;
    std::once_flag flag; // std::once_flag to ensure initialization happens only once
    std::atomic<bool> ready{ false }; // Atomic flag to indicate whether the object is initialized

    void initializeObject() {
        if (!object) {
            object = new ExpensiveObject(); // Initialize the object
            ready.store(true, std::memory_order_release); // Mark object as ready
        }
    }

public:
    void useObject() {
        std::call_once(flag, &LazyInitialization::initializeObject, this); // Call initializeObject() once
        while (!ready.load(std::memory_order_acquire)) {} // Wait until object is initialized with acquire semantics
        object->doSomething(); // Use the object
    }

    ~LazyInitialization() {
        delete object;
    }
};

int main() {
    LazyInitialization test1;
    std::vector<std::jthread> vec;
    //creating a vector of thread based on the device capacity minus 1
    for (size_t i = 1; i < CPUThreadNum; i++) {

        vec.emplace_back([&test1]() {test1.useObject(); });
    }
    //jthread object is auto joinable but for double safty implementing join function
    for (auto& v : vec) {
        v.join();
    }
    // Simulate multiple threads trying to use the object simultaneously
    std::jthread t1([&test1]() {
        test1.useObject();
        });
    std::jthread t2([&test1]() {
        test1.useObject();
        });

    t1.join();
    t2.join();

    cout << "\nThe maximum thread capacity on this devise is: " << CPUThreadNum << endl;
    std::system("pause");
    return 0;
}