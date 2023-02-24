#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>

#define NUM_GUESTS 100
bool isCupcakeAvailable = true;
std::array<bool, NUM_GUESTS> guestsPicked;
std::mutex mutex;
int currentCount = 0;
unsigned int current_guest;

int generateRandomNumber(int min, int max);
void navigateLabyrinth(int threadIndex);
void checkCupcake();

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    std::array<std::thread, NUM_GUESTS> threads{};

    threads[0] = std::thread(checkCupcake);

    for (size_t i = 1; i < threads.size(); i++) {
        threads[i] = std::thread(navigateLabyrinth, i);
    }

    while (currentCount < NUM_GUESTS) {
        current_guest = generateRandomNumber(0, NUM_GUESTS);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    std::cout << "All " << currentCount << " guests have entered the labyrinth." << " Finished in " << duration.count() << "ms" << std::endl;
} 

void checkCupcake() {
    while (currentCount < NUM_GUESTS) {
        mutex.lock();

        if (current_guest == 0) {
            if (!isCupcakeAvailable) {
                currentCount++;
                isCupcakeAvailable = true;
            }
            
            if (isCupcakeAvailable && !guestsPicked[0]) {
                currentCount++;
                isCupcakeAvailable = true;
                guestsPicked[0] = true;
            }
        }

        mutex.unlock();
    }
}

int generateRandomNumber(int min, int max) {
    static bool first = true;
    if (first) {
        srand(time(NULL));
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}

void navigateLabyrinth(int threadIndex) {
    while (currentCount < NUM_GUESTS) {
        mutex.lock();

        if (current_guest == threadIndex && isCupcakeAvailable && !guestsPicked[threadIndex]) {
            isCupcakeAvailable = false;
            guestsPicked[threadIndex] = true;
        }

        mutex.unlock();
    }
}