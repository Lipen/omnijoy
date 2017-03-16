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
    double scale_left_, scale_right_, scale_cross_;
    ros::Publisher vel_pub_;
    ros::Subscriber joy_sub_;
};


TeleopTurtle::TeleopTurtle(): scale_left_(1), scale_right_(1), scale_cross_(1) {
    // nh_.param("axis_linear", linear_, linear_);
    // nh_.param("axis_angular", angular_, angular_);
    nh_.param("scale_left", scale_left_, scale_left_);
    nh_.param("scale_right", scale_right_, scale_right_);

    vel_pub_ = nh_.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1);

    joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopTurtle::joyCallback, this);
}

void TeleopTurtle::joyCallback(const sensor_msgs::Joy::ConstPtr& joy) {
    float js_left_x = joy->axes[0];
    float js_left_y = joy->axes[1];
    float js_right_x = joy->axes[2];
    float js_right_y = joy->axes[3];
    float js_cross_x = joy->axes[4];
    float js_cross_y = joy->axes[5];
    int js_A = joy->buttons[0];
    int js_B = joy->buttons[1];
    int js_C = joy->buttons[2];
    int js_D = joy->buttons[3];
    int js_L1 = joy->buttons[4];
    int js_R1 = joy->buttons[5];
    int js_L2 = joy->buttons[6];
    int js_R2 = joy->buttons[7];

    geometry_msgs::Twist twist;
    twist.linear.x = -scale_right_ * js_right_x;
    twist.linear.y = scale_right_ * js_right_y;
    // twist.linear.x = -scale_left_ * js_left_x;
    twist.angular.z = scale_left_ * js_left_x;

    // twist.linear.x = scale_cross_ * js_cross_y;
    // twist.angular.z = scale_cross_ * js_cross_x;


    vel_pub_.publish(twist);
}


int main(int argc, char** argv) {
    ros::init(argc, argv, "teleop_turtle");
    TeleopTurtle teleop_turtle;

    ros::spin();
}
