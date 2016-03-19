# ros-tictactoe
A ros package which implements tictactoe simulation created for training in ros.
How to install the tictactoe simulator:

1. Create a workspace for the simulator

    ```
    mkdir -p ~/tictactoe_ws/src
    cd  ~/tictactoe_ws/src
    catkin_init_workspace
    ```
2. Download dependencies

    ```
    mkdir complex_communication
    cd complex_communication
    git clone https://github.com/iolyp/ros-tictactoe.git
    cd ..
    cd ..
    ```
3. Build the simulator

    ```
    catkin_make
    ```
4. Source the environment

    ```
    source devel/setup.bash
    ```
How to run a game simulation:

1. Run a simulation by executing a launch file:

    ```
    roslaunch complex_communication start_game.launch
    ```
