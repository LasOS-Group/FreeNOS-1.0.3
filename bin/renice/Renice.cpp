/*
 * Copyright (C) 2015 Niek Linnenbank
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

#include <Types.h>
#include <Macros.h>
#include <stdio.h>
#include <unistd.h>
#include <ProcessClient.h>
#include "Renice.h"

Renice::Renice(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Alters the nice value of running process");
    //we should register the flag -n
    parser().registerFlag('n', "renice", "Specifies the number to add to the renice value of the process");

    //save the priority level and process id by registerPositional
    parser().registerPositional("priorityLevel", "save the priority level");
    parser().registerPositional("processID", "save the processID");

}

Renice::~Renice(){}

Renice::Result Renice::exec()
{
    
    //if the flag is inputted 
    if(renice(arguement.get("renice"), priority, ID){
        //create an object of processClient 
        const ProcessClient process;

        //save the processid and prioritylevel inputted into corresponding variables 
        ProcessID pid = arguement.get("processID");
        int priority = arguement.get("priorityLevel");

        //call setPriority to set the priority of the process by passing the process ID and the priority level 

        setPriority(pid, priority);
    }
}
