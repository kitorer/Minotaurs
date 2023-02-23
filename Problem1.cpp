#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <vector>
#include <algorithm>

std::mutex mtx;
std::condition_variable cv;
int num_guests;
int num_entered = 0;
int num_left = 0;
std::vector<int> guests;

//random number generator
int random(int min, int max) {
    static bool first = true;
    if (first) {
        srand(time(NULL));
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}

void enter_labyrinth(int id) {
    std::unique_lock<std::mutex> lock(mtx);
    while (num_left > 0) {
        cv.wait(lock);
    }
    if (std::find(guests.begin(), guests.end(), id) == guests.end()) {
        guests.push_back(id);
    }
    num_entered++;
    if (num_entered == num_guests) {
        num_entered = 0;
        num_left = num_guests;
        cv.notify_all();
    }
}

void leave_labyrinth(int id) {
    std::unique_lock<std::mutex> lock(mtx);
    num_left--;
    if (num_left == 0) {
        cv.notify_all();
    }
}

int main() {
    std::cout << "Enter the number of guests: ";
    std::cin >> num_guests;

    std::vector<std::thread> threads;
    for (int i = 0; i < num_guests; i++) {
        threads.push_back(std::thread([i] {
            enter_labyrinth(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            leave_labyrinth(i);
        }));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "All guests have visited the labyrinth at least once!" << std::endl;

    return 0;
}