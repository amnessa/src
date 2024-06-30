from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    ld= LaunchDescription()

    station_names =["216","arif","ceku","bob_marley_faruk","Garavel_Usta"]

    robot_news_station_nodes = []

    for name in station_names:
        robot_news_station_nodes.append(Node(
            package="my_cpp_pkg",
            executable="gora_news_node",
            name="robot_news_station" + name.lower(),
            parameters=[{"robot_name":name}]
        ))

    smartphone_node= Node(
        package="my_cpp_pkg",
        executable="smartphone_node",
        name="smartphone"
    )


    for node in robot_news_station_nodes:
        ld.add_action(node)

    ld.add_action(smartphone_node)        
    return ld