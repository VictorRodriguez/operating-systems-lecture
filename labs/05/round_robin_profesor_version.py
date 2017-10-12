
#
# Round Robin calculator
#
# Simulate the Round Robin mechanism based on a queue of processes 
# Print the Avg turn around time
# 
# Please improve so it can be used since command line and plotted 
#
# process = [] might be a random list of elapsed times 
#
# Experiment with this and make 3D graphs for:
#   
#   avg_turn_time vs quantum vs max process size
#
#   context_switch vs  quantum vs max process size
#

quantum = 4
context_switch = 2
execution_time = 0
avg_turnaround_tm = 0.0
context_switchs = 0

processes =[2,3,4,12,8,5,6,1]
num_processes = len(processes)

for process in processes:
    if process <= quantum:
        print("process executed")
        execution_time+=process
        print("execution time " + str(execution_time))
    else:
        print("process interrupted")
        remain_time = process - quantum
        context_switchs+=1
        print("time process executed: "+ str(quantum))
        execution_time+=quantum
        execution_time+=context_switch
        print("execution time " + str(execution_time))
        processes.append(remain_time)

    print processes
    print

avg_turnaround_tm = float(execution_time)/float(num_processes)
print ("Number of processes : " + str(num_processes))
print ("Number of context switch : " + str(context_switchs))
print ("Avg turn around time : " + str(avg_turnaround_tm))
