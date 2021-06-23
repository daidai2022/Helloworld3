// Helloworld3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <syncstream>
#include <queue>
#include <chrono>

constexpr unsigned int N = 20;

void sub1(int num) {
    {
        using namespace std;
        osyncstream Cout{ std::cout };
        Cout << "sub1: ";
        for (int i = 0; i < num; i++)
            Cout << (i ? ',' : '[') << i;
        Cout << "]\n";
    }
}

void sub2(int num) {
    {
        using namespace std;
        ostream& Cout{std::cout};
        Cout << "sub2: ";
        for (int i = 0; i < num; i++)
            Cout << (i ? ',' : '[') << i;
        Cout << "]\n";
    }
}

std::mutex mutex_;
void sub3(int num) {
    {
        using namespace std;    
        lock_guard<mutex> lock(mutex_);
        ostream& Cout{ std::cout };
        Cout << "sub3: ";
        for (int i = 0; i < num; i++)
            Cout << (i ? ',' : '[') << i;
        Cout << "]\n";
    }
}

void sub4(int num) {
    {
        using namespace std;
        osyncstream Cout{ std::cout };
        osyncstream Cout2{ std::cout };
        Cout << "sub4-1: ";
        for (int i = 0; i < num; i++)
            Cout << (i ? ',' : '[') << i;
        Cout << "]\n";

        Cout2 << "sub4-2: ";
        for (int i = 0; i < num; i++) 
            Cout2 << (i ? ',' : '[') << i;
        Cout2 << "]\n";

    }
}

void sub5(int num) {
    {
        using namespace std;
        osyncstream Cout{ std::cout };
        osyncstream Cout2{ std::cout };
        Cout << "sub5-1: ";
        for (int i = 0; i < num; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            Cout << (i ? ',' : '[') << i;
        }
        Cout << "]\n";

        Cout2 << "sub5-2: ";
        for (int i = 0; i < num; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            Cout2 << (i ? ',' : '[') << i;
        }
        Cout2 << "]\n";

    }
}

void sub6_1(int num) {
    {
        using namespace std;
        osyncstream Cout{ std::cout };
        Cout << "sub6-1: ";
        for (int i = 0; i < num; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            Cout << (i ? ',' : '[') << i;
        }
        Cout << "]\n";
    }
}

void sub6_2(int num) {
    {
        using namespace std;
        osyncstream Cout{ std::cout };
        Cout << "sub6-2: ";
        for (int i = 0; i < num; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            Cout << (i ? ',' : '[') << i;
        }
        Cout << "]\n";
    }
}

void sub7_1(int num) {
    {
        using namespace std;
        osyncstream Cout{ std::cout };
        Cout << "sub7-1: ";
        for (int i = 0; i < num; i++) {
            std::this_thread::sleep_for(std::chrono::microseconds(500));
            Cout << (i ? ',' : '[') << i;
        }
        Cout << "]\n";
    }
}

void sub7_2(int num) {
    {
        using namespace std;
        osyncstream Cout{ std::cout };
        Cout << "sub7-2: ";
        for (int i = 0; i < num; i++) {
            std::this_thread::sleep_for(std::chrono::microseconds(1000));
            Cout << (i ? ',' : '[') << i;
        }
        Cout << "]\n";
    }
}


void exec(std::queue<std::thread>&& a) {
    for (; !a.empty(); a.pop()) {
        a.front().join();
    }
}

int main() {
    {
        using namespace std;
        //priority_queue<thread> aaaaa;
        queue<thread> a;
        for (int i = 1; i < N; i++) {
            auto r1 = thread(sub1, i);
            a.push(move(r1));
        }
        {
            exec(move(a));
            //for (; !a.empty(); a.pop()) {
            //    a.front().join();
            //}
        }
        for (int i = 1; i < N; i++) {
            auto r2 = thread(sub2, i);
            a.push(move(r2));
        }
        {
            exec(move(a));
        }
        for (int i = 1; i < N; i++) {
            auto r3 = thread(sub3, i);
            a.push(move(r3));
        }
        {
            exec(move(a));
        }
        for (int i = 1; i < N/2; i++) {
            auto r4 = thread(sub4, i);
            a.push(move(r4));
        }
        {
            exec(move(a));
        }
        for (int i = 1; i < N / 2; i++) {
            auto r5 = thread(sub5, i);
            a.push(move(r5));
        }
        {
            exec(move(a));
        }
        for (int i = 1; i < N / 2; i++) {
            auto r61 = thread(sub6_1, i);
            a.push(move(r61));
            auto r62 = thread(sub6_2, i);
            a.push(move(r62));
        }
        {
            exec(move(a));
        }
        for (int i = 1; i < N / 2; i++) {
            auto r71 = thread(sub7_1, i);
            a.push(move(r71));
            auto r72 = thread(sub7_2, i);
            a.push(move(r72));
        }
        {
            exec(move(a));
        }
        //auto r2 = thread(sub1, 11);
        //auto r3 = thread(sub1, 12);
        //r1.join();
        //r2.join();
        //r3.join();
        {              
            //a.push(move(r2));
            //a.push(move(r3));
            for (; !a.empty(); a.pop()) {
                //a.back().join();
                a.front().join();    
            }

        }
        //vector<decltype(r1)> b;
        //b.push_back(move(r1));
        
    }
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
