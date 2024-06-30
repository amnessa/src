#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"
#include "example_interfaces/msg/int64.hpp"
#include "example_interfaces/srv/set_bool.hpp"

class Number_counter : public rclcpp::Node 
{
public:
    Number_counter() : Node("subscriber_publisher") ,counter_(0)
    {
        subscriber_ = this -> create_subscription<example_interfaces::msg::Int64>("Number", 10,
                            std::bind(&Number_counter::callbacknews, this, std::placeholders::_1));
        RCLCPP_INFO(this->get_logger(),"subcription started"); 

        publisher_= this-> create_publisher<example_interfaces::msg::Int64>("number_count",10); 

        RCLCPP_INFO(this->get_logger(),"sub publish started");  

        reset_number_service_ = this-> create_service<example_interfaces::srv::SetBool>("reset_counter",
                            std::bind(&Number_counter::callbackresetter, this, std::placeholders::_1,std::placeholders::_2));


    }
private:

    void callbacknews(const example_interfaces::msg::Int64::SharedPtr msg)
    {
        counter_ += msg->data;
        auto newMsg = example_interfaces::msg::Int64();
        newMsg.data= counter_;
        publisher_->publish(newMsg);
    }

    void callbackresetter(const example_interfaces::srv::SetBool::Request::SharedPtr request,
                            const example_interfaces::srv::SetBool::Response::SharedPtr response)
    {
        if(request->data){
            counter_= 0;
            response->success = true;
            response->message = "Counter has been reset";
        }else{
            response->success = false;
            response->message = "Counter has not been reset";
        }
    }

    int counter_;
    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscriber_;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    rclcpp::Service<example_interfaces::srv::SetBool>:: SharedPtr reset_number_service_;
};


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Number_counter>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}