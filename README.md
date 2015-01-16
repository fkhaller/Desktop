# Matrix-Explorer
Fairly straight forward. I used a basic linked list structure and created a 3 dimenional list to store each block of data
in the world. Matrix3D initializes the space and linked lists that hold all the blocks of the world. The Iterator does what 
iterators do and helps build object in the world. Object inserter handles putting objects into the world where Object veiwer
lets you see the world in the console. Console commands are handled by the main class where the world is also created.

The game has a practical restart mecanism that only triggers if you die. There are two ways to die. Get blown up by a bomb or fall from a certain height. You can climb over 1 unit high blocksby moving into them and you do fall when there is no block beneath you. The graphics are powered by ASCI and everythng is printed twice to make squares. The bombs start at 5 and end in 0.

all files except main are templates. I created this project with the GNU GCC Compiler in Code::Blocks and itis tested only with this compiler!
