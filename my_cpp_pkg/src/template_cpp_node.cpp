#include "rclcpp/rclcpp.hpp"

class MyCustomNode : public rclcpp::Node // Modify this
{
public:
    MyCustomNode() : Node("node_name") //Modify this
    {

    }
private:

};


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyCustomNode>(); //Modify this
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}