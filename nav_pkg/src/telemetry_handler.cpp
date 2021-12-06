#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/BatteryState.h>
#include </home/husarion/husarion_ws/devel/include/rosbot_ekf/Imu.h>

void imuCallback(const rosbot_ekf::ImuConstPtr &imu)
{
    float x_orientation = imu->orientation.x;
    float y_orientation = imu->orientation.y;
    float z_orientation = imu->orientation.z;
    std::cout << "Orientation [" << x_orientation << " " << y_orientation << " " << z_orientation << "]" << std::endl;
    float angularVelocity[3];
    int index = 0;
    for (float value : imu->angular_velocity)
    {
	angularVelocity[index] = value;
	index++;
    }
    index = 0;
    std::cout << "Angular Velocity (deg/s): [";
    for(int i = 0; i<3; i++) 
    {
	std::cout << angularVelocity[i] << " ";
    }
    std::cout << "]" << std::endl;

    float linearAcceleration[3];
    for (float value : imu->linear_acceleration)
    {
        linearAcceleration[index] = value;
        index++;
    }
    index = 0;
    std::cout << "Linear Acceleration (G's): [";
    for(int i = 0; i<3; i++) 
    {
        std::cout << linearAcceleration[i] << " ";
    }
    std::cout << "]" << std::endl;
}

void batteryCallback(const sensor_msgs::BatteryStateConstPtr &batterystate)
{
    float Voltage = batterystate->voltage;
    std::cout << "Voltage: " << Voltage << std::endl;
    if(Voltage <= 10.0) {
	std::cout << "Battery Status: LOW" << std::endl;
    }
    else {
	std::cout << "Battery Status: OK" << std::endl;
    }
    //Eventually publish to necessary node for shipping to database
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "telemetry_handler");
    ros::NodeHandle n("~");
    ros::Subscriber sub_batt = n.subscribe("/battery", 1, batteryCallback);
    ros::Subscriber sub_imu = n.subscribe("/mpu9250", 1, imuCallback);
    ros::Rate loop_rate(0.5);
    while (ros::ok())
    {
        std::cout << "-----------------------------------------------------------" << std::endl;
        ros::spinOnce();
        loop_rate.sleep();
        std::cout << "---------------------------------------------------------" << std::endl;

    }
    
}
