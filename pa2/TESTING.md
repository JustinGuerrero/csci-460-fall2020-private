#Justin Guerrero : Operating Systems CS460
## Testing

This program required a lot more testing. I was in deadlocks, I was unsure if I was making threads, and I was unsure what the gdb was even telling me (wasn't much.) However, it was nice to be able to see where my faults were happening.

Running gdb step by step using the "next" function allowed me to basically do the exact same thing clion does or any IDE that uses the "step into" function. When I was experiencing deadlock it allowed me to step from line to line showing me where things happened.

The problem wasn't in my code at all but rather in a variable that was misnamed. I had spelled RADNSEED instead of RANDSEED. Which pretty much bombed my entire code. 