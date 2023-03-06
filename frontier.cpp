#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>
#include <vector>
#include <stack>

// Define the global variables
ros::Publisher cmd_vel_pub;
sensor_msgs::LaserScan laser_msg;
std::vector<float> laser_ranges;
bool laser_received = false;

// Define the DFS algorithm
void DFS()
{
    // Create a stack to keep track of the visited nodes
    std::stack<std::pair<int, int>> node_stack;

    // Create a 2D array to keep track of the visited nodes
    int visited[laser_msg.ranges.size()][laser_msg.ranges.size()] = {0};

    // Set the starting position to the middle of the environment
    int x = laser_msg.ranges.size() / 2;
    int y = laser_msg.ranges.size() / 2;

    // Push the starting position onto the stack
    node_stack.push(std::make_pair(x, y));

    // Loop until the stack is empty
    while (!node_stack.empty())
    {
        // Get the current position
        std::pair<int, int> current_node = node_stack.top();
        node_stack.pop();

        // Check if the current node is a frontier
        if (laser_ranges[current_node.first + current_node.second * laser_msg.ranges.size()] > 3.0 && !visited[current_node.first][current_node.second])
        {
            // Publish a command to move to the frontier
            geometry_msgs::Twist cmd_vel_msg;
            cmd_vel_msg.linear.x = 0.5;
            cmd_vel_pub.publish(cmd_vel_msg);

            // Mark the frontier as visited
            visited[current_node.first][current_node.second] = 1;
        }
        else
        {
            // Mark the current node as visited
            visited[current_node.first][current_node.second] = 1;

            // Push the neighbors onto the stack
            if (current_node.first > 0 && !visited[current_node.first - 1][current_node.second])
            {
                node_stack.push(std::make_pair(current_node.first - 1, current_node.second));
            }
            if (current_node.first < laser_msg.ranges.size() - 1 && !visited[current_node.first + 1][current_node.second])
            {
                node_stack.push(std::make_pair(current_node.first + 1, current_node.second));
            }
            if (current_node.second > 0 && !visited[current_node.first][current_node.second - 1])
            {
                node_stack.push(std::make_pair(current_node.first, current_node.second - 1));
            }
            if (current_node.second < laser_msg.ranges.size() - 1 && !visited[current_node.first][current_node.second + 1])
            {
                node_stack.push(std::make_pair(current_node.first, current_node.second + 1));
            }
        }
    }
}

// Define the laser scan callback function
void laserCallback(const sensor_msgs::LaserScan::ConstPtr
