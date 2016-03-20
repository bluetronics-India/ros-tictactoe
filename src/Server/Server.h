#ifndef __SERVER_H_INCLUDED__
#define __SERVER_H_INCLUDED__

#include "ros/ros.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Int32MultiArray.h"

struct server{

    private:
        ros::NodeHandle n;
        ros::Subscriber move_sub;
        ros::Publisher winner_pub;
        ros::Publisher table_pub;
        std_msgs::Int32MultiArray saved_table;
        pthread_mutex_t mtx;
        
    public:
        server();
        ~server();
        void moveCallback(const std_msgs::Int32MultiArray::ConstPtr& new_table);
        void connectCallback(const ros::SingleSubscriberPublisher& table_pub);
        void Loop();

};

#endif