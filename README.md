# Text-UI-of-the-Floating-World: a project with several goals, or no goal but many side effects.
# A rough list/description:

The primary purpose for writing the main application, which make will cause gcc to compile into an executable, txwrk, was/is to test some of the libraries I've written which I will put in repositories, which I'll name when I create them here, and to see the functions put to use in an application rich in graphics.

The graphics library I put in a separate repository, Grali, is programmed using Xlib-xcb to generate the windows, and it uses a few of the functions to draw and create a color palette, and uses Cairo to create mono-space text in a somewhat window like structure drawn above, or as a layer within the graphics drawn in a window.

The functions in the library in Grali facilitate creating 2d graphics of limited color palette using solid colored filled squares in place of pixels, to draw low-res still or animated graphics. The progammer can control every individual pixel  individually with little effort. The effect can be very vivid, or it can be used to closely reproduce the look of old school graphics like the 1979 Atari VCS videogame console. You can write your own Pitfall Harry!

There is significant config file reader which can handily deal with hundreds of labelled values meant for hundereds of variables

The application compiled when one type $make work will, if it compiles, an executable: txwrk

%make work
%./txwrk
Segmentation fault (core dumped)

Hahahah! But yeah, if a textfile, txtui.cfg
  is not present in the same folder or contains bad data
  
PURPOSES:
Develop a set of functins and data types for the creation, display, and animation of pixel based graphics using limited palettes, and generally, tho' not neccessarily, low resolutions.
  The motivation initially was very specifically for making old school style videogames. How would it have been if home computers
  in the 1980's had virtully limitless computing power? What if video arcade games had the speed and RAM?
  
Noticable emergent behavior between interacting agents which moved and animated sprite-like graphics led to exploring and interacting with dynamic systems which exhibit emergence and sometimes complexity
  There are so many variables for the user to adjust that a new config file reader was required
   
To have the greatest, most dynamic interactin with the systems,a CLI superimposed on the moving graphics in real time seems like it will be the best solution so now we have dynamic study of dynamic systems and emergence
  So now we have the beginnings of terminal emulation, displaying characters floaating above moving graphics. The intent is to create a CLI for real time interaction with the systems which are drawing the graphics
  
For simplicity and direct pixel-level control of the contents of the diplay, I've chosen Xlib-XCB and discovered it is not the
ungainly awkward, cryptic incomprehensible challenge of hearsay.For limited needs in terms of GUI XCB seems almost spot on perfect and it interoperates with Xlib, which is copiously documented and there are good tutorials easily to be found online.

One final cherry- Cairo. Cairo is easy to use to draw in windows and has some nice baby functions perfect for
  drawing text over graphics in the buffers as well. Easy.
  
My experience as an old timer from the 8 bit era is that the things I've been warned away from as too low level are for the most part fairly simple. The use of Xlib-XCB was not difficult. Having only known Atari BASIC and BASIC XL, and some assembly for a few microprocessor, it was exciting to learn C, which I was also warned away from as dangerous, full of memory leaks and without any good libraries (????)

Possibly there are others who would get more into a simpler, less abstract and cautious into to programming.

As a hobbyist, and an old timer I've no use for all the low-stakes drama over programming dogmas you'll find in many discussion forums. 

AND THE WARNINGS PEOPLE GIVE HARPING ON THE SAME THING OVER AND OVER!!! ABSURD!! I'm glad I ignored so many of them.

No memory leak ever dripped corrosive fluid from my computer.

My hope if to help middle aged old nerds returning to computer programming as a hobby after decades away from it. It's hard at first to get one's bearings and to find the information one wants. People tend to steer the newbie towards they themselves are familiar with, and unknowingly hand out misinformation as advice, which is really just hearsay they've picked up.
  
My personal agenda is to have fun with writing code in C on a Unix-like system. What we have as commonplace, often free software resources was the stuff of dreams for nerds like me of the 80s. UNIX-like operating systems, big fast computers, a C compiler, all sorts of documentation, X windows!

I dreamt of those and now that they're here I just want to dive in and enjoy.

If one has no professional or serious software development needs or agenda ignore self-styled experts and forgive everyone their big egos and find your own way.

not argue niggly points my ego gets attached to.
