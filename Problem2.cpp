#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>

const int MAX_GUESTS = 10; 

std::mutex mtx; 
int num_viewed = 0; 
std::random_device rd;
std::mt19937 gen(rd());

int view_vase(int  delay, int guest_id){
    std::cout << "Guest " << guest_id << " is viewing the vase." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    num_viewed++;
    return num_viewed;
}
void enter_showroom(int guest_id) {
    std::uniform_int_distribution<> dis(500, 2000); // random delay between 500ms and 2000ms

    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "Guest " << guest_id << " is waiting to enter the showroom..." << std::endl;
    while (true) {
        if (std::cout.rdbuf()->in_avail() == 0 && num_viewed < MAX_GUESTS) {
            std::cout << "Guest " << guest_id << " is entering the showroom." << std::endl;
            break;
        }
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(dis(gen)));
        lock.lock();
    }

    view_vase(dis(gen), guest_id);
    std::cout << "Guest " << guest_id << " is leaving the showroom." << std::endl;
    std::cout << std::endl;
    std::cout.clear(); 
}

void set_showroom_status() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1000, 5000); 
    while (num_viewed < MAX_GUESTS) {
        mtx.lock();
        std::cout << "The showroom is now available." << std::endl;
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(dis(gen)));
        std::cout.clear(); 

        mtx.lock();
        std::cout << "The showroom is now busy." << std::endl;
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(dis(gen)));
        std::cout.clear(); 
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    std::thread t1(set_showroom_status);

    std::thread guests[MAX_GUESTS];
    for (int i = 0; i < MAX_GUESTS; i++) {
        guests[i] = std::thread(enter_showroom, i);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    for (int i = 0; i < MAX_GUESTS; i++) {
        guests[i].join();
    }
    t1.join();
    return 0;
}
