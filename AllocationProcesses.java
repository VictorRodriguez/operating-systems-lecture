public class AllocationProcesses{

    static void allocateProcesses(int blockSize[], int processSize[]){
        int allocation[] = new int[processSize.length];

        for (int i = 0; i < allocation.length; i++)
            allocation[i] = -1;

        for (int i=0; i<processSize.length; i++){
            for (int j=0; j<blockSize.length; j++){
                if (blockSize[j] >= processSize[i]){
                    allocation[i] = j;
                    blockSize[j] -= processSize[i];
                    break;
                }
            }
        }

        System.out.println("\nProcess No.\tProcess Size\tBlock no.");
        for (int i = 0; i < processSize.length; i++){
            System.out.print("   " + (i+1) + "\t\t" + processSize[i] + "\t\t");
            if (allocation[i] != -1)
                System.out.print(allocation[i] + 1);
            else
                System.out.print("Not Allocated");
            System.out.println();
        }
    }

    public static void main(String[] args)
    {
         int blockSize[] = {200, 300, 400, 100, 600};
         int processSize[] = {452, 389, 101, 403};

         allocateProcesses(blockSize, processSize);
    }
}
