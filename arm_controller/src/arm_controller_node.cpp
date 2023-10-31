#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float64.h>

void joint_statesCallback(const sensor_msgs::JointState& msg)
{
  for (int i = 0; i < 4; i++)
    ROS_INFO("Joint %d position: [%lf]", i + 1, msg.position[i]);
}

int main(int argc, char* argv[]){
  ros::init(argc, argv, "arm_controller_node");
  ros::NodeHandle nodeHandle;
  ros::Subscriber subscriber = nodeHandle.subscribe("arm/joint_states",10,joint_statesCallback);
  ros::Publisher commandPublisher1 = nodeHandle.advertise<std_msgs::Float64>("arm/PositionJointInterface_j0_controller/command", 1);
  ros::Publisher commandPublisher2 = nodeHandle.advertise<std_msgs::Float64>("arm/PositionJointInterface_j1_controller/command", 1);
  ros::Publisher commandPublisher3 = nodeHandle.advertise<std_msgs::Float64>("arm/PositionJointInterface_j2_controller/command", 1);
  ros::Publisher commandPublisher4 = nodeHandle.advertise<std_msgs::Float64>("arm/PositionJointInterface_j3_controller/command", 1);
  ros::Rate loopRate(10);
  
  std_msgs::Float64 pos_1;
  std_msgs::Float64 pos_2;
  std_msgs::Float64 pos_3;
  std_msgs::Float64 pos_4;
  pos_1.data = 0;
  pos_2.data = 1;
  pos_3.data = 1;
  pos_4.data = 1;
  while (ros::ok()) {
    commandPublisher1.publish(pos_1);
    commandPublisher2.publish(pos_2);
    commandPublisher3.publish(pos_3);
    commandPublisher4.publish(pos_4);

    ros::spinOnce();
    loopRate.sleep();
  }
  
  return 0;
}
