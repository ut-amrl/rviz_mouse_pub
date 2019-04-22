# rviz_mouse_pub
RViz plugin to publish mouse interactions with 2D map.

## Dependencies
Install [ROS](http://wiki.ros.org/ROS/Installation)

## Build
1. Add the project path to `ROS_PACKAGE_PATH`
1. Run `make`

## Run
1. Run rviz as usual:
    ```
    rosrun rviz rviz
    ```
1. Add the plugin to RViz using the "+" button on the toolbar.
1. Click on the "MousePub" button to activate the tool
1. Mouse events will be published to `mouse_pub`
