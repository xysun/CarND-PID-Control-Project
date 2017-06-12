#include "PID.h"
#include <iostream>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;

    p_error = 0;
    i_error = 0;
    d_error = 0;

    this->MAX_STEP = 4000;
    this->step = 0;

    d_Kp = 0.005;

    best_error = 0;
    is_first_run = true;
    is_down = false;
}

void PID::UpdateError(double cte) {
    d_error = cte - p_error;
    p_error = cte;
    i_error += cte;
}

double PID::TotalError() {
    return Kp*p_error + Ki*i_error + Kd*d_error;
}

void PID::reset(){

    std::cout << "original Kp: "<<Kp<<std::endl;

    if (is_first_run){
        best_error = i_error;
        best_Kp = Kp;
        Kp += d_Kp;
        is_first_run = false;
    }else{
        if (i_error < best_error){
            std::cout << "reduced error! from " << best_error << "to: " << i_error << std::endl;
            best_error = i_error;
            best_Kp = Kp;
            d_Kp *= 1.1;
            Kp += d_Kp;
            is_down = false;
        }
        else{
            if (is_down){
                Kp += d_Kp;
                d_Kp *= 0.9;
                is_down = false;
            }
            else{
                Kp -= 2 * d_Kp;
                is_down = true;
            }
        }
    }
    std::cout << " best error: " << best_error << " best Kp " << best_Kp << std::endl;
    std::cout <<"new Kp:"<<Kp<<" new d_Kp: "<<d_Kp << std::endl;

    // reset errors
    d_error = 0;
    i_error = 0;
    p_error = 0;

    // reset step
    step = 0;

}

