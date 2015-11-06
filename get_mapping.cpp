 1 先安装hector_slam：  sudo apt-get install ros-indigo-hector-slam 

 2 修改包hector_mapping中的mapping_default.launch文件（路径：/opt/ros/indigo/share/hector_mapping/launch或roscd进入）：     <arg name="odom_frame" default="nav"/>


 3 在工作空间中的包tars_slam中的tars_hector_mapping.launch写为：
<launch>

  <include file="$(find turtlebot_bringup)/launch/minimal.launch" />
  <include file="$(find rplidar_ros)/launch/rplidar.launch" />
  <node pkg="tf" type="static_transform_publisher" name="base_link_to_laser" args="0 0 0 0 0 0 base_link laser 100" />
  <include file="$(find turtlebot_teleop)/launch/logitech.launch" />

  <arg name="geotiff_map_file_path" default="$(find hector_geotiff)/maps"/>
  <include file="$(find hector_mapping)/launch/mapping_default.launch"/>
  <include file="$(find hector_geotiff)/launch/geotiff_mapper.launch">
    <arg name="trajectory_source_frame_name" value="scanmatcher_frame"/>
    <arg name="map_file_path" value="$(arg geotiff_map_file_path)"/>
  </include>
  <node pkg="rviz" type="rviz" name="rviz" 
    args="-d $(find hector_slam_launch)/rviz_cfg/mapping_demo.rviz"/>
</launch>


 4 运行：roslaunch tars_slam tars_hector_mapping.launch


 5 存图：rosrun map_server map_saver
