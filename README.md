# nsortdisplay
An NCurses-Based Display for Sorting Algorithms

# Purpose
  The purpose of this program is to provide a terminal-compatible visual display of different sorting algorithims; including their general function, speed, and so on. This will be done through NCurses.

# List of Sorting Algorithims
  - Bubble Sort
  - Quick Sort
  
# Usage
  To compile the program, simply run the command ``make`` in the directory which you've cloned the repository.
  Then, after opening the binary, follow the onscreen instructions.

# Credits
  Special thanks goes to Ubuntu Hideout user *DWD (Daniel) - The Danfather* for pointing out several issues in Alpha 0.1.x and Alpha 0.2.x. All changes from 0.1.1 to 0.2.1 were suggested by him. Another huge thanks to Ubuntu Hideout user *Xen* for helping me understand the pointer black-magic that is working with arguments and pThreads. Without those two, this wouldn't have been possible.

# Changelog
  *Beta 1.0.0* (August 24th, 2022)
  - Finally added sorting comparisons through ``ncomp();``.
  - Added sorting algorithms; Bubble Sort in ``bubble.c``, and Quick Sort in ``quick.c``.
  
  *Alpha 0.2.1* (August 19th, 2022)
  - Fixed an error in ``menu.c`` where the function ``inputcheck();`` would produce an error due to unused arguments. Error was fixed by removing the arguments wholesale.
  - Converted the nanoseconds in ``delaysel.c`` to milliseconds (For display only, as they need to be in nanoseconds to function properly with the rest of the program.) as to provide an easier experience for the end user.
  - Corrected the position of the "_ Comparisons per Second" in ``delaysel.c`` as to be symmetrical to the milliseconds display.
  
  *Alpha 0.2.0* (August 18th, 2022)
  - ``makefile`` no longer has the ``-w`` flag, which I thought was for extra warnings. Now, it has ``-Werror`` which forces compiles to address errors.
  - Date in the function ``menu();`` has been corrected from displaying ``/21`` to ``/22``, properly reflecting the year.
  - The function ``inputcheck();`` in ``menu.c`` now returns ``0`` to avoid an error. Hopefully this doesn't cause issues.
  - ``algolsel.c`` now includes ``pthread.h`` as to avoid an error.
  - The menu for selecting sorting algorithms in ``algolsel();`` has been updated to use ``A_REVERSE`` on entries that have already been selected.
  - Printing within ``delaysel();`` has been changed to provide the user with more information, and has corrected the unit symbol(?) for nanoseconds.

  *Alpha 0.1.1* (August 17th, 2022)
  - Added ``makefile`` to the repository after accidentally forgetting it.
  - Changed numbering system of versions to three-digit versions to reflect potential minor changes.
  - Shifted various elements in ``menu();`` to the right.
  
  *Alpha 0.1.0* (August 17th, 2022)
  - Added a macro for a "main menu" (``menu();``/``menu.c``), selection of algorithm (``algolsel();``/``algolsel.c``), and setting the delay (``delaysel();``/``delaysel.c``). All can be found in ``menu.h``.
