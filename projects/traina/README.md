#Your onid folder should contain a readme file that contains your name and your onid
# Aleita Herrera-Train 
## ONID: TRAINA


### Running Game 

Use the following command to initialize game. 

	$ make playdom 

Followed by 

	$./playdom <int 1 - 30>


### Cleaning files

	$ make clean

### Running Test Suite 


First run the code to load and run a game to make sure all code is available to the test suite. 
	
	$ make playdom 
	$ ./playdom <int>

Then run the following command to prepare all tests to be ran. 

	$ make unitTests

Now you can open the output file from the command line to which the results of the test have been output. 

