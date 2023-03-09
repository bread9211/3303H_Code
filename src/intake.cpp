#include "main.h"

pros::Motor conveyor(3,MOTOR_GEARSET_6, true, MOTOR_ENCODER_DEGREES);
pros::ADIDigitalOut indexer ('H');
pros::ADIDigitalOut expansion('A');

bool move_intake = false;

bool toggle = false;

void set_conveyor(bool up){
  conveyor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  if (up == true){
    conveyor.move_velocity(600);
  }
  else{
    conveyor.move_velocity(0);
  }
}

void toggle_Intake(){
  if (master.get_digital_new_press(DIGITAL_L1)){
    move_intake = !move_intake;
  }

  else if (master.get_digital(DIGITAL_L2)){
    conveyor.move_velocity(-600);
  }

  if (move_intake){
    conveyor.move_velocity(600);
    //expansion.set_value(true);
  }
  else{
    conveyor.move_velocity(0);
  }
}

void set_indexer(bool toggle){
  if (toggle){
    indexer.set_value(true);
  }
  else{
    indexer.set_value(false);
  }
}

void toggle_index(){
  if (master.get_digital(DIGITAL_R2)){
    set_indexer(false);
    conveyor.move_velocity(600);
  }
  else{
    set_indexer(true);
  }
}

void conveyoropposite(){
  if (master.get_digital(DIGITAL_L2)){
    // set_conveyor(true);
    conveyor.move_velocity(-600);
  }
  else{
    set_conveyor(false);
  }
}

void index(){
  set_conveyor(true);
  pros::delay(350);
  set_indexer(false);
  pros::delay(250);
  set_indexer(true);
  set_conveyor(false);
}

void IndexAuton(bool up){
  if (up == true){
    set_indexer(true);
  }
  else{
    set_indexer(false);
  }
}

void tglexpansion(){
    if (master.get_digital_new_press(DIGITAL_DOWN)){
        toggle = !toggle;
    }

    if (toggle){
        expansion.set_value(true);
    }
    else{
        expansion.set_value(false);
    }
}