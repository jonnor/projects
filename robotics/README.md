
http://www.anuncommonlab.com/articles/how-kalman-filters-work/

# Fun

Competitions with autonomous robots

* Folkrace. Drive RC-type cars around a track, longest distance in a timeperiod wins.
* Sumo. Push another robot outside a sumo ring

Typical robotics demo projects

* Line follower
* Balancing bot
* Obstacle avoidance
* Cathing objects

# Learning

## Kalman filters

Great for combining uncertain information. Used for instance for sensor fusion.

In the ALICE experiement at LHC/CERN, Kalman filters were used in orther to establish
the trajectories of particles based on their observations in the different sensor units (ITS, TPC, TRD).

* [How Kalman filters work](http://www.anuncommonlab.com/articles/how-kalman-filters-work/),
and other *recursive state estimation* algorithms, including *particle filters*, *Sigma-Point Filter*, *Extended Kalman* and *Linear Kalman*.
Linear Kalman can be done with simplified code, especially good for embedded systems.
* [How Kalman filters work: Part 2](http://www.anuncommonlab.com/articles/how-kalman-filters-work/part2.html),
discusses implementation considerations, both numerial and theoretical performance as well as speed.
Including *Joseph form*, *Square root filtering*, *sequential updates*. *Iteration* and *smoothing*
"use of sequential scalar updates can make a Kalman filter extremely fast".
Brief discussion of the related *information filter*.
Also verification through simulations, including *mismatched simulations* and *Monte Carlo*.

For realistic applications, a reduction to a small percentage of the runtime of the “full matrix” update is common"
* [How a Kalman filter works, in pictures](http://www.bzarg.com/p/how-a-kalman-filter-works-in-pictures/)
* [Extended Kalman filter](https://en.wikipedia.org/wiki/Extended_Kalman_filter),
"...the state transition and observation models don't need to be linear functions of the state but may instead be differentiable functions".
* Extended Kalman filter [on ARM Cortex M4](http://diydrones.com/profiles/blogs/px4-autopilot-new-software-hardware-accelerated-extended-kalman)
* Kalman filter implementation [on dsPIC30](http://tom.pycke.be/mav/92/kalman-demo-application)
* [Model based Kalman Filter for Mobile Robot Self-Localization](http://cdn.intechopen.com/pdfs-wm/10566.pdf)

