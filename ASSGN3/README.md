# Assignment 3 
## Submission Files
- `main.cpp`
- `ProjectProposal.pdf`

## Overview
The libraries we used for the demo are OpenGL, Box2D, and YSE. We used OpenGL 
to render the window and the objects and to handle keyboard input. Box2D 
allowed us to simulate a world with real-life properties, like gravity, and we 
used it to generate the coordinates for our moving objects. Finally, we used 
YSE to play music when the program is run.

When the program starts, a window opens. There is a square character that the 
user can control using the arrow keys. There are conditions to guard against the 
square moving off the screen. Additionally, there is a stream of small, blue 
squares moving down the screen, which is supposed to mimick rain. The stream is 
not infinite, and it accelerates faster with each tick. If the user presses the 
'F1' key, sound will start playing.

## Code Attributions
We followed examples in the library documentations and those found online in 
order to develop our code. We used what we learned from these examples and 
adapted them to meet the needs of our demo. For certain features, there was only 
one way to implement them (e.g., to play a sound in YSE, you need to: 1) 
initialize the audio system, 2) load the audio file, and 3) check if the audio 
file was propoerly loaded), so there was not much we could modify in these 
situations. Our sources are: 
- http://www.dgp.toronto.edu/~ah/csc418/fall_2001/tut/square (tutorial on how 
to render an object on a window in OpenGL) 
- http://www.iforce2d.net/b2dtut/introduction (Box2D tutorials on a wide variety 
of topics)
- http://www.attr-x.net/yse/reference/md_01_sound.html (tutorial on how to play 
a sound using YSE)
