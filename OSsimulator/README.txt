Wei Shi's CSCI340 README:

	
			1. Open terminal. 
			2. Enter into the directory with this README.txt file and Makefile. 
			3. Type make clean(to delete old object files) just in case.
			2. Type make all.
			3. The executable will be ~/temp/run.me

			Input file: None

NOTE:

			1. Memory is compacted after every termination and an eligible process from pool is selected.
			2. Process and device IDs start at 1!
			3. Cylinders start at 0!
			4. Uninitialized processes have PID 0!
			   Therefore if a Segment has belongs to a "process" with PID 0, it is a hole.
			5. Used process IDs are not recycled!

