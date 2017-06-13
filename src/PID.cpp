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

    d_Kp = 0.004;
    d_Kd = 0.01;

    best_error = 0;

    i_Kp = 0;
    i_Kd = 0;

    best_error = 1e06;
    max_lap = 16;
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

    std::cout << "i_Kp, i_Kd" << i_Kp << "," << i_Kd << std::endl;
    std::cout << "Kp, Kd" << Kp << "," << Kd << std::endl;

    if (i_error < best_error){
        std::cout << "---- new record! ---" << i_error << std::endl;
        best_error = i_error;
        best_Kp = Kp;
        best_Kd = Kd;
        std::cout << " best Kp, Kd" << Kp << "," << Kd << std::endl;
    }

    i_Kd += 1;
    if (i_Kd ==max_lap + 1){
        i_Kd = 0;
        i_Kp += 1;
        Kp += d_Kp;
        Kd -= max_lap*d_Kd;
    }else{
        Kd += d_Kd;
    }

    if (i_Kp == 3){
        std::cout << "----done!----" << std::endl;
        std::cout << "---- best record! ---" << best_error << std::endl;
        std::cout << " best Kp, Kd" << best_Kp << "," << best_Kd << std::endl;
        exit(0);
    }

    // reset errors
    d_error = 0;
    i_error = 0;
    p_error = 0;

    // reset step
    step = 0;

}

