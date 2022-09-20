# nsortdisplay
An NCurses-Based Display for Sorting Algorithms
Version: Beta 2.1.0 (September 12th, 2022)

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
  The following should be all completed by Release Candidate 1.0.0:

  - Fix the stack smashing that occurs for some reason. *May have been fixed in Beta 2.1.0.*

  - Correct error where the array used by the program, for some reason, has a zero in it. *Fixed in Beta 2.1.0.*

  - Add entry-redundancy protection (As in, you cannot select a previously selected entry.) in ``arraysel();``. *Added in Beta 2.1.0.*

  - Ensure that the current method of elapsing time in ``ncomp();`` is correct - perhaps passing a pointer into the Algorithm pThread that is incremented by the pThreaded function would provide superior accuracy.
  
# Changelog
  *Beta 2.1.0* (September 19th, 2022)
  - Rewritten the entirety of ``arraysel();``. It now has an actually functional quasi-random array-filling thing, and now is presentable in function.
  
  *Beta 2.0.2* (September 12th, 2022)
  - Fixed an issue with ``main();``'s required-space-checking routine where the error message informing the user that their screen size is too small would not print. *Thanks to user ``Simon`` on the Doom Emacs Discord for pointing this out.*
  - Fixed error within ``delaysel();`` where the integer ``delay`` could be checked for a value, even though no value was assigned to it. *Thanks to user ``endangered`` on the Doom Emacs Discord for pointing this out.

  *Beta 2.0.1* (September 12th, 2022)
  - Changed the instance of ``mvwprintw();`` on line ``152`` of ``ncomp.c`` from using an ``int`` to an ``unsigned long``.
  
  *Beta 2.0.0* (September 12th, 2022)
  - Added ``arraysel.c`` and ``arraysel();``.
  - Updated ``menu.h`` to include ``arraysel();``.
  - The array the program sorts, ``int array[18]``, is now called in ``main();`` and edited through ``arraysel();``.
  - ``wrefresh(stdscr);`` is now called at the end of all major routines in the program's NCurses department (?).
  
  *Beta 1.4.1* (September 4th, 2022)
  - Placed ``bubble.c``, ``quick.c``, and ``sorts.h`` in a new folder - ``sorts``.
  
  *Beta 1.4.0* (September 4th, 2022)
  - Added diagnostic information, those being a count of the comparisons done and a count of the elapsed time, added to ``ncomp();``.
  - Updated ``bubble.c`` to commit ``1dbdaf8`` of ``https://github.com/act17/sorts``.
  
  *Beta 1.3.0* (September 2nd, 2022)
  - Added (likely very ineffecient) method of seeing if all elements in the array are sorted, and subsequently preparing the program to terminate.
  - Removed unnessicary, and somehow unnoticed ``printw();`` in ``bubble.c`` used for diagnostic purposes.
  - Layed the foundation for a new function - ``arraysel();``. Added ``arraysel.c``, ``void arraysel();`` to ``menu.h``, and added a new argument to ``ncomp();``, that being the ``int*`` ``array``. There's currently no function for ``arraysel();``, so there's no use of it in the program currently. ``int array[18]`` is called in the function ``main();``.
  
  *Beta 1.2.1* (August 31st, 2022)
  - Formatted all ``*.c`` files with ``clang-format``.
  - Added line to state version, and date of version release in ``README.md``.
  
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
