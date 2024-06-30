#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

class RobotNewsStationNode : public rclcpp::Node 
{
public:
    RobotNewsStationNode() : Node("robot_news_station") 
    {
        this->declare_parameter("robot_name","216");
        robot_name_=this->get_parameter("robot_name").as_string();
        
        publisher_ = this-> create_publisher<example_interfaces::msg::String>("Robotic_News",10);

        timer_ = this->create_wall_timer(std::chrono::milliseconds(500),
                                        std::bind(&RobotNewsStationNode::publishNews, this));

        RCLCPP_INFO(this->get_logger(),"Gora News Station has been started.");
    }
private:
    

    void publishNews()
    {
        auto msg = example_interfaces::msg::String();
        msg.data = std::string("Hellou, this is a me ")+ robot_name_ + std::string(" from the Gora News Station");
        publisher_->publish(msg);
    }

    std::string robot_name_;
    rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotNewsStationNode>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}