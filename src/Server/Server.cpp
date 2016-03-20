//import ros libraries
#include "ros/ros.h"

//std::vector use for variable arrays
//#include <vector>
//using namespace std;
//vector<...> a;
//or
//#include <vector>
//std::vector<...> a;

//boost::array is used for fixed size arrays(better performance compared to std::vector)
//C++11 supports std::array that is similar to boost
//i think ros doesnt support std::array
//#include <boost/array.hpp>
//typedef boost::array<int8_t, 9> array;

//some arrays exists at std_msg
//these libraries use std::vector
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Int32MultiArray.h"
#include "std_msgs/Empty.h"

#include <boost/bind.hpp>


#include "Server.h"

//callback gets the msg
//msg is received through a boost::shared_ptr
//when all shared pointers that point at a msg gets deleted then the msg is deleted
//in order not be able to alter the msg from Callback, const is used
//although altering is possible using const_cast :)

server::server(){

    table_pub = n.advertise<std_msgs::Int32MultiArray>("get_table", 1,boost::bind(&server::connectCallback, this, _1));
    winner_pub = n.advertise<std_msgs::Empty>("winner", 1);
    move_sub = n.subscribe("get_move", 1, &server::moveCallback,this);
    for (int i = 0; i < 9 ; i++){
        saved_table.data.push_back(0);
    }
    pthread_mutex_init(&mtx,NULL);

}

server::~server()
{

}

void server::moveCallback(const std_msgs::Int32MultiArray::ConstPtr& new_table){

    int i = 0;
    std_msgs::Empty msg;
    int winner = 0;
    int table[9];
    int counter = 0;

    pthread_mutex_lock( &mtx );

    //Copy new table from msg - it is pressumed that players dont cheat
    saved_table.data.clear();
    ROS_INFO("Table\n");
	for(std::vector<int>::const_iterator it = new_table->data.begin(); it != new_table->data.end(); ++it)
	{
        saved_table.data.push_back(*it);
		table[i] = *it;
        ROS_INFO("%i\n",table[i]);
		i++;
	}
    ROS_INFO("End of Table\n");

    table_pub.publish(saved_table);

	//Rules
	if ((table[0] == 1 && table[1] == 1 && table[2] == 1) || (table[3] == 1 && table[4] == 1 && table[5] == 1) || (table[6] == 1 && table[7] == 1 && table[8] == 1)){
        winner = 1;
	}
    if ((table[0] == 1 && table[3] == 1 && table[6] == 1) || (table[1] == 1 && table[4] == 1 && table[7] == 1)){
        winner = 1;
	}
	if ((table[2] == 1 && table[5] == 1 && table[8] == 1) || (table[0] == 1 && table[4] == 1 && table[8] == 1) || (table[2] == 1 && table[4] == 1 && table[6] == 1)){
        winner = 1;
	}
	if ((table[0] == 2 && table[1] == 2 && table[2] == 2) || (table[3] == 2 && table[4] == 2 && table[5] == 2) || (table[6] == 2 && table[7] == 2 && table[8] == 2)){
        winner = 2;
	}
    if ((table[0] == 2 && table[3] == 2 && table[6] == 2) || (table[1] == 2 && table[4] == 2 && table[7] == 2)){
        winner = 2;
	}
	if ((table[2] == 2 && table[5] == 2 && table[8] == 2) || (table[0] == 2 && table[4] == 2 && table[8] == 2) || (table[2] == 2 && table[4] == 2 && table[6] == 2)){
        winner = 2;
	}

	//Checks if someone winned then sends msg to players to terminate
	if ( winner != 0 ){
        ROS_INFO("Winner is player %i\n",winner);
        winner_pub.publish(msg);
        ros::spinOnce();
        ros::shutdown();
	}

    //Checks if tie then sends msg to players to terminate
    for(i = 0; i < 9; i++){
        if(table[i] != 0){
            counter++;
        }
    }
    if (counter == 9){
        ROS_INFO("Tie\n");
        winner_pub.publish(msg);
        ros::spinOnce();
        ros::shutdown();
    }

    pthread_mutex_unlock( &mtx );

	return;
}

void server::connectCallback(const ros::SingleSubscriberPublisher& table_pub){
     
    table_pub.publish(saved_table);

}

void server::Loop(){

    ros::spin();

    return;
}
