import java.util.Random;
import java.util.Scanner;

public class MemoryManagement {
	
	public static void eraseProcess(int process, int[] memory) {
		for(int i = 0; i < memory.length; i++) {
			if(memory[i] == process) {
				memory[i] = 0;
			}
		}
	}//borra un proceso
	
	public static void allocateProcess(int process, int processLength, int[] memory) {
		int size = processLength;
		for(int i = 0; i < memory.length; i++) {
			if(memory[i] == 0 && size > 0) {
				memory[i] = process;
				size -= 10;
				System.out.println("Process "+process+" allocated in memory segment "+i);
			}
		}
		if(size > 0) {
			eraseProcess(process,memory);//erases what could have been allocated
			System.out.println("Not enough memory for process "+process);
		}
	}//agrega un proceso
	
	public static void main(String[] args) {
		int[] memory = new int[25];
		int[] processes = new int[4];
	    Random randomGenerator = new Random();
	    Scanner input = new Scanner(System.in);

		for(int i = 0; i < processes.length;i++) {
			int processLength = randomGenerator.nextInt(50);
			processes[i] = processLength;
			int processNum = i+1;
			System.out.println("Process "+processNum+" is of size "+processLength);
			allocateProcess(processNum,processLength,memory);
		}//cierra for
		
		System.out.print("Which process do you wish to erase? (1 to 4) ");
		int erase = input.nextInt();
		eraseProcess(erase,memory);
		System.out.print("What is the length of the next process you wish to allocate? ");
		int allocate = input.nextInt();
		allocateProcess(5,allocate,memory);
	}

}
