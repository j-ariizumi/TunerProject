# Piezo Tuner Project

Welcome to my tuner project! 
In this repo, you can find my code with the Arduino libraries (hopefully I move it to baremetal soon), my PCB schematics and layout, and my CAD files for the encasement.

## Purpose
As a hobbyist double bass player, I have been in several amateur orchestras.  
  
If you've ever tuned at an orchestra rehearsal before, you'd know just how annoying it is to try and listen to your instrument to tune while the person next to you is practicing their part last minute because they didn't practice all week.  
  
That's why, for me, the most reliable option for tuning was using a clip-on tuner that relied on vibrations rather than a mic.
Taking this, combined with my desire to learn about designing and developing a project, I decided to make my own tuner!

## Principle of how it works
Piezoelectric materials are materials that produce voltage when a mechanical strain or stress is applied to them.
I use a piezoelectric disk as my sensor in this project, as the vibration from my instrument will produce a voltage at a frequency equal to the note that is being played by the instrument.
