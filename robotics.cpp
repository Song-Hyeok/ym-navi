//wall_follower_node.cpp
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"

class WallFollower
{
public:
    WallFollower()
    {
        
        ros::NodeHandle nh;
        laser_sub_ = nh.subscribe("/laser_scan", 1, &WallFollower::laserCallback, this);
        cmd_vel_pub_ = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
    }

    void laserCallback(const sensor_msgs::LaserScan::ConstPtr &msg)
    {
        
        geometry_msgs::Twist cmd_vel;
        cmd_vel.linear.x = 0.15;  
        cmd_vel.angular.z = 0.0;  

        cmd_vel_pub_.publish(cmd_vel);
    }

private:
    ros::Subscriber laser_sub_;
    ros::Publisher cmd_vel_pub_;
};

int main(int argc, char **argv)
{

    ros::init(argc, argv, "wall_follower_node");

    WallFollower wall_follower;
    ros::spin();

    return 0;
}

//CMakeLists.txt
find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  geometry_msgs
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(wall_follower_node src/wall_follower_node.cpp)
target_link_libraries(wall_follower_node ${catkin_LIBRARIES})


//build and execution
catkin_make
source devel/setup.bash
rosrun your_package_name wall_follower_node
