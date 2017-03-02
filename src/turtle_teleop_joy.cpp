#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>


class TeleopTurtle {
public:
    TeleopTurtle();

private:
    void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

    ros::NodeHandle nh_;

    int linear_, angular_;
    double scale_lin_, scale_ang_;
    ros::Publisher vel_pub_;
    ros::Subscriber joy_sub_;

};


TeleopTurtle::TeleopTurtle(): linear_(1), angular_(2) {
    nh_.param("axis_linear", linear_, linear_);
    nh_.param("axis_angular", angular_, angular_);
    nh_.param("scale_angular", scale_ang_, scale_ang_);
    nh_.param("scale_linear", scale_lin_, scale_lin_);

    vel_pub_ = nh_.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1);

    joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopTurtle::joyCallback, this);
}

void TeleopTurtle::joyCallback(const sensor_msgs::Joy::ConstPtr& joy) {
    geometry_msgs::Twist twist;
    twist.angular.z = scale_ang_*joy->axes[angular_];
    twist.linear.x = scale_lin_*joy->axes[linear_];
    vel_pub_.publish(twist);
}


int main(int argc, char** argv) {
    ros::init(argc, argv, "teleop_turtle");
    TeleopTurtle teleop_turtle;

    ros::spin();
}