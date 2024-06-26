#include <Arduino.h>
#include "proj_types.h"
#include "robot.h"
#include "IRLine.h"

extern IRLine_t IRLine;

void control(robot_t& robot)
{
    robot.tis = millis() - robot.tes;

    //robot.setState(4);

    // Rules for the state evolution
    /*if(robot.state == start && robot.tof_dist > 0.10 && robot.prev_tof_dist < 0.05 && robot.tis > 3000){
      robot.rel_s = 0;
      //robot.setState(start);
    }*/if(robot.state == STOP){
      IRLine.crosses = 0;
      robot.rel_theta = 0;
      //robot.setState(fline);
      
    } else if(robot.state == FLINE && IRLine.crosses >= 1){
      IRLine.crosses = 0;
      robot.rel_theta = 0;
      robot.setState(STOP);
      
    } else if(robot.state == TLEFT && robot.rel_theta > radians (80)){
      IRLine.crosses = 0;
      robot.setState(STOP);

      
    } else if(robot.state == TRIGHT && robot.rel_theta < radians (-80)){
      IRLine.crosses = 0;
      robot.setState(STOP);  
      
      
    } else if(robot.state == PICKB && robot.tof_dist < 0.04){ 
      robot.setState(11); 
      
      
    } else if(robot.state == 11 && robot.tis > 1000){
      robot.rel_s = 0;
      robot.setState(12); 
      
      
    } else if(robot.state == 12 && robot.rel_s < -0.08){
      robot.rel_theta = 0;
      robot.setState(13); 
      
      
    } else if(robot.state == 13 && robot.rel_theta < radians(-160)){
      robot.rel_theta = 0;
      IRLine.crosses = 0;
      robot.setState(STOP); 

      
    // } else if(robot.state == 14 && IRLine.crosses >= 1){
    //   robot.rel_s = 0;
    //   robot.rel_theta = 0;
    //   robot.setState(stop); 

      
    } else if(robot.state == DROPB && robot.tis > 1000){
      robot.rel_s = 0;
      robot.rel_theta = 0;
      //robot.setState(22);
      robot.setState(21);

      
    } else if(robot.state == 21 && robot.rel_s < -0.08){
    robot.rel_theta = 0;
    robot.setState(22);

      
    } else if(robot.state == 22 && robot.rel_theta < radians(-160)){
      IRLine.crosses = 0;
      robot.rel_theta = 0;
      robot.setState(STOP);

      
    // } else if(robot.state == 23 && IRLine.crosses >= 1){
    //   IRLine.crosses = 0;
    //   robot.setState(stop);
    
      
    } else if(robot.state == LEFTLINE && robot.rel_theta > radians(70)){
      IRLine.crosses = 0;
      robot.rel_theta = 0;
      robot.setState(FLINE);
    
      
    } else if(robot.state == RIGHTLINE && robot.rel_theta < radians (-70)){
      IRLine.crosses = 0;
      robot.rel_theta = 0;
      robot.setState(FLINE);
    
 
    } else if(robot.state == START && robot.tof_dist > 0.10 && robot.prev_tof_dist < 0.05 && robot.tis > 3000){
      robot.setState(STOP);
    
 
    }
    //  if(robot.state == 0 && robot.tof_dist > 0.10 && robot.prev_tof_dist < 0.05 && robot.tis > 3000) {
    //   robot.rel_s = 0;
    //   robot.setState(1);

    // } else if (robot.state == 1 && robot.tof_dist < 0.04) {
    //   robot.setState(2);

    // } else if(robot.state == 2 && robot.tis > 400) {
    //   robot.rel_s = 0;
    //   robot.setState(3);

    // } else if(robot.state == 3 && robot.rel_s < -0.1) {
    //   robot.rel_theta = 0;
    //   robot.setState(4);

    // } else if(robot.state == 4 && robot.rel_theta > radians(170) && IRLine.total > 1500) {
    //   IRLine.crosses = 0;
    //   robot.setState(5);

    // } else if(robot.state == 5 && IRLine.crosses >= 5) {
    //   robot.rel_s = 0;
    //   robot.rel_theta = 0;
    //   robot.setState(6);

    // } else if(robot.state == 6 && robot.rel_theta < radians(-70) && IRLine.total > 1500) {
    //   robot.setState(7);

    // } else if(robot.state == 7 && robot.tis > 2000) {
    //   IRLine.crosses = 0;
    //   robot.setState(8);

    // } else if (robot.state == 202 && robot.tis > robot.T1) {
    //   robot.setState(200);

    // } else if(robot.state == 20 && robot.LastTouchSwitch && !robot.TouchSwitch) {
    //   robot.rel_s = 0;
    //   robot.setState(21);

    // } else if(robot.state == 21 && robot.TouchSwitch) {
    //   robot.setState(22);

    // } else if(robot.state == 22 && robot.TouchSwitch) {
    //   //robot.setState(1);

    // } else if(robot.state == 25) {
    //   //robot.setState(1);

    // }

    // Actions in each state
    /*if (robot.state == start){
      robot.setRobotVW(0,0);

     } else */if (robot.state == STOP){
      //robot.setRobotVW(0,0);

     } else if (robot.state == FLINE){  
       robot.rel_theta = 0;                  
       robot.followLine(IRLine);
    
     } else if (robot.state == TLEFT) {  
       //robot.rel_theta = 0;
       robot.setRobotVW(0.04, 1.5); //w was 2
       

     } else if (robot.state == TRIGHT) {  
       robot.setRobotVW(0.04, -1.5); //w was 2
       

     } else if (robot.state == PICKB) {  //follow until find box
       robot.followLine(IRLine);
       

     } else if (robot.state == 11) {  //iman on and get box
       robot.solenoid_state = 1;
       robot.followLine(IRLine);
       

     } else if (robot.state == 12) {  //go back a little
       robot.setRobotVW(-0.12, 0); //v was 0.1
       

     } else if (robot.state == 13) {  //turn 180
       robot.setRobotVW(0, -2.5); //w was 3
       

    //  } else if (robot.state == 14) {  //follow until find cross
    //    robot.followLine(IRLine);
       

     } else if (robot.state == DROPB) {  
      //  robot.followLineRight(IRLine, robot.follow_v, robot.follow_k);
       robot.followLine(IRLine);

     } else if (robot.state == 21) {  //iman off and go back
       robot.solenoid_state = 0;
       robot.setRobotVW(-0.1, 0);
       

     } else if (robot.state == 22) {  //turn 180
       robot.setRobotVW(0, -2.5); // w was 3
       

    //  } else if (robot.state == 23) {  
    //    robot.followLine(IRLine);   
       

     } else if (robot.state == LEFTLINE) {  
       robot.setRobotVW(0.02, 2); //was v = 0.02 and w = 2.5
       

     } else if (robot.state == RIGHTLINE) {  
       robot.setRobotVW(0.02, -2); //was v = 0.01 and w = 2.5
       

     }

    if (robot.state == START) {         // Robot Stoped            
      robot.solenoid_state = 0;
      robot.setRobotVW(0, 0);
    }

    // if (robot.state == 0) {         // Robot Stoped            
    //   robot.solenoid_state = 0;
    //   robot.setRobotVW(0, 0);
    // }
    
    // } else if (robot.state == 1) {  // Go: Get first box
    //   robot.solenoid_state = 0;
    //   robot.followLineLeft(IRLine, robot.follow_v, robot.follow_k);

    // } else if (robot.state == 2) { // Turn Solenoid On and Get the Box
    //   robot.solenoid_state = 1;
    //   robot.followLineLeft(IRLine, robot.follow_v, robot.follow_k);
    
    // } else if (robot.state == 3) {  // Go back with the box
    //   robot.solenoid_state = 1;
    //   robot.setRobotVW(-0.2, 0);
      
    // } else if (robot.state == 4) {  // Turn 180 degrees
    //   robot.solenoid_state = 1;
    //   robot.setRobotVW(0, 2);
      
    // } else if (robot.state == 5) {  // long travel to the box final destination
    //   robot.solenoid_state = 1;
    //   //followLineRight(80 - 40 * (IRLine.crosses >= 5), -2.0);
    //   robot.followLineRight(IRLine, robot.follow_v, robot.follow_k);
      
    // } else if (robot.state == 6) {  // Advance a little then turn to place the box
    //   robot.solenoid_state = 1;
    //   robot.setRobotVW(0.05, -2);
      
    // } else if (robot.state == 7) {  
    //   robot.solenoid_state = 1;
    //   robot.followLineRight(IRLine, robot.follow_v, robot.follow_k); 

    // } else if (robot.state == 8) { // Drop the box and go back
    //   robot.solenoid_state = 0;
    //   if (robot.tis < 2000) robot.setRobotVW(-0.1, 0);
    //   else robot.setRobotVW(0, 0);
    
    // } else if (robot.state == 20) {
    //   robot.v_req = 0;
    //   robot.w_req = 0;

    // } else if (robot.state == 21) {
    //   robot.v_req = 0.1;
    //   robot.w_req = 0;
    
    // } else if (robot.state == 22) {
    //   robot.v_req = 0.1;
    //   robot.w_req = 0;
    //   robot.solenoid_state = 1;
    
    // } else if (robot.state == 25) {
    //   robot.v_req = 0;
    //   robot.w_req = 0;
    //   robot.solenoid_state = 1;
    
    //}
    
    
      if (robot.state == 50) { //Test
      robot.setRobotVW(0.1, 0);      

    } else if (robot.state == 100) {
      robot.v_req = 0;
      robot.w_req = 0;

    } else if (robot.state == 101) {
      robot.v_req = 0;
      robot.w_req = 0;

    } else if (robot.state == 200) {
      robot.PWM_1 = 0;
      robot.PWM_2 = 0;

    } else if (robot.state == 201) {
      robot.PWM_1 = robot.PWM_1_req;
      robot.PWM_2 = robot.PWM_2_req;
    
    } else if (robot.state == 202) {
      robot.PWM_1 = robot.PWM_1_req;
      robot.PWM_2 = robot.PWM_2_req;      
    }
  
}
