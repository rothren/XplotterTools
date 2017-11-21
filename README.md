# XplotterTools
A small c program generating gcode files for the XPlotter


**How to use

Well... there isn't a lot to say, it is a single c file with no dependency. Just open it in Eclipse/CodeBlocks/or the IDE you like the most, compile and run. After that, you'll find a "xplotter.g" file in your source folder. Put this file on a SD card, put the card in your Xplotter... et voilà!

**What you got (for now):

/!\Remember, all coordinates are in mm and can be floating! (ex : circle(10 , 20.45 , 7.86) Will draw a circle at (10,20.45) with a 7.86mm radius

line(x1,y1,x2,y2) : draw a line between point (x1,y1) and (x2,y2)

lineRelative(x,y) : draw a line from your current position going on a (x,y) vector.

circle(x,y,r) : draw a circle at (x,y) with a radius of 'r' 

int fingerJoint (float x1, float y1, float x2, float y2,float firstTeethLength, float teethLength, float teethDepth);
This one... raws a fingerjoint, usually used for box assembly. It goes from (x1,y1) to (x2,y2), straight at first for 'firstTeethLength' millimeters, then draws teeh that are 'teethlength' long and 'teethDepth' deep. Ex:
fingerJoint(0,0,105,0,  10  ,  5  ,  3);
draws a perfect fingerjoint from 0 to 105 on th x axis... just try it out!

arcDegtoDeg(x1,y1,r,angle1,angle2,direction) : draw an arc where the center is at (x1,y1), with a 'r' radius, between angle1 and angle2 (in degrees). direction needs to be positive or negative, to indicate... well, what's the direction between the two angles. positive is clockwise, megative is counterclockwise. 
Small example : 
     arcDegtoDeg(50,50,10,0,90,1)
     
     This will draw a quarter circle (angle 0 to angle 90 in a positive path), centered in 50,50, with a radius of 10
     Inverting the direction will draw 3/4th of a circle! (going from angle 0 to angle 90 counterclockwise takes 270degrees)

**You can also : 

move(x,y) : Go to position (x,y) at normal speed. Beware! If laser in on, it will stay on!

moveFast(x,y) : Go to position (x,y) as fast as possible. Other future operations will still go at the speed you specified.

setPower(power) : Set the laser power (0-255) 0 is off, 255 is  as hot as possible.

setSpeed(speed) : Set the speed at which you are drawing stuff in mm/min

laserOn() : Activate the laser. If power is on 0, it still wont work.

laserOff() : Deactivate the laser.

setAbsolute() : 'Normal' mode for this program. should be used everywhere, except (see setRelative())

setRelative() : set coordinates to relative. should only be used with the 'move()' or 'moveFast' functions, and directly set back to absolute mode.

--------------------------------------------


**I don't know anything about programming :(

That's not really important, I'm sure you'll be able to use this!

Step 1 : Donwload Codeblocks

Go on http://www.codeblocks.org/downloads/26 and download  codeblocks-16.01mingw-setup.exe (or whatever version number it is)

Step 2 : Install Codeblocks

Wherever you want

Step 3 : Create a new project

Click on 'Create a new project' (once Code::Blocks has started)
Choose 'Console application'
Next
Choose "C", NOT "C++"!
Next
Give a name to your project
Next
Finish

On the file browser on the left of the screen, look for a 'main.c' file in the "Sources" folder, and open it.
Erase everything, paste the content of my 'main.c' file that you can find somewhere on this github project.
In this file, you'll find a commentary (a line starting with //) saying : 
//and here you add what you want!

...well, that's pretty self explanatory, that's where you should starting typing your commands!
When you're done, go on Build>Build and Run.
If there's no error, you should have a xplotter.g file in your project folder, congratulation!


