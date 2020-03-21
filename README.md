# Text-UI-of-the-Floating-World is a project with several goals, or possibly no goal but many side effects, depending how one looks at it. Let's see a list:

Develop a set of functins and data types for the creation, display, and animation of pixel based graphics using limited palettes, and generally, tho' not neccessarily, low resolutions.
  The motivation initially was very specifically for making old school style videogames. How would it have been if home computers
  in the 1980's had virtully limitless computing power? What if video arcade games had the speed and RAM?
  
More generally, it is the quality and inventiveness of the artful graphics of those old games which the very limited colors,
resolution, processing power, and memory drew from the game designer. The games were competing for quarters in videogame
arcades and competition breeds creativity.
  As an artist, I want to use those limits-or some of the characteristic limits of those
  days as formal rules as part of my process, to stimulate my own inventiveness and creativity.
  
I noticed emergent behavior in the mass of interacting objects which moved and animated sprite-like graphics like Mario in Donky
Kong or the combating avatars in Electronic Arts' game, Archon, hich used to love playing with my friends in high school, on my
Atari 800XL back in high schoo. I began exploring.
  Now we have exploration of and interaction with dynamic systems which exhibit emergence and sometimes complexity
  There are far more variables for the user to adjust now beyond the keyboard controls or joystick and trigger
  Exploring is a creative process-expression of the emotions, curiosity and fascination will be part of my artist's process
   
To have the greatest, most dynamic interactin with the systems,a CLI superimposed on the moving graphics in real time seems like it will be the best solution so now we have dynamic study of dynamic systems and emergence
  So now we have terminal emulation, displaying characters floaating above graphic representations-animatin probably-of the
  behaviors happening within the systems. Beyond just drawing the characters will be the CLI itself.
  For now, the application will generate simple menus and "scoreboards," displays in a menu style of the values of different
  parameters and internal data structure of the actors within the system.
  
For simplicity and direct pixel-level control of the contents of the diplay, I've chosen Xlib-XCB and discovered it is not the
ungainly awkward, cryptic incomprehensible challenge of hearsay. GTK+ and Qt would be MORE complicated and they don't allow for such total control. For limited needs in terms of GUI XCB seems almost spot on perfect and it interoperates with Xlib, which has some very good simplifications AND is copiously documents and some very good tutorials-which can be applied to XCB once one becomes acquainted well enough with them.
  This is the last big thing at the moment-creating windows, offscreen buffers, drawing in them and swapping them to show
  animation and one final cherry- Cairo. Cairo is easy to use to draw in windows and has some nice baby functions perfect for
  drawing text over graphics in the buffers as well. Easy.
  
My experience as an old timer from the 8 bit era is that the things I've been warned away from as too low level are for the most part fairly simple, and writing small functions to further simplify use of Xlib-XCB was not difficult. Having only know Atari BASIC and BASIC XL, and some assembly for a few microprocessor, it was exciting to learn C, which I was also warned away from. Maybe those warnings are good for the more serious development environment but had I heeded them I'd have missed out on getting into the nitty gritty. AND ironically, would have had much more to learn with those helpful highly abstracted libraries or getting into JavaScript
  Possibly there are others who would get more into a simpler, less abstract and cautious into to programming. I certainly am
  glad I sidestepped HTML-5 and complex object orient development environments and language. As a hobbyist, and an old timer,
  all the low-stakes drama over programming dogmas are just a waste of energy. No memory leak ever dripped corrosive fluid from
  my computer. I'd like to write some guide for middle aged old nerds returning to computer programming as a hobby after being
  away for a few decades. It's hard at first to get one's bearings and to find the information one wants. People tend to steer
  the newbie towards their own preferences, which they believe are superior, and at first it was easy to believe them-they sound
  so confident. But some wil warn you away with misinformation from things they know nothing about.
  
Grouchy aren't I? But my hope is to find and have fun with writing code for fun, and explore what was the stuff of legends
for nerds of the 80s. UNIX-like operating systems, big fast computers, a C compiler, all sorts of documentation, X windows!
I dreamt of those and now that they're here I just want to dive in and enjoy, not argue niggly points my ego gets attached to.
  
I'd like to rewrite this with 1/10th the vebiage. SO verbose!
