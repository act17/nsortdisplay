# nsortdisplay
An NCurses-Based Display for Sorting Algorithms

# Purpose
  The purpose of this program is to provide a terminal-compatible visual display of different sorting algorithims; including their general function, speed, and so on. This will be done through NCurses.
  The current version is Alpha 0.1. This means that there's no actual comparing being done; this is rather a stage used to diagnose and potential problems with the configuration steps to the program's operation.

# List of Sorting Algorithims
  Not applicable.
  
# Usage
  To compile the program, simply run the command ``make`` in the directory which you've cloned the repository.
  So far, there is no other usage besides setting three integers through the NCurses menu that the program provides. These three integers will be printed after all of them are set.
# Credits

# Changelog
  *Alpha 0.1.1* (August 17th, 2022)
  - Added ``makefile`` to the repository after accidentally forgetting it.
  - Changed numbering system of versions to three-digit versions to reflect potential minor changes.
  - Shifted various elements in ``menu();`` to the right.
  
  *Alpha 0.1.0* (August 17th, 2022)
  - Added a macro for a "main menu" (``menu();``/``menu.c``), selection of algorithm (``algolsel();``/``algolsel.c``), and setting the delay (``delaysel();``/``delaysel.c``). All can be found in ``menu.h``.
