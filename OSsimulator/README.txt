Wei Shi's simple terminal-based OS simulator README:

	
			1. Open terminal. 
			2. Enter into the directory with this README.txt file and Makefile. 
			3. Type make clean(to delete old object files) just in case.
			2. Type make all.
			3. The executable will be ~/temp/run.me

			Input file: None

NOTE:

			1. Process and device IDs start at 1!
			2. Cylinders start at 0!
			3. Uninitialized processes have PID 0!
			   Therefore if a Segment has belongs to a "process" with PID 0, it is a hole.
			4. Used process IDs are not recycled!
			5. Disk scheduling uses CLOOK algorithm.
			6. CPU scheduling is round robin.
			7. Memory management through segmentation.
			
			
COMMANDS:

			S- Enter snapshot mode
				m- print memory
				p- print printer queue
				d- print disk queue
				c- print CD/RW queue
				r- print ready queue
				
			A- Add new process
			T- End current CPU time slice
			t- Terminate current running process
			

