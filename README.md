# NSGA [![Build Status](https://travis-ci.org/pawel-jakubowski/NSGA.svg?branch=master)](https://travis-ci.org/pawel-jakubowski/NSGA)

Non-Dominated Sorting Genetic Algorithm as Bicriterial Optimization Method with constraints

![NSGA](https://cloud.githubusercontent.com/assets/9104400/22433253/0f3865ca-e718-11e6-948d-27e98a9c70c3.png)

## Features
* Solving bicriterial optimization problem with constraints (NSGA-II)
* Processing of two goal functions with up to 5 variables as string ```f(x1,x2,x3,x4,x5)```
* Allows to define up to 5 constraints
* Plots expression and Pareto-optimized solution vector
 
For details of implementation check algorithm description on wiki:
https://github.com/pawel-jakubowski/NSGA/wiki/Algorithm-description

## User manual

![Application GUI](https://cloud.githubusercontent.com/assets/9104400/22433227/f4ea49c2-e717-11e6-9bef-cbd3b19da6df.jpg)

### Basic parameters
In order to find a solution of a multi objective optimization problem define the following data in the program:
-	Functions input – objectives to be optimized described by objective functions ```f1, f2``` e.g. ```x1^2+x2^2+ atan(x3)= 0```
- Restrictions input – restrictions to solution space ```g1 – g5```, declared as a inequalities
-	Boundaries – (optionable) this window allows user to set additional boundaries for specific decision vector value  

### Advanced settings
This tab contains values that allows improving the solution result by defining specific values of genetic algorithm. If not declared, the default settings will be used.
-	Individuals number – number of individuals in initial population can be changed by typing a constant in this line (default: 50)
-	Generations number - number of generations can be changed by typing a constant in this line (default: 5)
-	Variables number - number of variables defines the x’s count in objective functions (default: 5),
-	Lower/Upper bound – in this window user can set general boundaries for function parameters (```x1```, ```x2```, etc.) (default: -5, 5)

### Launch
After functions, constraints, bounds and genetic algorithm values declaration, click the *Launch* button - that initiates the genetic algorithm and plots the solution in plot tab when it ends.

*NOTE: GUI allows user to check the specific solution values and genetic algorithm parameters in a Log tab.*

### Plot
It is possible to resize, scope and move the plot simply by using scroll and left mouse button. To move around the plot area push and hold the left mouse button while moving the mouse in the direction according to the direction of the plot translation. In order to focus on a specific area of a plot scroll backwards. To decrease the focus scroll forward.

### Available functions
|Function|Description|
|:------:|-----------|
|sin|sine trigonometric function|
|cos|cosine trigonometric function|
|tan|tangent trigonometric function|
|asin|	arcsine trigonometric function|
|acos|	arcosine trigonometric function|
|atan|	arctangent trigonometric function|
|sinh|	hyperbolic sine trigonometric function|
|cosh|	hyperbolic cosine trigonometric function|
|tanh|	hyperbolic tangent trigonometric function|
|ln|	natural logarithm|
|log|	logarithm of base 10|
|log2|	logarithm of base 2|
|log10|	logarithm of base 10|
|exp|	exponent|
|sqrt|	squared root|
|abs|	absolute value|
|sign|	signum|

### Available operations
|Symbol|Description|
|:----:|-----------|
|+|	plus|
|-|	minus|
|=|	equality|
|*|	multiplication|
|/|	division|
|^|	exponentiation|
|<|	less than|
|>|	greater than|
|<=|	less than or equal to|
|>=|	greater than or equal to|

 
