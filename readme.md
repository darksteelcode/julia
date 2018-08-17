# Julia
A Julia set renderer for the TI-84 Plus CE, drawing an iterative fractal of the form *z*=*z*^2+*c*.

![](images/fractal1.png)
![](images/fractal2.png)
![](images/fractal3.png)

## Usage
#### Upload
To transfer to a calculator, send the `bin/julia.8xp` file to your calculator. If you get a message about needing `libload`, send all of the files in the `clibraries` directory to your calculator. These are the libraries that the program requires.
#### Usage
![](images/menu.png)
<br>The above image is of the main menu. On the main menu, parameters are set for the fractal. The following controls can be used:<br>
##### Controls
Enter: draw the fractal with the current parameters <br>
0-9 Keys: set the parameters to a series of presets. Use enter to draw. <br>
Arrow Keys: change the value of *c*. *c*'s value is represented by the crosshairs in the upper-left preview. <br>
2nd: update the preview in the upper-left to get an approzimation of what the fractal will look like.<br>
Plus and Minus keys: change the number of iterations<br>
( and ): change the colors for the background and foreground, repectivley. Press 2nd to draw preview in these colors.<br>
##### Exiting
During or after rendering, press and hold any key to exit.
