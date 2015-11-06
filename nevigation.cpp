// 2015.8.26

#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <kobuki_dock_drive/dock_drive.hpp>
#include <tf/transform_listener.h>
#include "kobuki_auto_docking/auto_docking_ros.hpp"



typedef actionlib::SimpleActionClient<kobuki_msgs::AutoDockingAction> AutoDockingClient;
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;



void doneCb(const actionlib::SimpleClientGoalState& status,
            const kobuki_msgs::AutoDockingResultConstPtr& result)
{

	ROS_INFO("Finished in state [%s]", status.toString().c_str());
	ROS_INFO("Answer: %s", result->text.c_str());
	//ros::shutdown();
}



void activeCb()
{
	ROS_INFO("Action server went active.");
}



void feedbackCb(const kobuki_msgs::AutoDockingFeedbackConstPtr& feedback)
{
	ROS_INFO("Feedback: [DockDrive: %s]: %s",feedback->state.c_str(),feedback->text.c_str());
}



int main(int argc, char** argv)
{
	ros::init(argc, argv, "auto_dock_test");
	//tell the action client that we want to spin a thread by default
	MoveBaseClient ac("move_base", true);													//用类定义一个对象
	AutoDockingClient bc("dock_drive_action",true);

	//wait for the action server to come up
	while(!ac.waitForServer(ros::Duration(2.0)))
	{
		ROS_INFO("Waiting for the move_base action server to come up");
  } 

	move_base_msgs::MoveBaseGoal goal;
	kobuki_msgs::AutoDockingGoal goala; // define a message is different from python

	//we'll send a goal to the robot to move 1 meter forward
  goal.target_pose.header.frame_id = "map";											//目标姿态，头属性，坐标系的ID
  goal.target_pose.header.stamp = ros::Time::now();							//时间戳

	//702的点
	goal.target_pose.pose.position.x = -2.130;   									//7.264
	goal.target_pose.pose.position.y = 0.395;										//3.372  门外点
	goal.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw( -0.137);
	ROS_INFO("Sending goal one");
	ac.sendGoal(goal);
	ac.waitForResult();

while(1)
{ 


	//第一个点
	
  do
  {
	  goal.target_pose.pose.position.x = 8.397;   									//7.264
	  goal.target_pose.pose.position.y = -1.296;											//3.372  门外点
	  goal.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw( 0.184);
    ROS_INFO("Sending goal 1 ");
	  ac.sendGoal(goal);
	  ac.waitForResult();
  }while(ac.getState() != actionlib::SimpleClientGoalState::SUCCEEDED);
  
  
    //自动充电三秒
  
  do
{
	
	bc.sendGoal(goala, doneCb, activeCb, feedbackCb);
	bc.waitForResult();
	ros::Duration(3.0).sleep();
	ROS_INFO("docking ");
}while(ac.getState() != actionlib::SimpleClientGoalState::SUCCEEDED);


//弹出
	ros::NodeHandle nh;
	ros::Publisher velocity_command_publisher = nh.advertise< geometry_msgs::Twist >("/mobile_base/commands/velocity", 10);
	ros::Rate loop_rate(10);
	ROS_INFO("backward beginning");
	for(int j=0;j<62;j++)
	{
		geometry_msgs::Twist backward_vel;
		backward_vel.linear.x = -0.1;
		backward_vel.linear.y = 0.0;
		backward_vel.linear.z = 0.0;
		backward_vel.angular.x = 0.0;
		backward_vel.angular.y = 0.0;
		backward_vel.angular.z = 0.0;
		ROS_INFO("backward");
		velocity_command_publisher.publish(backward_vel);
		ros::spinOnce();
		loop_rate.sleep();
	}
	ROS_INFO("backward over");
  
  
  
   	//第tow个点
	
  do
  {
	  goal.target_pose.pose.position.x = 12.592;   									//7.264
	  goal.target_pose.pose.position.y = -1.235;											//3.372  门外点
	  goal.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(-0.084);
    ROS_INFO("Sending goal 2 ");
	  ac.sendGoal(goal);
	  ac.waitForResult();
  }while(ac.getState() != actionlib::SimpleClientGoalState::SUCCEEDED);
  
  
  	//第three个点
	
  do
  {
	  goal.target_pose.pose.position.x =16.032;   									//7.264
	  goal.target_pose.pose.position.y = -1.211;											//3.372  门外点
	  goal.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(-0.032);
    ROS_INFO("Sending goal 3 ");
	  ac.sendGoal(goal);
	  ac.waitForResult();
  }while(ac.getState() != actionlib::SimpleClientGoalState::SUCCEEDED);
  

  
   //第4个点
	
  do
  {
	  goal.target_pose.pose.position.x =20.008;   									//7.264
	  goal.target_pose.pose.position.y = -1.810;											//3.372  门外点
	  goal.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(0.672);
    ROS_INFO("Sending goal 4 ");
	  ac.sendGoal(goal);
	  ac.waitForResult();
  }while(ac.getState() != actionlib::SimpleClientGoalState::SUCCEEDED);

 
 	//第 5 个点
	
  do
  {
	  goal.target_pose.pose.position.x = 21.584;   									//7.264
	  goal.target_pose.pose.position.y = 0.492;											//3.372  门外点
	  goal.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(-1.687);
    ROS_INFO("Sending goal 5 ");
	  ac.sendGoal(goal);
	  ac.waitForResult();
  }while(ac.getState() != actionlib::SimpleClientGoalState::SUCCEEDED);
  
 

}

	return 0;
}

