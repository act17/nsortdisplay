# nsortdisplay
An NCurses-Based Display for Sorting Algorithms
Version: Beta 1.2.1 (August 31st, 2022)

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

# Checklist for Next Release
  The following should be all completed by Beta 2.0.0:
  
  - ``menu.c``'s "PRESS ANY KEY TO START" should be moved to a pThread as to ensure that the user will not have to wait a period of time before the next screen renders. *Finished in Beta 1.1.0.*
  
  - Controls should be added to the bottom of the screen with ``algolsel();`` and ``delaysel();`` *Finished in Beta 1.1.0.*

  - Option to add a custom delay with ``delaysel();`` *Finished in Beta 1.2.0.*

  - Option to enter a custom array to sort, or have one be randomised on the spot. Should be in a new function - ``arraysel();``.

  - Increase number of elements of the array from 10 to 22. The width of the area in ``ncomp();`` that elements are displayed upon is 90-units wide. That means that, keeping the 4-unit width of the element windows, there can be up to 22 element windows - assuming there's a 1-unit wide space between ``lborder`` and ``rborder``. *Finished in Beta 1.2.0. Actual elements were only increased by 8.*

  - Have there be an updated-live tracker for the comparisons made by the sorting algorithms, and there being a timer that shows elapsed time to the user in ``ncomp();``.

  - Make a way for the program to know when the sorting is done, and have the program subsequently stop the comparisons and allow the user to exit the program. *Added in Beta 1.3.0.*

  - ``wrefresh();``s in the entirety of the program should be ordered in a manner that avoids the "blinking space" being within general eyeshot. Perhaps calling ``wrefresh(stdscr);`` would be the solution.

# Changelog
  *Beta 1.3.0* (September 2nd, 2022)
  - Added (likely very ineffecient) method of seeing if all elements in the array are sorted, and subsequently preparing the program to terminate.
  - Removed unnessicary, and somehow unnoticed ``printw();`` in ``bubble.c`` used for diagnostic purposes.
  
  *Beta 1.2.1* (August 31st, 2022)
  - Formatted all ``*.c`` files with ``clang-format``.
  - Added line to state version, and date of version release in ``README.md``.
  - Layed the foundation for a new function - ``arraysel();``. Added ``arraysel.c``, ``void arraysel();`` to ``menu.h``, and added a new argument to ``ncomp();``, that being the ``int*`` ``array``. There's currently no function for ``arraysel();``, so there's no use of it in the program currently. ``int array[18]`` is called in the function ``main();``.
  
  *Beta 1.2.0* (August 31st, 2022)
  - Added new option to enter a custom delay in ``delaysel();``.
  - Increased the number of array elements from 10 to 18. Altered ``bubblewrap();`` and ``quickwrap();`` to reflect this change. Size of the array-element display window has been significantly increased.
  
  *Beta 1.1.0* (August 29th, 2022)
  - Altered ``menu.c``'s "PRESS ANY KEY TO START" message to permit entering input as soon as possible.
  - Added controls to ``algolsel();`` and ``delaysel();``.
  - Added bold-print to ``menu.c``, ``algolsel.c``, and ``delaysel.c``'s various interfaces to improve visual appearance.
  - Added a checklist for the next release.
  
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
