/* Guillermo Herrera Acosta
 * A01400835 
 * Programa que simula un algoritmo de ordenamiento de memoria basico de una main memory
 */

public class AlgoritmoMemoria {
	
	private Integer bS; //Block space 
	private Integer memoyLength;
	
	public AlgoritmoMemoria(Integer bs, Integer mainMemorySize){
		this.bS=bs;
		this.memoyLength=mainMemorySize;
	}
	public AlgoritmoMemoria() {
		this(10,0xFF);
	}
	
	public void crearProcesos() {
		Integer tPP= this.memoyLength/this.bS; //tamano de bloques en la main memory
		Integer contador=0; //Contador de procesos
		Integer pc=0; //Contador de posiciones de espacios en la main memory
		double randomNum;
		int var;
		System.out.println("El tamano de los bloques es de "+tPP);

		while(pc<=tPP) {
			randomNum= (Math.random()%this.bS*20); //Numero al azar dentro del rango del doble del espacio
			
			if(randomNum<this.bS){
				var=pc+1;
				System.out.println("Proceso No.: "+contador+" ,de tamano: "+randomNum+ " ocupa posicion: "+pc+"-"+var+" de la main memory");
				contador++;
				pc++;
			}else {
				var=pc+2;
				System.out.println("Proceso No.: "+contador+" ,de tamano: "+randomNum+ " ocupa posicion: "+pc+"-"+var+" de la main memory");
				contador++;
				pc+=2;
			}
		}
	}
	
	public static void main(String [] args) {
		AlgoritmoMemoria am= new AlgoritmoMemoria();
		am.crearProcesos();
	}
}

