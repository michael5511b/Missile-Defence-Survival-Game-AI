# Missile Survival Game AI

## Q&A
- Write an overview of how your AI works, including how it detects where projectiles will fall and how it chooses where to go.

**ANS**: Given the position and velocity of each projectiles in the air, using some basic physics calculations, we can acquire the time and position where each projectile is going to land. We mark the land with missiles about to land and the land with explosions happening as "1" and "2", leaving "0" as indication of safe space. The player's AI would move towards the nearest 0 at any given moment.

- What challenges did you face when writing an AI?

**ANS**: I would say the biggest challenge is not the programming itself. These few weeks have been very hectic for an MRSD student and I barely have the time to do this homework. I do, however, very much enjoy this assignment and intend to perfect my AI in the future.

- How well does your AI work on a Hard scenario? If it doesn’t work, why? If it does, try harder scenarios and see when it does fail and explain why?

**ANS**: It does not work as well as in the medium level. I suspect it is due to the binary nature of the "1" and "0" labeling. If given more time, I would score each discrete space based on "the distance of predicted landing zone to self" and "time until the missile lands".

- What did you think of the assignment and did it meet its goals? Why or why not?

**ANS**: I really enjoy this assignment, it is fun and it introduce us to all the important OOD features of C++ in a cool way.
