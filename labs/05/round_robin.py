
# autor: Juan Manuel

# Simulate the Round Robin mechanism based on a queue of processes
# Graph the behavior of avg_turnaround_tms and context_switches
# of a queue of processes with diferent quantum values
#
# process = [] might be a random list of elapsed times

from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
import matplotlib.pyplot as plt

def printInfo():
    print ("Quantums")
    print quantums
    print ("Avg Turnaround times:")
    print avg_turnaround_tms
    print ("Context Switches")
    print context_switches
    print("Initial processes")
    print processes

quantum = input("Enter the initial quantum: ")
quantum_max = input("Enter the final quantum: ")
quantums = []

context_switches = []
avg_turnaround_tms = []
max_process_sizes = []

processes =[2,3,4,12,8,5,6,1]
num_processes = len(processes)

while quantum <= quantum_max:

    processes =[2,3,4,12,8,5,6,1]
    max_process_size = 0
    context_switch = 2
    context_switchs = 0
    execution_time = 0
    avg_turnaround_tm = 0.0

    i = 0
    quantums.append(quantum)

    while i < len(processes):

        if max_process_size < processes[i]:
            max_process_size = processes[i]
            print max_process_size

        if processes[i] <= quantum:
            print("process executed")
            execution_time += processes[i]
            print("execution time " + str(execution_time))
        else:
            print("process interrupted")
            remain_time = processes[i] - quantum
            context_switchs += 1
            print("time process executed: "+ str(quantum))
            execution_time+=quantum
            execution_time+=context_switch
            print("execution time " + str(execution_time))
            processes.append(remain_time)

        print processes
        print
        i += 1

    avg_turnaround_tm = float(execution_time)/float(num_processes)
    avg_turnaround_tms.append(avg_turnaround_tm)
    max_process_sizes.append(max_process_size)
    context_switches.append(context_switchs)
    quantum += 1

printInfo()

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

z = max_process_sizes
y = avg_turnaround_tms
# y = context_switches
x = quantums

ax.plot_trisurf(x, y, z, cmap=cm.jet, linewidth=0.2)

plt.show()
