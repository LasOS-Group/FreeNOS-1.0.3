/*
 * Copyright (C) 2009 Niek Linnenbank
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <ProcessManager.h>
#include <Process.h>
#include <sys/wait.h>
#include "Wait.h"

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Wait for the process to terminate");
    parser().registerPositional("PID", "Wait for the process with the given process id to terminate then continue with the other processes!");
}

Wait::~Wait()
{
}

Wait::Result Wait::exec()
{
    //declaring a variable of type proecss id 
    pid_t processID;
    int status;
    bool inputValidation = false; 
    pid_t waited; 
    //saving the process id input by the user  
    processID =atoi(arguments().get("PID"));
    
    //check the process ids available and if it matches to the input process id 
    for (ProcessID pid = 0; pid < ProcessClient::MaximumProcesses; pid++)
    {
        if(pid == processID)
        {
            inputValidation = true; 
            //call the waitpid to wait and pass in the process id 
            //WAIT NOW 
            waited = waitpid(processID, &status, 0); 
            break; 
        }
    }
    
    //the process id is not valid 
    if(!inputValidation)
    {
        ERROR("Invalid Process ID '" << arguments().get("PID") << "'"); 
        return InvalidArgument; 
    }
    //could not wait 
    else if(processID != waited)
    {
        ERROR("Failed to sleep: " << strerror(errno));
        return IOError;
    }
   
    //DONE 
    return Success; 
}
