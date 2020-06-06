# Code Style

This is CodeStyle for ChocolataClicer Apps contributed by Bohdan Velichko and Ili Abernihin

Please make sure your code conforms to the following general guidelines. If something is unclear or undocumented, the rule of thumb is to try to make the source code easy to read, concise, and match the code around it.

* * *


### Naming

Naming of all code structures for ChocolataSlicer Apps.

* Use camelCase; classes begin with upper case and variables with lower case.
* Member variables begin with an ’_' prefix and small letter (_variable).
<!-- * Static variables begin with an ’s' prefix (sInstance). -->
* enum types are uppercase camelCase enum name with underscore + uppercase enum variable
    * ex. enum FileType_ { FileType_Stl, FileType_Obj, FileType_Amf }. 

* * *


### Spacing and Line Breaks 

* Use tabs for indentation, with a tab stop value of 4.
* Anything inside a namespace starts with no indentation.
* Place spaces between braces, braces and arguments, etc.

* Brackets for class methods and functions begin on a new line. Brackets for everything else (class declarations, if / for / while loops, etc. ) begin on the same line following a space.
* The contents of an if, for, or while statement should always be on a new line. This not only makes it easier to read but also prevents some ambiguities that come up in some debugging situations, where you can’t tell if you’ve jumped into the body of the statement or * not. 
* else statements should be placed on a new line for vertical readability. 

* * *


### Types

* Users types declarated "using" or "typedef" must have suffix _t.
* Pointers and references should have suffix "Ptr" or "Ref" depended.
* Template types should have prefix "_".

* * *


### Comments

Every function, class and variable must have description(Comments). It contains 3 sections:

* @brief  : Full and simple description of target object(class or function).
* @param  : Description of argument. Describes type of this variable and main purpose.
* @return : Descruption of return param. Describes type of it and it's format.

Not every object can contain full comment. For example, classes can only contain @brief sectina, while functions contain full comment

* * *


### Log output

Logging must follow certain rules. There are 2 types:

* Info : Contains statistic info such numbers with title + ":" symbol + number
* Dev : Contains detailed information about something in a string format. This provides a header + "~>" + statement
    * ex. |info   | function(line of file) | ChocolataApp ~> ChocolataSlicer version : 0.1.1
    * ex. |debug  | function(line of file) | Window config loaded : assets/config/windowSettings.json | time : 0.110004

* * *