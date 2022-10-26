
/**
 
  Name: CHOW Hau Cheung Jasper
  ITSC Email address: hcjchow@connect.ust.hk

  If I am a student taking this course for the first time, I declare that:
   - I do not copy from other's students' code 
   
  If I am a student retaking this course, I declare that: 
   - I work on this project based on the requirements this semester
   - I do not copy from other's students' code

  TODO: Clearly explain your implementation in point form. 
  For example:
    Step 1.0: Iterate through each line in the input text file. Strip the newline character from that line. (this is start of loop). If we finish reading all the lines, go to step 2.
    Step 1.1: Ignore all lines whose first character is '#'
    Step 1.2: Declare a char array of length 'len' called 'first_block' and another char array of length 'len' called 'second_block'
    Step 1.3: Define 'reading_matrix_row_count'=0. Determine whether the text to be read is a regular input line (reading_matrix=0) or a matrix line (reading_matrix>0). If the former, go to step 1.3.1. Else go to step 1.3.3.
        Step 1.3.1: Read the type of the input and store the input type in 'first_block' and its corresponding value in 'second_block'. For instance if the line being read is "algorithm = safety" then 'first_block'="algorithm", 'second_block'="safety"
        Step 1.3.2: compare the contents of 'first_block' aka the input type, to the predefined input types (eg KEYWORD_ALOGRITHM). There are FOUR types of inputs:
		Step 1.3.2.1: the input is an integer (eg 'num_process'=n, 'num_resource'=m, or 'request_process_id'=q.) Store the read integer in its corresponding integer variable. Go to step 1.0.
		Step 1.3.2.2: the input is a string (eg 'algorithm', 'strategy'). Store the read string in its corresponding char array variable. Go to step 1.0.
		Step 1.3.2.3: the input is a vector (eg 'request_vector', 'available_vector').
			Step 1.3.2.3.1: Let k=0. Read integer in 'second_block' and store that integer in the kth index of the corresponding vector.
			Step 1.3.2.3.2: Look for the next integer and increment k by 1 then go to step 1.3.2.3.1. If no integers left to be read, go to step 1.0.
		Step 1.3.2.4: the input is the precursor to a matrix ie the line is ("allocation_matrix = " OR "max_matrix = "). Then set reading_matrix=1 if the former and reading_matrix=2 for the latter. Go to step 1.0.
	Step 1.3.3: We know the input is a list of numbers separated by whitespace. So just read each number and save it in the corresponding matrix's (reading_matrix_row_count+1)'th row. For example if reading_matrix=2 and reading_matrix_row_count = 2 we read those values into the 3rd row (index 2) of the max_matrix. If reading_matrix_row_count reaches n (number of processes), set reading_matrix_row_count to 0 and reading_matrix to 0 (we are done reading the matrix.) Go to step 1.0.
    Step 2: compute 'need_matrix' = 'max_matrix' - 'allocation_matrix'
    Step 3: initialise 'finish_vector' to be all 0s and vector in R^n
    Step 3: print the inputs. Also print 'need_matrix' and 'finish_vector' if algorithm is resource request type
    Step 4: if algorithm is resource request, go to step 4.1. Else go to step 5.
        Step 4.1: add 'request_vector' to qth row of 'allocation_matrix'
	Step 4.2: check if all elements of request less than all elements of qth row of need matrix. If no, raise type 1 error and return. Else go to step 4.3
	Step 4.3: subtract 'request_vector' from qth row of 'need_matrix'. check if all elements of request less than all elements of work vector. If no, raise type 2 error and return. Else go to step 4.4.
	Step 4.4: set 'work_vector' in R^m to be 'work_vector' - 'request_vector'. go to step 5.
    Step 5: print 'Banker's algo execution', 'Step 0', 'work_vector', 'finish_vector'
    Step 6: Conduct Banker's algorithm. Explained below.

    
    
    Banker's algorithm explanation (Step 6)
    Step 1: Declare 'seq' aka execution order vector to be a vector of 0s in R^n
    Step 2: declare integer 'can_grant'=0. At the end of the inner loop, if can_grant=0, it means system is unsafe/request cannot be processed.
    Step 3: start with 'stepcount'=0. For every 'stepcount' value in {0,1,...,n-1}, iterate:
        Step 3.1: set int found = 0. If =1, denotes whether we have found a process whose need vector is less than or equal to the work vector. Also set 'can_grant'=0.
        Step 3.2: start with i=0. For every i<n, iterate:
            Step 3.2.1: if strategy is smallest index, set u=i. Else set u=n-1-i (for largest index first)
            Step 3.2.2: check if every element of uth row of need is less than 'available_vector' (if yes return 1 else return 0), and store result in variable 'found'
            Step 3.2.3: if 'found'==1 AND finish[u]==0, set finish[u] to 1 and add uth row of allocation to the work vector (because process u can be allocated). set 'can_grant' to 1 and update seq[stepcount]=process u and exit loop; ie go to next iteration of Step 3.
            Step 3.2.4: if 'found'==0, increment i and go back to step 3.2. However if i==n go to step 3.3.
        Step 3.3: if 'can_grant'==0, means we tried all processes and none of them can have resources allocated to them successfully. Then exit both the inner and outer loop. If 'can_grant'==1 go to step 3.4.
        Step 3.4: if 'can_grant'==1, print the work and finish vectors at the current step, increment 'stepcount' and go back to Step 3. However if stepcount==n go to step 4.
    Step 4: If 'can_grant'==0 then at some step, no processes can be allocated resources successfully. show result is a failure (depending on which algorithm was used, text output varies slightly) and exit banker's algorithm. If 'can_grant'==1 go to step 5 instead.
    Step 5: If 'can_grant'==1, means at each step, there exists a process which can be allocated resources while keeping system in safe state. Print that the output is successful (varies slightly depending on which algorithm was used.) Exit Banker's algorithm.
    
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define the MAX_RESOURCE and MAX_PROCESS
#define MAX_RESOURCE 10
#define MAX_PROCESS 10

// Assume that we only need to support 2 types of space characters: 
// " " (space), "\t" (tab)
#define SPACE_CHARS " \t"

// Keywords (to be used when parsing the input and print_parsed_values)
#define KEYWORD_ALOGRITHM "algorithm"
#define KEYWORD_STRATEGY "strategy"
#define KEYWORD_NUM_RESOURCE "num_resource"
#define KEYWORD_NUM_PROCESS "num_process"
#define KEYWORD_AVAILABLE_VECTOR "available_vector"
#define KEYWORD_ALLOCATION_MATRIX "allocation_matrix"
#define KEYWORD_MAX_MATRIX "max_matrix"
#define KEYWORD_REQUEST_VECTOR "request_vector"
#define KEYWORD_REQUEST_PROCESS_ID "request_process_id"

// Keywords (to be used in print_parsed_values and the final result)
#define KEYWORD_NEED_MATRIX "need_matrix"
#define KEYWORD_FINISH_VECTOR "finish_vector"
#define KEYWORD_WORK_VECTOR "work_vector"
#define KEYWORD_EXECUTION_ORDER "execution_order"


// Valid algorithms
#define ALGO_SAFETY "Safety"
#define ALGO_RR "Resource-Request"

// Valid strategies
#define STRATEGY_SMALLEST_INDEX "smallest-index"
#define STRATEGY_LARGEST_INDEX "largest-index"


// Useful string template used in printf()
// We will use diff program to auto-grade the PA2 submissions
// Please use the following templates in printf to avoid formatting errors
//
// Examples:
//
//   printf(template_step_i, 0)    # print === Step 0 ===\n on the screen
//   printf(template_safety_safe)  # print The system is safe\n on the screen

const char template_banker_result[] = "=== Banker's algorithm result ===\n";
const char template_step_i[] = "=== Step %d ===\n";
const char template_safety_safe[] = "The system is safe\n";
const char template_safety_not_safe[] = "The system is not safe\n";
const char template_rr_error_1[] = "Error case 1: request <= need_%d failed\n";
const char template_rr_error_2[] = "Error case 2: request <= available\n";
const char template_rr_can_grant[] = "CAN be immediately granted to process %d\n";
const char template_rr_cannot_grant[] = "CANNOT be immediately granted to process %d\n";

// Global variables:
// For simplicity, 
// Let's make everything static without any dynamic memory allocation
// In other words, we don't need to use malloc()/free() in PA2
// It will save you lots of time to debug if everything is static

char algorithm[100] = ""; // valid algorithm: ALGO_SAFETY or ALGO_RR
char strategy[100] = ""; // valid strategy: 
int num_resource = 0; // m
int num_process = 0; // n
int alloc[MAX_PROCESS][MAX_RESOURCE]={0}; // n x m
int max[MAX_PROCESS][MAX_RESOURCE]={0}; // n x m
int need[MAX_PROCESS][MAX_RESOURCE]={0}; // n x m
int work[MAX_RESOURCE]={0}; // m vector (i.e. the available_vector at the beginning)
int finish[MAX_PROCESS]={0}; // n vector
int seq[MAX_PROCESS]={0}; // n vector, the final execution order
int req_process_id = -1; // used in "Resource-Request" algorithm
int request[MAX_RESOURCE]={0}; // m vector, used in "Resource-Request" algorithm


// Function prototypes 
void print_parsed_values(); // Given and Implemented: No need to make any changes
void parse_input(); // TODO: Implement the input file handling 
void solve_banker_algorithm(); // TODO: Implement the banker's algorithm  


// Two helper print functions
// print a vector
// Example: 
// print_vec("work", work, num_resource);
void print_vec(char *name, int vec[MAX_RESOURCE], int n);

// print a matrix - it maybe useful for you to debug
void print_mat(char *name, int mat[MAX_PROCESS][MAX_RESOURCE], int num_process, int num_resource);

// The main function: Given and Implemented: No need to make any changes
int main() {
    parse_input(); // parse the input and store the values to the global variables
    printf("=== Banker's algorithm input values ===\n");
    print_parsed_values(); // print the parsed values
    printf("=== Banker's algorithm execution ===\n");
    solve_banker_algorithm(); // solve the problem using the banker's algorithm
    return 0;
}

void parse_input() {
    FILE *fp = stdin;
    char *line = NULL;
    ssize_t nread;
    size_t len = 0;
  
    // DECLARATION START
    int reading_matrix = 0; // =0 if not reading matrix, =1 if reading allocation matrix, =2 if reading max matrix
    int reading_matrix_row_count = 0; // =i if reading ith row of a matrix
    // DECLARATION END

    while ( (nread = getline(&line, &len, fp)) != -1 ) {

        line = strtok(line,"\n"); // remove the \n character at the end
        if ( line == NULL )
            continue; // ignore empty lines
      
        // IMPLEMENTATION START
      
        // skip hashtag lines
        if (line[0]=='#'){
            continue;
        }
        
        char first_block[len];
        char second_block[len];
        // if not reading a matrix, separate all valid lines into first_block (string), then " = ", then a string consisting of any character but newline
        if (reading_matrix > 0){
            int pos = 0;
            int total_pos = 0;
            int j = 0;
            // read a row of alloc
            if (reading_matrix==1){
                while (1 == sscanf(line + total_pos, "%d%n", &alloc[reading_matrix_row_count][j], &pos)){
                    total_pos += pos;
                    j += 1;
                }
            }
            // read a row of max
            else if (reading_matrix==2){
                while (1 == sscanf(line + total_pos, "%d%n", &max[reading_matrix_row_count][j], &pos)){
                    total_pos += pos;
                    j += 1;
                }
            }
            reading_matrix_row_count += 1;
            if (reading_matrix_row_count == num_process){ // if done reading matrix, set row count back to 0
                reading_matrix = 0;
                reading_matrix_row_count = 0;
            }
        }
        else{
            sscanf(line, "%s = %[^\n]", first_block, second_block);
            if (strcmp(first_block, KEYWORD_ALOGRITHM)==0){
                sscanf(line, "%s = %s", first_block, algorithm);
            }
            else if (strcmp(first_block, KEYWORD_STRATEGY)==0){
                sscanf(line, "%s = %s", first_block, strategy);
            }
            else if (strcmp(first_block, KEYWORD_NUM_RESOURCE)==0){
                sscanf(line, "%s = %d", first_block, &num_resource);
            }
            else if (strcmp(first_block, KEYWORD_NUM_PROCESS)==0){
                sscanf(line, "%s = %d", first_block, &num_process);
            }
            else if (strcmp(first_block, KEYWORD_REQUEST_PROCESS_ID)==0){
                sscanf(line, "%s = %d", first_block, &req_process_id);
            }
            else if (strcmp(first_block, KEYWORD_AVAILABLE_VECTOR)==0){
                int pos = 0;
                int total_pos = 0;
                int index_count = 0;
                //printf("%s\n", second_block);

                // read the char * 'second_block' to get the first integer and store it in 0th index of 'work' vector
                // then increment 'total_pos' to 'second_block' to read the next integer and store it in next index of 'work' vector, and repeat
                while (1 == sscanf(second_block + total_pos, "%d%n", &work[index_count], &pos)){
                    total_pos += pos;
                    index_count += 1;
                }
            }
            else if (strcmp(first_block, KEYWORD_REQUEST_VECTOR)==0){
                int pos = 0;
                int total_pos = 0;
                int index_count = 0;
                while (1 == sscanf(second_block + total_pos, "%d%n", &request[index_count], &pos)){
                    total_pos += pos;
                    index_count += 1;
                }
            }
            else if (strcmp(first_block, KEYWORD_ALLOCATION_MATRIX)==0){
                reading_matrix = 1;
            }
            else if (strcmp(first_block, KEYWORD_MAX_MATRIX)==0){
                reading_matrix = 2;
            }
        }
    }
}

// helper function. Given two vectors a and b in R^m:
// if the jth element of a is less than or equal to the jth element of b for all j in {0,...,m-1} then return 1;
// else return 0
int checks_less_than(int a[], int b[]){
    for (int j=0; j<num_resource; j++){
        if (a[j] > b[j]){
            return 0;
        }
    }
    return 1;
}


void solve_banker_algorithm() {
    if (strcmp(algorithm, ALGO_RR)==0){
        // alloc[q] += request
        for (int i=0; i<num_resource; i++){
            alloc[req_process_id][i] += request[i];
        }
        // check for type 1 error
        if (checks_less_than(request, need[req_process_id])==1){
            for (int i=0; i<num_resource; i++){
                need[req_process_id][i] -= request[i];
            }
        }
        else{
            printf(template_rr_error_1, req_process_id); return;
        }
        // check for type 2 error
        if (checks_less_than(request, work)==1){
            for (int i=0; i<num_resource; i++){
                work[i] -= request[i];
            }
        }
        else{
            printf(template_rr_error_2); return;
        }
    }
    printf(template_step_i, 0);
    print_vec(KEYWORD_WORK_VECTOR, work, num_resource);
    print_vec(KEYWORD_FINISH_VECTOR, finish, num_process);

    int can_grant = 0; // if =0 by the end of an inner loop, means no process could be allocated its request resources
    for (int stepcount=0; stepcount < num_process; stepcount++){
        int found = 0;
        can_grant = 0; // reset whenever we look for a new resource
        for (int i=0; i<num_process; i++){
            int u;
            if (strcmp(strategy, STRATEGY_SMALLEST_INDEX)==0){
                u = i;
            }
            else{
                u = num_process-1-i;
            }
            found = checks_less_than(need[u], work);
            if (found==1 && finish[u]==0){ // if need[u] less than or equal to work and vector hasn't been finished
                finish[u] = 1;
                // available_vector += uth row of allocation matrix
                for (int j=0; j<num_resource; j++){
                    work[j] = work[j] + alloc[u][j];
                }
                seq[stepcount] = u;
                can_grant = 1;
                break;
            }
        }
        if (can_grant==1){// if we did find a valid process, print the resultant work and finish vector at that step
            printf(template_step_i, stepcount+1);
            print_vec(KEYWORD_WORK_VECTOR, work, num_resource);
            print_vec(KEYWORD_FINISH_VECTOR, finish, num_process);
        }
        // if no process can be allocated its requested resources
        if (can_grant==0){break;}
    }
    printf(template_banker_result);

    // Show your banker's algorithm result here
    if (can_grant==0){
        if (strcmp(algorithm, ALGO_RR)==0){
            print_vec(KEYWORD_REQUEST_VECTOR, request, num_resource);
            printf(template_rr_cannot_grant, req_process_id);
            printf("%s = []\n", KEYWORD_EXECUTION_ORDER);
        }else{
            printf(template_safety_not_safe);
            printf("%s = []\n", KEYWORD_EXECUTION_ORDER);
        }
    }
    else{
        if (strcmp(algorithm, ALGO_RR)==0){
            print_vec(KEYWORD_REQUEST_VECTOR, request, num_resource);
            printf(template_rr_can_grant, req_process_id);
            print_vec(KEYWORD_EXECUTION_ORDER, seq, num_process);
        }
        else{
            printf(template_safety_safe);
            print_vec(KEYWORD_EXECUTION_ORDER, seq, num_process);
        }
    }
}

void print_mat(char *name, int mat[MAX_PROCESS][MAX_RESOURCE], int num_process, int num_resource) {
    int i,j;
    printf("%s = [\n", name);
    for (j=0;j<num_process;j++) {
        for (i=0;i<num_resource;i++) {
            printf("%d", mat[j][i]);
            if ( i<num_resource-1 )
                printf(",");
        }
        printf("\n");
    }
    printf("]\n");
}

void print_vec(char *name, int vec[MAX_RESOURCE], int n) {
    int i;
    printf("%s = [", name);
    for (i=0;i<n;i++) {
        printf("%d", vec[i]);
        if ( i<n-1 )
            printf(",");
    }
    printf("]\n");
}

void print_parsed_values() {
    int i, j;
    printf("%s = %s\n", KEYWORD_ALOGRITHM, algorithm);
    printf("%s = %s\n", KEYWORD_STRATEGY, strategy);
    printf("%s = %d\n", KEYWORD_NUM_PROCESS, num_process);
    printf("%s = %d\n", KEYWORD_NUM_RESOURCE, num_resource);
    print_vec(KEYWORD_AVAILABLE_VECTOR, work, num_resource);
    print_mat(KEYWORD_ALLOCATION_MATRIX, alloc, num_process, num_resource);
    print_mat(KEYWORD_MAX_MATRIX, max, num_process, num_resource);
    for (j=0;j<num_process;j++) 
        for (i=0;i<num_resource;i++) 
            need[j][i] = max[j][i] - alloc[j][i];

    print_mat(KEYWORD_NEED_MATRIX, need, num_process, num_resource);
    for (i=0;i<num_process;i++) {
        finish[i] = 0;
        seq[i] = -1;
    }
    print_vec(KEYWORD_FINISH_VECTOR, finish, num_process);
    if ( strcmp(algorithm, ALGO_RR )==0  ) {
        printf("%s = %d\n", KEYWORD_REQUEST_PROCESS_ID, req_process_id);
        print_vec(KEYWORD_REQUEST_VECTOR, request, num_resource);
    }
}
