#include "ros/ros.h"

#include "std_msgs/Empty.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Int32MultiArray.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h> 

#include <pthread.h>

#include "Player.h"

player::player(int player_id){

    move_pub = n.advertise<std_msgs::Int32MultiArray>("get_move", 2);
    table_sub = n.subscribe("get_table", 2, &player::tableCallback,this);
    winner_sub = n.subscribe("winner", 2, &player::winnerCallback,this);
    id = player_id;
    pthread_mutex_init(&mtx,NULL);
    drop_msg = false;
}

player::~player(){

}

void player::tableCallback(const std_msgs::Int32MultiArray::ConstPtr& new_table){


    int i = 0;
    int table[9];
    int counter = 0;
    int randNum;
    std_msgs::Int32MultiArray move;
    ros::Rate loop_rate(0.5);

    pthread_mutex_lock( &mtx );

    if (drop_msg == true){
        drop_msg = false;
        pthread_mutex_unlock( &mtx );
        return;
    }

    //Copy table
	for(std::vector<int>::const_iterator it = new_table->data.begin(); it != new_table->data.end(); ++it)
	{
		table[i] = *it;
		i++;
	}

	//check if player turn then...
	for(i = 0; i < 9; i++){
        if (table[i] == 0){
            counter++;
        }
	}
	if (((counter + this->id )% 2) && counter != 0) {

        //... generate random numbers until you find an empty cell then fill the cell then...
        while(true){
            srand(time(NULL));
            randNum = rand()%(9);
            if (table[randNum] == 0){
                table[randNum] = this->id;
                break;
            }
        }
        //... publish move
        for(i = 0; i < 9; i++){
            move.data.push_back(table[i]);
        }
        drop_msg = true;
        move_pub.publish(move);

	}

    pthread_mutex_unlock( &mtx );

    return;
}

void player::winnerCallback(const std_msgs::Empty::ConstPtr& winner){
    ros::shutdown();
	return;
}

void player::Loop(){

    ros::spin();

    return;
}