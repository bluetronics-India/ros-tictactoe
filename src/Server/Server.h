#ifndef __SERVER_H_INCLUDED__
#define __SERVER_H_INCLUDED__

#include "ros/ros.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Int32MultiArray.h"

struct server{

    private:
        ros::NodeHandle n;
        ros::Subscriber table_sub;
        ros::Publisher winner_pub;
        ros::Publisher table_pub;
        std_msgs::Int32MultiArray saved_table;
        
    public:
        server();
        ~server();
        void moveCallback(const std_msgs::Int32MultiArray::ConstPtr& new_table);
        void Loop();

};

#endif