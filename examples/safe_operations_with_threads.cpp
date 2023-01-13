#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>

using namespace std;

constexpr int N_INTERATIONS = 10;

mutex _mutex;
int sharedVariable = 0;


template<typename... Args>
void safeOperation(void (*func)(Args...), Args... args){
    _mutex.lock();
    (*func)(args...);
    _mutex.unlock();
}


void write(){
    sharedVariable += 1;
}
#define write() safeOperation(write);


void read(){
    if (sharedVariable == 5){
        usleep(10);
        cout << "2 * 5 = " << 2 * sharedVariable << endl;
    }
}
#define read() safeOperation(read);



void someWriteTask(){
    for(int i = 0; i < N_INTERATIONS; i++){
        write();
        usleep(1);
    }
}


void someReadTask(){
    for(int i = 0; i < N_INTERATIONS; i++){
        read();
        usleep(1);
    }
}


int main(){
    thread readThread(someReadTask), writeThread(someWriteTask);

    writeThread.join();
    readThread.join();

    return 0;
}
