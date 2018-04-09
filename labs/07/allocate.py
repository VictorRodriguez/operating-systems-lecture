from random import *

def populate(procesos, max):
	pro=[]
	for element in range(0,procesos):
		pro.append(randint(1,max))
	return pro

dic={}
def allocate(procesos):
	process=procesos
	biggest=0
	for key,element in dic.items():
		for num in element:
			if(num>biggest):
				biggest=num

	for position in range(0	,len(procesos)):
		lastPosition=0
		for key,element in dic.items():
			for num in element:
				if(num>lastPosition):
					lastPosition=num
		if(procesos[position]%10==0 and (position+1 not in dic)):
			dic[position+1]=[lastPosition,lastPosition+procesos[position]]
		elif(procesos[position]%10!=0 and (position+1 not in dic)):
			size=0
			for num in range(0,10):
				if((procesos[position]+num)%10==0):
					size=procesos[position]+num
			dic[position+1]=[lastPosition,lastPosition+size]
		elif(procesos[position]%10==0 and (position+1 in dic)):
			lista=dic[position+1]
			if(lista[0]==0 and lista[1]==0):	
				dic[position+1]=[biggest,biggest+procesos[position]]
		elif(procesos[position]%10!=0 and (position+1 in dic)):
			size=0
			lista=dic[position+1]
			if(lista[0]==0 and lista[1]==0):		
				for num in range(0,10):
					if((procesos[position]+num)%10==0):
						size=procesos[position]+num
				dic[position+1]=[biggest,biggest+size]

	print("Tamaño de los 4 procesos:")
	print(procesos)
	print("Acomodo de procesos y su rango de memoria")
	print(dic)
	return(dic)

	print("Tamaño de los 4 procesos:")
	print(procesos)
	print("Acomodo de procesos y su rango de memoria")
	print(dic2)
	return(dic2)

def eliminarProceso(numProceso,dicc, lista):
	lista[numProceso-1]=0
	dicc[numProceso]=[0,0]
	print("Después de haber eliminado:")
	print(dicc)
	return(lista, dicc)

listaProcesos=populate(4,100)
diccionario=allocate(listaProcesos)
dic=diccionario

print("Escoge un proceso a eliminar: 1,2,3,4")
toDelete=int(input(""))

newProcesos, cosaLista=eliminarProceso(toDelete,diccionario,listaProcesos)

print("¿Agregar nuevo proceso? 1 para si, o 0 para no")
newProcess=int(input(""))
if(newProcess==1):
	print("Nombre del nuevo proceso: "+str(toDelete))
	tamaño=(randint(1,100))
	newProcesos[toDelete-1]=tamaño
	allocate(newProcesos)
print("Terminado")