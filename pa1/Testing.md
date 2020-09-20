<<<<<<< HEAD
#Testing

##Testing memory locations with gdb
In this small write up I will talk about how I tested my program with gdb and found the locations of my files in memory.
First thing that I needed to do was run gdb.

``` gbd -q album ```

Once the gdb was started I placed a breakpoint at each function. In the video I used the resizePhoto function. 

``` b resizePhoto ```

Then I wanted to pass it some arguments so I could find out where the programs memory jumped to and from.

`` r photos/*.jpg ```

This passed in all the photos (the whopping 2 photos) from my photo album into the gdb to be evaluated.

=======
#Testing

##Testing memory locations with gdb
In this small write up I will talk about how I tested my program with gdb and found the locations of my files in memory.
First thing that I needed to do was run gdb.

``` gbd -q album ```

Once the gdb was started I placed a breakpoint at each function. In the video I used the resizePhoto function. 

``` b resizePhoto ```

Then I wanted to pass it some arguments so I could find out where the programs memory jumped to and from.

`` r photos/*.jpg ```

This passed in all the photos (the whopping 2 photos) from my photo album into the gdb to be evaluated.

>>>>>>> 0453ffae993d168f1e5dcbccc37ccbb8a9bde253
