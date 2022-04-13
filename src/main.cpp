#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <cmath>

using namespace std;

float inverseQuakeSQRT(float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i =* (long *) &y;
    i = 0x5f3759df - (i >> 1);
    y = * (float *) &i;
    y = y * (threehalfs - (x2 * y * y)); //Iteration 1
    y = y * (threehalfs - (x2 * y * y)); //Iteration 2

    return y;
}

float inverseStdLibSQRT(const float &number)
{
    return 1.0F/sqrt(number);
}

pair<size_t, vector<float>> measureElapsedTime(const vector<float> &numbers, std::function<float(float)> f)
{
    vector<float> ys = {};

    auto start = std::chrono::high_resolution_clock::now();
    for(auto number: numbers)
    {
        ys.push_back(f(number));
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto time_interval = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    return make_pair(time_interval.count(), ys);
}

void show_result(const string &name, const vector<float> &numbers, std::function<float(float)> f)
{
    cout << name << endl;
    auto results = measureElapsedTime(numbers, f);
    cout << "Total elapsed time is " << results.first << " microseconds" << std::endl;
    for(size_t i=0; i<numbers.size(); i++)
    {
        std::cout << "y=1/sqrt(x) calculate for x="<< numbers[i] << " is " << results.second[i] << endl;
    }
}


int main(int, char*[])
{
    //Generate data sample.
    const vector<float> numbers = {  0.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F, 10.0F, 11.0F, 12.0F, 13.0F, 14.0F, 15.0F, 16.0F, 17.0F, 18.0F, 19.0F, 20.0F, 2022.0F,
                                     0.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F, 10.0F, 11.0F, 12.0F, 13.0F, 14.0F, 15.0F, 16.0F, 17.0F, 18.0F, 19.0F, 20.0F, 2022.0F,
                                     0.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F, 10.0F, 11.0F, 12.0F, 13.0F, 14.0F, 15.0F, 16.0F, 17.0F, 18.0F, 19.0F, 20.0F, 2022.0F,
                                     0.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F, 10.0F, 11.0F, 12.0F, 13.0F, 14.0F, 15.0F, 16.0F, 17.0F, 18.0F, 19.0F, 20.0F, 2022.0F,
                                     0.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F, 10.0F, 11.0F, 12.0F, 13.0F, 14.0F, 15.0F, 16.0F, 17.0F, 18.0F, 19.0F, 20.0F, 2022.0F,
                                     0.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F, 10.0F, 11.0F, 12.0F, 13.0F, 14.0F, 15.0F, 16.0F, 17.0F, 18.0F, 19.0F, 20.0F, 2022.0F,
                                     0.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F, 10.0F, 11.0F, 12.0F, 13.0F, 14.0F, 15.0F, 16.0F, 17.0F, 18.0F, 19.0F, 20.0F, 2022.0F,
                                     0.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F, 10.0F, 11.0F, 12.0F, 13.0F, 14.0F, 15.0F, 16.0F, 17.0F, 18.0F, 19.0F, 20.0F, 2022.0F,
                                     0.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F, 10.0F, 11.0F, 12.0F, 13.0F, 14.0F, 15.0F, 16.0F, 17.0F, 18.0F, 19.0F, 20.0F, 2022.0F
                                  };

    //Make calculations
    show_result("Using Inverse SQRT Quake III algorithm:", numbers, inverseQuakeSQRT);
    cout << endl;
    show_result("Using C++ std::sqrt():", numbers, inverseStdLibSQRT);
    
    return 0;
}