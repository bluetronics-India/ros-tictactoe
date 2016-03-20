#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__

#include "ros/ros.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Int32MultiArray.h"
#include "std_msgs/Empty.h"

#include <pthread.h>


struct player{

    private:
        ros::NodeHandle n;
        ros::Subscriber table_sub;
        ros::Subscriber winner_sub;
        ros::Publisher move_pub;
        pthread_mutex_t mtx;
        int id;
        bool drop_msg;
        
    public:
        player(int player_id);
        ~player();
        void tableCallback(const std_msgs::Int32MultiArray::ConstPtr& new_table);
        void winnerCallback(const std_msgs::Empty::ConstPtr& winner);
        void Loop();

};

#endif