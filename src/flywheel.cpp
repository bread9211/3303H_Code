#include "main.h"

pros::Motor flywheel(1, MOTOR_GEARSET_6, false, MOTOR_ENCODER_DEGREES);

bool flywheelToggle = false;

void move_flywheel(){
    if (master.get_digital_new_press(DIGITAL_R1)){
        flywheelToggle = !flywheelToggle;
    }

    if (flywheelToggle){
        //flywheel.move_velocity(140);
        set_flywheel_speed(2800);
    }

    else{
        //flywheel.move_velocity(0);
        set_flywheel_speed(0);
    }
}

void flywheel_auto(int speed){
    flywheel.move_velocity(speed);
}

void flywheelPID(double target){
    //Constants
    double kP = 0.6;
    double kV = 0.0354;
    double threshold = 150;

    double error = 0;
    double prevError = 0;

    double output = 0;

    while (true){
        //Proportional
        error = target - flywheel.get_actual_velocity()*6;

        //Set Speed of Flywheel
        if (error > threshold){
            output = 127;
        }

        else if (error < - threshold){
            output = 0;
        }

        else{
            output = (kV * target) + (kP * error);
        }

        flywheel.move(output);

        prevError = error;
        pros::delay(10);
    }
}


void set_flywheel_speed(int speed){
    static std::unique_ptr<pros::Task> pidTask {};
    if (pidTask != nullptr) {pidTask -> remove();}

    pidTask = (speed == -1) ? nullptr : std::make_unique<pros::Task>([=]{flywheelPID(speed);});
}
