# PowerUp - Motion Profile Testing
This branch is used for testing motion profile paths.  It contains all the functionality of the master branch with motion profiling added in a separate directory.  Some of the laptops had trouble compiling the motion profiling code.

The path is set in the Robot.cpp/TestInit method and can be tested using the Test mode in driver station.

Location codes:
 - RL, RC, RR - Robot placement at start of match.  Robot Left, Robot Centre, Robot Right
 - SL, SR - location of alliance lighted switch.  Switch Left, Switch Right
 - PY1, PY2 - cube location on the centre (pyramid) stack.  PY1 - first cube on the ground, PY2 - second cube on top of another cube
 So the autonomous command RCtoSRCommand sends the robot on the path from robot centre to switch right.  The CommandGroups commands use different autonomous commands to create a series of movements for the robot.
