Instructions


1) Install Ubuntu in bare metal system (latest version of ubuntu if possible)

2) inside Ubuntu follow this instructions to install phoronix 

    https://wiki.ubuntu.com/PhoronixTestSuite

3) Make sure that it works correctly: 

    phoronix-test-suite list-available-tests

    This should list the available tests 

    
4) Run this one: 
   
   phoronix-test-suite benchmark pts/x264

5) Modify the kernel

    *) Check the value of the kernel :

        # sysctl -a | grep vm.swappiness
            vm.swappiness = 60
    
    *) Re run the benchmark:
        
        # phoronix-test-suite run aio-stress

        AIO-Stress 0.21:
            pts/aio-stress-1.1.1 [Test: Random Write]
            Test 1 of 1
            Estimated Trial Run Count:    3
            Estimated Time To Completion: 3 Minutes (09:36 CDT)
                Started Run 1 @ 09:34:07
                Started Run 2 @ 09:34:14
                Started Run 3 @ 09:34:21  [Std. Dev: 4.12%]
                Started Run 4 @ 09:34:28  [Std. Dev: 3.51%]
                Started Run 5 @ 09:34:35  [Std. Dev: 3.05%]

            Test Results:
                3268.66
                3028
                3238.29
                3245.94
                3214.95

            Average: 3199.17 MB/s


        3) Modify the parameter under analysis:
        sysctl -w vm.swappiness=40

    4) Verify the change in performance :

    AIO-Stress 0.21:
        pts/aio-stress-1.1.1 [Test: Random Write]
        Test 1 of 1
        Estimated Trial Run Count:    3
        Estimated Time To Completion: 2 Minutes (09:41 CDT)
            Started Run 1 @ 09:40:17
            Started Run 2 @ 09:40:25
            Started Run 3 @ 09:40:32  [Std. Dev: 0.61%]

        Test Results:
            3274.36
            3246.05
            3235.91

        Average: 3252.11 MB/s


    IMPORTANT

    The values we are going to change are 

    Kernel 

        kernel.sched_latency_ns
        kernel.sched_migration_cost_ns
        kernel.sched_min_granularity_ns
        kernel.sched_nr_migrate
        kernel.sched_rr_timeslice_ms
        kernel.sched_rt_period_us
        kernel.sched_rt_runtime_us
        kernel.sched_schedstats 
        kernel.sched_shares_window_ns
        kernel.sched_time_avg_ms
        kernel.sched_tunable_scaling
        kernel.sched_wakeup_granularity_ns
    
    Memory

        vm.swappiness

    More info here: 
    
    https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/6/html/Performance_Tuning_Guide/s-cpu-scheduler.html
    http://fizyka.umk.pl/~jkob/prace-mag/cfs-tuning.pdf 
    https://doc.opensuse.org/documentation/html/openSUSE_121/opensuse-tuning/cha.tuning.taskscheduler.html
    https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/6/html/Performance_Tuning_Guide/s-memory-tunables.html
