# Minotaurs
compilation steps
`g++ -o p1 Problem1.cpp -lpthread`
`./p1`
`g++ -o p2 Problem2.cpp -lpthread`
`./p2`

## Problem 1

### run-down

In this program, multithreading, randomness, and a mutex were used to simulate a group of guests navigating a labyrinth to get a cupcake. Functions were defined to check whether the cupcake is available and whether each guest has picked it up, and to allow each guest to navigate the labyrinth and pick up the cupcake if it is available. The program used a mutex for thread safety and measured its duration using std::chrono.

### Implementation

The program defines NUM_GUESTS as the number of guests who will navigate the labyrinth, a mutex mutex for thread safety, and three integer variables: currentCount to track the number of guests who have entered the labyrinth, current_guest to track the current guest being considered, and generateRandomNumber to generate random delays.

The program defines checkCupcake to check whether the cupcake is available and whether the current guest has picked it up, and navigateLabyrinth to allow each guest to navigate the labyrinth and pick up the cupcake if it is available.

The program uses std::array to store whether each guest has picked up the cupcake, std::thread to create threads for each guest and for checking the cupcake, and std::chrono to measure the program's duration.

The program creates a thread for checkCupcake and an array of threads for navigateLabyrinth for each guest, with a 1 second delay between each thread start. The program loops until all guests have entered the labyrinth, at which point the threads join.

## Problem 2
### run-down

In this program, multithreading, randomness, and a mutex were used to simulate a Minotaur showing his favorite crystal vase to guests in a dedicated showroom with a single door. Functions were defined to encapsulate the code for viewing the vase, allowing guests to enter the showroom, and simulating guests setting a sign on the door. The program used random delays and a mutex for thread safety.

### explenation
I chose solution 2, it seems most logical to me because you can view the state of the vase room in comparison to 1. And 3 seems to have a flaw where you a state with no empty queue results in the state of the vase room being lost. I suppose you can peek for 1 and 3 but that isn't explicitly stated.

### Methods
The program defines MAX_GUESTS as the maximum number of guests who can view the vase, a mutex mtx for thread safety, and an integer variable num_viewed to track the number of guests who have viewed the vase.

The program defines view_vase to encapsulate the code for viewing the vase, enter_showroom to allow guests to enter the showroom, and set_showroom_status to simulate guests setting a sign on the door indicating when the showroom is available.

The program uses std::random_device, std::mt19937, and std::uniform_int_distribution from the <random> header to generate random delays.

The program creates a thread for set_showroom_status and an array of threads for enter_showroom for each guest, with a 1 second delay between each thread start.

After all guests have viewed the vase, the threads join.
