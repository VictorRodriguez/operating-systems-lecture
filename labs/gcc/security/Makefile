all:
	gcc vuln.c -o vuln -m32 -O0	
	gcc vuln.c -o vuln-cet -m32 -O0	-fcf-protection 
	gcc vuln-variable.c -o vuln-variable -m32 -O0	
first-rop:
	gcc -m32 -fno-stack-protector first_rop.c -o first_rop
first-rop-test:
	echo "Launching attack. You should get a new shell."
	python rop_attack.py
clean:
	rm -rf vuln
	rm -rf vuln-cet
	rm -rf vuln-variable
	rm -rf first_rop
	rm -rf a.out

