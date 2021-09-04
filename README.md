# Lo res Artist of the Floating World: a project with several goals, or no goal but many side effects.
# A rough list/description:

PURPOSES:
Develop a set of functions and data types for the creation, display, and animation of pixel based graphics using limited palettes, and generally, tho' not neccessarily, low resolutions.
  The motivation initially was very specifically for making old school style videogames. How would it have been if home computers
  in the 1980's had virtully limitless computing power? What if video arcade games had the speed and RAM?
  
  As I wrote code to test the graphics functions, emergent behavior and hints of complexity arose among the interacting objects used to draw various animations and images. So more and more variables were called for until the thing evolved into something else. There's a nice simple config file reader, a way to take enums from C code and put them in config files and then specify values in the config file using the tokens of the enum like enum example_enum { value0, value1, value2 }; and then in the file: variablename_example = value1
  
For simplicity and direct pixel-level control of the contents of the diplay, I've chosen Xlib-XCB and discovered it is but doesn't have to be the
ungainly awkward, cryptic incomprehensible challenge it generally is said to be. For limited needs in terms of GUI XCB seems almost spot on perfect and it interoperates with Xlib, which is copiously documented and there are good tutorials easily to be found online.

One final cherry- Cairo. Cairo is easy to use to draw in windows and has some nice baby functions perfect for
  drawing text over graphics in the buffers as well. Easy.
  
My experience as an old timer from the 8 bit era is that the things I've been warned away from as too low level are for the most part fairly simple. The use of Xlib-XCB was not difficult. Having only known Atari BASIC and BASIC XL, and some assembly for a few microprocessors, it was exciting to learn C, which I was also warned away from as dangerous, full of memory leaks and without any good libraries (????)

Possibly there are others who would get more into a simpler, less abstract and cautious into to programming.

As a hobbyist, and an old timer I've no use for all the low-stakes drama over programming dogmas you'll find in many discussion forums. 

AND THE WARNINGS PEOPLE GIVE HARPING ON THE SAME THING OVER AND OVER!!! ABSURD!! I'm glad I ignored so many of them.

No memory leak ever dripped corrosive fluid from my computer.

My hope if to help middle aged old nerds returning to computer programming as a hobby after decades away from it. It's hard at first to get one's bearings and to find the information one wants. People tend to steer the newbie towards they themselves are familiar with, and unknowingly hand out misinformation as advice, which is really just hearsay they've picked up.
  
My personal agenda is to have fun with writing code in C on a Unix-like system. What we have as commonplace, often free software resources was the stuff of dreams for nerds like me of the 80s. UNIX-like operating systems, big fast computers, a C compiler, all sorts of documentation, X windows!

I dreamt of those and now that they're here I just want to dive in and enjoy.

If one has no professional or serious software development needs or agenda ignore self-styled experts and forgive everyone their big egos and find your own way.

not argue niggly points my ego gets attached to.
