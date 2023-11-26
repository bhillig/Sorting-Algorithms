# Sorting Algorithms Visualizer
A C++ desktop application that visualizes multiple sorting algorithms. Supports Bubble Sort, Selection Sort, and Insertion Sort.

Having used multiple sorting visualizers online, I was frustrated at the lack of interaction among them. I wanted to be able to change the algorithm in real-time to see how the data reacted and a have a greater sense of control of what was going on. So I decided to build one myself.

## Features:

- Users can adjust both the number of elements and speed of the algorithm during execution

- Users can change sorting algorithms mid execution to see the data dynamically change

![](https://github.com/bhillig/Sorting-Algorithms/blob/main/gifs/multisort.gif)

## How It's Made:

**Tech used:** C++, SFML, ImGui

Upon start-up a random set of data is generated in C++ and visualized using SFML. The application runs in an idle loop until the user either manipulates the data or sorts it. When sorting is requested, the application will execute the algorithm desired bit by bit each frame at a speed given by the user.

The SFML graphics library is used to give a visual representation of the data.

The ImGui library is used to give the user immediate control over which algorithm they want to visualize and how they want it to perform. The application supports resizing the data, changing its color, and speed at which its current algorithm is performed. 

![](https://github.com/bhillig/Sorting-Algorithms/blob/main/gifs/sort.gif)

## Optimizations & Improvements

Currently, the application limits the sorting algorithm speed by manually breaking out of sorting after a few swaps occurs. Due to various implementation differences, this can cause some sorting algorithms to get more work done than others per frame. Instead of manually breaking I would like to add asynchronous support in the future that limits algorithms by time.

## Lessons Learned:

This project was unique to me in that it was the first time I had to intentionally limit the performance of the code I was writing so that it could be visualized over the course of many frames instead of one.

I learned a lot on application architecture while developing this as I wanted to ensure it would be easy to implement further additions and improvements.

## Other Projects:
Take a look at my other projects:

**Neon Blade Impetus:** https://github.com/bhillig/Neon-Blade-Impetus

**CShell:** https://github.com/bhillig/CShell
