/**
 
  Name: CHOW, Hau Cheung Jasper 
  ITSC Email address: hcjchow@connect.ust.hk

  TODO: Clearly explain how you implement process_cmd in point form. For example:

    Step 1: detect the correct input pattern of the command - the pattern can be 1 of 6. To do that we implement the find_input_pattern helper function, which searches for special characters <, > and | by checking each character of 'cmdline' one at a time (since at most there can be one of each). If both < and > found and < is found before >, we know it is pattern 4, otherwise pattern 5. If | found, must be pattern 6. If only < found, pattern 2. If only > found, pattern 3. If no <, > or | found, pattern 1.
    Step 2: once we have the appropriate pattern (the value should be an integer in the set {1,...,6}), declare a array of char pointers (each element of array points to first char of a string). This array shall store K commands. First element of the array stores the 1st command, and then the subsequent element(s) store the argument(s) of that 1st command. Then we add a null terminator. Then the next element of the array stores the 2nd command, and then the subsequent element(s) stores the argument of the 2nd command, then add a null terminator. Repeat this procedure until all K commands stored. In our case K=2 since our test cases only require 2 level pipe. We also know the max number of arguments, so the size of this array should be (1+MAX_ARGUMENTS+1)*K
    Step 3: declare flags is_input, is_output. We will need these later for input/output redirection from stdin/stdout
    Step 4: initialise integer array of size K whose ith element shall contain the number of arguments in the ith command
    Step 5: initialise char pointer array of size 3 to store segments of the command. We only need 3 segments despite having K=2 because we cannot have input/output redirection at same time as piping. for example, "cmd < input > output" will yield the segments "cmd", "input", "output" in that order 
    Step 6: initialise integer variable to hold number of segments of the current command
    Step 7: initialise two char pointer arrays to hold the names of the input/output files respectively. The maximum length of these names is given by MAX_SEGMENT_LENGTH
    Step 8: using 'cmdline' (the input from the user), parse the command as follows, depending on which value was returned in Step 1. if value k returned in step 1, go to 'Step 8.k'.
        Step 8.1: call read_tokens to strip all whitespace characters from the command and store the command and its arguments in the array in Step 2. Go to step 9.
        Step 8.2: call read_tokens with delimiter < to separate the 2 segments of the command and store them into the array declared in step 5.
            Step 8.2.1: strip all whitespace characters from the 1st segment of the command and store the stripped command and its arguments in the array in Step 2.
            Step 8.2.2: strip all whitespace characters from the 2nd segment of the command (which contains name of input file) and store it in the char array to hold input file name in Step 7.
            Step 8.2.3: set is_input to 1. Go to step 9.
        Step 8.3: call read_tokens with delimiter > to separate the 2 segments of the command and store them into the array declared in step 5.
            Step 8.3.1: strip all whitespace characters from the 1st segment of the command and store the stripped command and its arguments in the array in Step 2.
            Step 8.3.2: strip all whitespace characters from the 2nd segment of the command (which contains name of output file) and store it in the char array to hold output file name in Step 7.
            Step 8.3.3: set is_output to 1. Go to step 9.
        Step 8.4: call read_tokens with delimiter <> to separate the 3 segments of the command and store them into the array declared in step 5.
            Step 8.4.1: strip all whitespace characters from the 1st segment of the command and store the stripped command and its arguments in the array in Step 2.
            Step 8.4.2: strip all whitespace characters from the 2nd segment of the command (which contains name of input file) and store it in the char array to hold input file name in Step 7.
            Step 8.4.3: strip all whitespace characters from the 3rd segment of the command (which contains name of output file) and store it in the char array to hold output file name in Step 7.
            Step 8.4.4: set both is_input and is_output to 1. Go to step 9.
        Step 8.5: call read_tokens with delimiter <> to separate the 3 segments of the command and store them into the array declared in step 5.
            Step 8.5.1: strip all whitespace characters from the 1st segment of the command and store the stripped command and its arguments in the array in Step 2.
            Step 8.5.2: strip all whitespace characters from the 2nd segment of the command (which contains name of output file) and store it in the char array to hold output file name in Step 7.
            Step 8.5.3: strip all whitespace characters from the 3rd segment of the command (which contains name of input file) and store it in the char array to hold input file name in Step 7.
            Step 8.5.4: set both is_input and is_output to 1. Go to step 9.
        Step 8.6: call read_tokens with delimiter | to separate the 2 segments of the command and store them into the array declared in step 5.
            Step 8.6.1: strip all whitespace characters from the 1st segment of the command and store the stripped command and its arguments in the array in Step 2. Recall that at most this fills half the array.
            Step 8.6.2: strip all whitespace characters from the 2nd segment of the command and store the stripped command and its arguments in the SECOND HALF of the array in Step 2.
            Step 8.6.3: initialise a pipe for interprocess communication
            Step 8.6.4: use fork() to create two processes. The child process will handle the 1st command (step 8.6.1) and the parent will wait for completion of the child process before it executes the 2nd command (step 8.6.2)
                Step 8.6.4.1: Child process needs to close read end of its pipe and open write end of its own pipe (so it may write to the parent process). Then use execvp to execute the command obtained in step 8.6.1. Upon completion, go to step 8.6.4.2.
                Step 8.6.4.2: Parent process needs to close write end of its pipe and open read end of its own pipe (so it may read from the child process). Then use execvp to execute the command obtained in step 8.6.2. Upon completion, exit program.
    Step 9: If the is_input flag declared in Step 3 is equal to 1, redirect the input by closing stdin and replacing it with the input file whose name is in the first array in step 7.
    Step 10: If the is_output flag declared in Step 3 is equal to 1, redirect the output by closing stdout and replacing it with the output file whose name is in the second array in step 7.
    Step 11: The array stored in step 2 should hold a single command. Execute that command with execvp
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h> // For constants that are required in open/read/write syscalls
#include <sys/wait.h> // For wait() - suppress warning messages
#include <fcntl.h> // For open syscall

// Assume that each command line has at most 256 characters (including NULL)
#define MAX_CMDLINE_LEN 256

// Assume that we have at most 16 arguments
#define MAX_ARGUMENTS 16

// Assume that we only need to support 3 types of space characters: 
// " " (space), "\t" (tab), and newline (\n)
#define SPACE_CHARS " \t\n"

// Assume that we only have at most 2 pipe segements, 
// and each segment has at most 256 characters
#define MAX_PIPE_SEGMENTS 2
#define MAX_SEGMENT_LENGTH 256

 
// This function will be invoked by main()
void process_cmd(char *cmdline);

// read_tokens function is given
// This function helps you parse the command line
//
// Suppose the following variables are defined:
//
// char *pipe_segments[MAX_PIPE_SEGMENTS]; // character array buffer to store the pipe segements
// int num_pipe_segments; // an output integer to store the number of pipe segment parsed by this function
// char cmdline[MAX_CMDLINE_LEN]; // The input command line
//
// Sample usage:
//
//  read_tokens(pipe_segments, cmdline, &num_pipe_segments, "|");
// 
void read_tokens(char **argv, char *line, int *numTokens, char *token);


/* The main function implementation */
int main()
{
    char cmdline[MAX_CMDLINE_LEN];
    fgets(cmdline, MAX_CMDLINE_LEN, stdin);
    process_cmd(cmdline);
    return 0;
}

// helper function. Finds the input pattern; it must belong to one of 6 types
// 1. cmd
// 2. cmd < input
// 3. cmd > output
// 4. cmd < input > output
// 5. cmd > output < input
// 6. cmd | cmd2
int find_input_pattern(char *cmdline){

  int retval = 0; // value to return at the end
  int has_input = 0;
  int has_output = 0;
  int input_first = 0; // if this =1 then it corresponds to pattern 4
  int cmdline_len = strlen(cmdline);

  for (int i=0; i<cmdline_len; i++){
    if (cmdline[i]=='<'){
      has_input = 1;
      if (has_output==0){ // if '<' found before '>' then input first is true
        input_first = 1;
      }
    }
    else if (cmdline[i]=='>'){
      has_output = 1;
    }
    else if (cmdline[i]=='|'){
      retval = 6;
      return retval;
    }
  }
  if (has_input && has_output){
    if (input_first){
      retval = 4;
    }
    else{
      retval = 5;
    }
  }
  if (has_input==0 && has_output==0){
    retval = 1;
  }
  if (has_input && has_output==0){
    retval = 2;
  }  
  if (has_input==0 && has_output){
    retval = 3;
  }
  return retval;
}

void process_cmd(char *cmdline)
{
    int input_type = find_input_pattern(cmdline); // call helper function to find out how to parse command
    int is_input = 0; // if set to 1, means input should be redirected
    int is_output = 0; // if set to 1, means output should be redirected

    // declare somewhere to save arguments of the command(s) and the different segments of the command
    // the read_tokens function will also tell us how many arguments/segments there are in the command, so we create two ints to store those values
    // char * stores a string, so since max number of pipe segments is 2, we need 2d array like so:
    char* command_arguments[MAX_PIPE_SEGMENTS*(MAX_ARGUMENTS+2)]; // stores the 1st command (1), and then the arguments of the 1st command (at most MAX_ARGUMENTS), then NULL then the 2nd command, and then the arguments of the 2nd command, then NULL
    int num_arguments[2]; // ith element stores num of arguments in ith command
    char* cmdline_segments[3]; // at maximum there will be 3 'segments' ie (cmd), (output), (input). Not needed in pipe section
    int num_segments;
    // null terminate the relevant parts of the char pointer array (needed for execvp later)
    for (int i=1; i<=MAX_PIPE_SEGMENTS; i++){
      // in this case every 18th char must be null (first 17 are for command, and then 16 arguments)
      command_arguments[i*(MAX_ARGUMENTS+2)-1] = NULL;
    }

    // declare somewhere to save the input and output files
    char input_file[MAX_SEGMENT_LENGTH];
    char output_file[MAX_SEGMENT_LENGTH];

    // note the sscanf function indeed ignores spaces, tab and newline, which is all the characters in SPACE_CHARS according to https://www.ibm.com/docs/en/SSLTBW_2.1.0/com.ibm.zos.v2r1.ccrug00/sscanf.htm
    // therefore no need to do additional work with it

    if (input_type==1){
      // case 1. cmd
      // since no <, > or |, just use space chars as delimiter and we will get all the arguments in the command
      // number of arguments in command will be saved in 'num_arguments' and the arguments of said command saved in 'command_arguments'
      read_tokens(command_arguments, cmdline, &num_arguments[0], SPACE_CHARS);
    }
    else if (input_type==2){
      // case 2. cmd < input
      // established there is only a <. In that case break the 'cmdline' into 2 segments and save them into 'cmdline_segments'
      read_tokens(cmdline_segments, cmdline, &num_segments, "<");
      // cmdline_segments[0] now contains the actual command
      read_tokens(command_arguments, cmdline_segments[0], &num_arguments[0], SPACE_CHARS);
      sscanf(cmdline_segments[1], "%s", input_file);
      is_input = 1; // so we know we need to handle input redir later
    }
    else if (input_type==3){
      // case 3. cmd > output
      // established there is only a >. In that case break the 'cmdline' into 2 segments and save them into 'cmdline_segments'
      read_tokens(cmdline_segments, cmdline, &num_segments, ">");
      // cmdline_segments[0] now contains the actual command
      read_tokens(command_arguments, cmdline_segments[0], &num_arguments[0], SPACE_CHARS);
      sscanf(cmdline_segments[1], "%s", output_file);
      is_output = 1; // so we know we need to handle output redir later
    }
    else if (input_type==4){
      // case 4. cmd < input > output
      // established there is < and >. In that case break the 'cmdline' into 3 segments and save them into 'cmdline_segments'
      read_tokens(cmdline_segments, cmdline, &num_segments, "<>");
      // cmdline_segments[0] now contains the actual command
      read_tokens(command_arguments, cmdline_segments[0], &num_arguments[0], SPACE_CHARS);

      sscanf(cmdline_segments[1], "%s", input_file);
      sscanf(cmdline_segments[2], "%s", output_file);
      is_input = 1; // so we know we need to handle input redir later
      is_output = 1; // so we know we need to handle output redir later
    }
    else if (input_type==5){
      // case 5. cmd > output < input
      // established there is < and >. In that case break the 'cmdline' into 3 segments and save them into 'cmdline_segments'
      read_tokens(cmdline_segments, cmdline, &num_segments, "<>");
      // cmdline_segments[0] now contains the actual command
      read_tokens(command_arguments, cmdline_segments[0], &num_arguments[0], SPACE_CHARS);
      
      sscanf(cmdline_segments[2], "%s", input_file);
      sscanf(cmdline_segments[1], "%s", output_file);
      is_input = 1; // so we know we need to handle input redir later
      is_output = 1; // so we know we need to handle output redir later
    }
    else if (input_type==6){
      // case 6. cmd | cmd2
      // established there is |. In that case break the 'cmdline' into 2 segments and save them into 'cmdline_segments'
      read_tokens(cmdline_segments, cmdline, &num_segments, "|");
      // cmdline_segments[0] now contains command1, cmdline_segments[1] now contains command2
      read_tokens(command_arguments, cmdline_segments[0], &num_arguments[0], SPACE_CHARS);
      int offset = MAX_ARGUMENTS+2; // use this offset to calculate where to start saving the 2nd command (pointer arithmetic)
      read_tokens(command_arguments + offset, cmdline_segments[1], &num_arguments[1], SPACE_CHARS);

      // piping
      int pfds[2];
      pipe(pfds);
      pid_t pid = fork(); // return value of 0 = child, nonzero = parent
      char * this_command[MAX_ARGUMENTS+1]; // do this after fork
      if (pid==0){ // child handles command1
        close(1); // close stdout
        dup2(pfds[1], 1); // make stdout as pipe input
        close(pfds[0]);

        for (int i=0; i<MAX_ARGUMENTS+1; i++){
          this_command[i] = command_arguments[i];
        }
        execvp(this_command[0], this_command);
      } else { // parent process handles command2
        close(0); // close stdin
        dup2(pfds[0], 0); // make stdin as pipe output
        close(pfds[1]); // don't need this

        for (int i=0; i<MAX_ARGUMENTS+1; i++){
          this_command[i] = command_arguments[MAX_ARGUMENTS+2+i];
        }
        wait(0); // wait for the child process to succeed first
        execvp(this_command[0], this_command);
      }
      return;
    }
    else{ // should never reach here
      // ERROR
      exit(-1);
    }
    
    // change where stdin, stdout refer to
    if (is_input==1){
      int fd = open(input_file, O_RDONLY, S_IRUSR | S_IWUSR);
      close(0); // close stdin
      dup2(fd, 0); // replace it with 
    }
    if (is_output==1){
      int fd = open(output_file, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
      close(1); // close stdout
      dup2(fd, 1); // replace it with the file descriptor
    }
    char * this_command[MAX_ARGUMENTS+1]; // use this to save the single command to be executed
    for (int i=0; i<MAX_ARGUMENTS+1; i++){
      this_command[i] = command_arguments[i];
    }
    execvp(this_command[0], this_command);
}

// Implementation of read_tokens function
void read_tokens(char **argv, char *line, int *numTokens, char *delimiter)
{
    int argc = 0;
    char *token = strtok(line, delimiter);
    while (token != NULL)
    {
        argv[argc++] = token;
        token = strtok(NULL, delimiter);
    }
    argv[argc++] = NULL;
    *numTokens = argc - 1;
}