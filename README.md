# Money Detector 

- Using opencv librry to filter the image and only detect the edges of the money notes and coins (Removing the details)
- Implemented Linear Hough Transform function that takes the edge detected image and returns list of all lines within the threshold
- Implmeneted Circular Hough Transform function, takes a min and max radius to find in the image and returns a list of circles found
- Implmeneted Rectangle Detector that takes the list of lines from the Linear Hough transform and find all possible rectangles
- Implemented Color Detector that masks the circles and rectanlges found and uses color thresholding to detect the value of the coin or money note. 
