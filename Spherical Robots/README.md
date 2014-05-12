Spherical Swarm Robotics Control System
=======================================

As a junior in high school, I carried out original robotics research. Over the course of six months, I designed, prototyped, and wrote software for two spherical robots endowed with the ability to move independently, visually communicate, and interact with one another.
 

 
Abstract
=================

Spherical Swarm Robotics: Re-imagining Motion Mechanics for Collaboration
Garrett Parrish

The collaboration of organisms is an intrinsic aspect of the natural world (and our society); one of the most intriguing areas of robotics that has enormous potential is swarm collaboration. Similar processes such as task delegation and prioritization, informed through data collection and analysis, can be applied to swarm robotics. The technical issue to be addressed is the mechanical incompatibility of robots; new motion mechanisms can solve this problem. This research focused on mechanically re-envisioning robots so that teams can collaboratively gain and synthesize information and increase their efficiency, adaptability, and applications.
 
In order to fulfill design criteria of 1) being omni-directional, 2) having all mechanisms enclosed, 3) using inertial sensing and 4) using visual and wireless communication, a transparent sphere was employed as the primary design concept. 

Two motion mechanisms resulted from countless iterations on basic motion concepts. Two prototypes were constructed and tested (i.e. for max incline angle). Extensive theoretical modeling of the motion mechanisms was carried out using both Classical and Lagrangian Mechanics; this information, along with sensory data, gain information about the environment. A control scheme was designed, programmed, and implemented to allow precise control in all directions. 
 
A tangible application of this technology is in the sensing, mapping, and disarming of mine fields in military areas. Working as a team, any number of spheres could map out a minefield or even lead soldiers and vehicles through dangerous areas. The design of new motion mechanisms to increase collaborative interaction between robots will allow engineers to more effectively design and utilize the next generation of economic, intelligent, applicable, and versatile robotic systems. 

Mechanical Design
==========

The most fundamental mechanical component to be addressed is the chassis; it must be designed to elegantly incorporate a new motion mechanism that enhances collaboration. I chose the design of a sphere for four reasons:
﻿﻿
​A. Omni-directional chassis: essential for visual communication, positioning, and motion in any direction.

B. Built-in motion correction: if the robot loses balance, it will right itself (as opposed to traditional robots with a wheeled platform).
 
C. One point of contact with the ground: only one appendage needs to be controlled (eliminating problems associated with multiple legs).
﻿
D. Internal compartment: minimal interference with the environment and a safe housing for mechanical equipment.
﻿
The majority of my research (other than implementation) focused on the design of the motion mechanisms for a sphere. I purchased hamster balls from Petco and set out to design mechanisms to allow them to maneuver and interact.


Control Algorithms
===========

I used the Arduino microcontroller and programming language to control Mowgli and Baloo. For digital communication, I used XBEE wireless modules to connect the controller (Wii Nunchuk) to the robots. Designing, constructing, and building the electronics required a huge learning curve, since I was unfamiliar with the Java and Arduino programming languages, Lagrangian Mechanics, how servos and motors work, how to hack a Wii Nunchuk, what Pulse Width Modulation is, and much more.

I wanted to use a Wii Nunchuk as my controller, but since Nintendo doesn't allow for public prototyping, I had to hack into it. I set up a handshake with the Nunchuk, created a protocol to collect data from it, de-encrypted the output data, and converted it to a readable format. Next, I set up XBEE Wireless Modules to transmit the data, and implemented various fail-safes to ensure a continuous data stream.

I wanted to linearly map the joystick (or accelerometer) to the speed of my robot, so that when the driver pushes the joystick to half the max angle, the sphere would travel at half speed. I wrote a Java program that iterated through different PWM delay values (speeds) for the servo; I then used a video camera and Photoshop to calculate the angular displacement the servo traversed in five seconds, finding the angular speed that corresponded to that PWM delay. All the servos I used were slightly different, so I repeated this process four times.
​
I established a scale of the output data from the Nunchuk and mapped it to the desired speed.
​
I found the Taylor approximation (using hyperbolic tangent as a model) of the PWM vs. Angular Velocity relationship, and used its inverse to connect the desired speed to the correct PWM delay.  A similar process was repeated for the turn servo on my first prototype (i.e. tilt the joystick 45 degrees right - sphere tilts 45 degrees to the right).

I carried out various optimization tests (max incline angle, optimizing strait-line trajectories, and reducing wobbling), as well as made theoretical plans for allowing for collaboration (visual/digital communication). 


Links
===========

Demo video: http://www.youtube.com/watch?v=y_XDvefP_04

Project Desctiption: http://www.garrettparrish.com/#!spherical-swarm-robotics/c22fl

Press Release: http://linc.mit.edu/stem/2012-may/Schluter.html

Copyright Garrett Parrish 2012.
