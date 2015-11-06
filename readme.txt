(1)alter speed of kuboki:

 roscd ~/turtlebot/src/turtlebot/turtlebot_bringup/param/defaults

 vim smoother.yaml  : amend   speed_lim_v: 0.5


(2)ssh ubuntu@192.168.1.4    (ip of tk1 is 192.168.1.4)

(3)scp -r ~/catkin_ws ubuntu@192.168.1.4:~/g_ws

(4)modify kobuki's redius and inflantion  :
 
   cd ~/catkin_ws/src/tars_slam/param
     
   vim costmap_common_params.yaml   alter robot_radius: 0.18  and   inflation_radius:  0.08
 
(5) amend coordinate of beginning in kobuki:
 
   cd ~/catkin_ws/src/tars_slam/launch/includes
   
   vim amcl.launch.xml        alter:       <param name="initial_pose_x"            value="-2.575"/>
                                           <param name="initial_pose_y"            value="2.238"/>
                                           <param name="initial_pose_a"            value="-1.615"/> 
                                           
 
(6) start navigation of kuboki :
   
    step1:  nevigation.launch
    step2:  nevigation.cpp
    step3:  rosrun rviz rviz   
     
   

  
 
 
 
 
 
 
 
 
 
 
 
