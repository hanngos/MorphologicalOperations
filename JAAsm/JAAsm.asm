;Przekszta�cenia morfologiczne obrazu
;Go�ciniak Hanna
;Informatyka SSI 5 sem. 2020 / 21

;Program wykonuje wybrane operacje morfologiczne(erozj�, dylatacje, otwarcie lub zamkni�cie) na obrazach typu bmp.
;Po pobraniu nazwy obrazu podanej przez u�ytkownika oraz poprawnym odczytaniu danych wykonywane s� nast�puj�ce kroki :
;1. �binaryzacja�, czyli zamiana pikseli RGB na warto�� 0 lub 1,
;2. dodanie ramki do obrazu(skopiowanie brzeg�w oraz rog�w),
;3. wykonanie jednej z operacji morfologicznych, kt�re polega na sprawdzaniu w p�tli s�siedztwa ka�dego z pikseli i zwr�ceniu odpowiedniej warto�ci do tablicy wynikowej,
;4.��debinaryzacja� � zamiana warto�ci z tablicy wynikowej na RGB oraz
;5. zapis do pliku bmp.

.DATA

DIVISOR DD 3.0

.CODE

;void asmbinarization(BYTE * binary, int width, int height, BYTE * BMPData);
;Funkcja wykonujaca "binaryzacje", czyli zamiana pikseli RGB na warto�� 0 lub 1.
;RCX - BYTE * binary � wska�nik na zbinaryzowan� tablic� obrazu, kt�ra zostanie wype�niona zerami i jedynkami
;RDX - int width � szeroko�� obrazu, wykorzystana w p�tli oraz przy wyliczaniu indeks�w tablic
;R8 - int height � wysoko�� obrazu, wykorzystana w p�tli
;R9 - BYTE* BMPData � wska�nik na tablic� danych RGB, z kt�rej zostaj� pobrane odpowiednie warto�ci RGB kolejnych pikseli
asmbinarization PROC
	push rax
	push rbx
	push r10
	push r11
	push r12
	push r13
	push r14

	;int w = ((width * 3 + 3) & (-4));
	xor r10, r10
	mov r10, rdx ;r10 = width
	imul r10, 3 ;width * 3
	add r10, 3 ;width * 3 + 3
	and r10, -4 ;r10 = w

	xor r11, r11
	mov r11, r8 ;r11 = height
	dec r8 ;r8 = height--
	xor r11, r11
	dec r11
	xor r12, r12
	dec r12
	dec rdx ;rdx = width--

	xor ebx, ebx

H: ;for (int i = 0; i < height; i++)
	inc r11 ;r11 = i	
	W: ;for (int j = 0; j < width; j++)
		inc r12 ;r12 = j
		xor eax, eax

		;(BMPData[(i * w) + j * 3] + BMPData[(i * w) + j * 3 + 1] + BMPData[(i * w) + j * 3 + 2])) / 3 >= 129
		mov r13, r11 ;i
		imul r13, r10 ;i * w
		mov r14, r12 ;j
		imul r14, 3 ;j * 3
		add r14, r13 ;(i * w) + j * 3

		mov al, [r9 + r14] ;zapisanie B do rejestru xmm0
		movd xmm0, eax
		mov al, [r9 + r14 + 1] ;zapisanie G do rejestru xmm1
		movd xmm1, eax
		mov al, [r9 + r14 + 2] ;zapisanie R do rejestru xmm2
		movd xmm2, eax

		;zsumowanie sk�adowych piksla
		paddd xmm0, xmm1 ;B + G
		paddd xmm0, xmm2 ;R + G + B

		;podzielenie sumy R + G + B przez 3.0
		cvtdq2ps xmm0, xmm0
		movups xmm1, [DIVISOR]
		divps xmm0, xmm1 ;(R + G + B)/3
		
		cvtss2si eax, xmm0
		cmp eax, 129 ;sprawdzenie czy wynik obliczenia jest wi�kszy lub r�wny 129
		jge Zero ;je�li jest wi�kszy lub r�wny to skok to Zero bl = 0
		mov bl, 1 ;je�li nie to bl = 1
	
	Back:
		mov r15, rdx ;width - 1
		inc r15 ;width
		imul r15, r11 ;i * width
		add r15, r12 ;(i * width) + j
		mov [rcx + r15], bl ;binary[i * width + (j + l)] - zapisanie 0 lub 1 w odpowiednim miejscu w tablicy wynikowej

		cmp r12, rdx
		jne W ;je�li rejestry nie s� r�wne to skok to pocz�tku p�tli W

	xor r12, r12
	dec r12
	cmp r11, r8
	jne H ;je�li rejestry nie s� r�wne to skok do pocz�tku p�tli H
	jmp EndProc

Zero:
	mov bl, 0
	jmp Back

EndProc:
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop rbx
	pop rax

    ret 
asmbinarization ENDP


;void asmAddFrame(BYTE* binary, int width, int height, BYTE * withFrame)
;Funkcja dodaj�ca ramk� do obrazu(skopiowanie brzeg�w, rog�w oraz ca�ej tablicy binary).
;RCX - BYTE* binary - wska�nik na zbinaryzowan� tablic� obrazu b�d�c� �r�d�em, z kt�rego kopiowane s� dane do tablicy wynikowej withFrame
;RDX - int width - szeroko�� obrazu, wykorzystana w p�tli oraz przy wyliczaniu indeks�w tablic
;R8 - int height - wysoko�� obrazu, wykorzystana w p�tli oraz przy wyliczaniu indeks�w tablic
;R9 - BYTE* withFrame - wska�nik na tablic� wynikow� (obraz z ramk�)
asmAddFrame PROC
	push rcx
	push r8
	push r9
	push rdx
	xor rax, rax
	mov rax, rcx ;rax = binary
	xor rcx, rcx
	mov rcx, rdx ;width
	xor r10, r10
	mov r10, rcx ;width
	mov bl, 8

;p�tle kopiuj�ce �rodek (obraz bez ramki)
H:
	dec r8 ;i
	W:
		mov rdx, r10 ;w
		imul rdx, r8 ;w * i
		dec rcx ;j 
		add rdx, rcx ;(w * i) + j
		mov bl, [rax + rdx] ;bl = binary[(w * i) + j]
		inc rcx ;j + 1
		mov rdx, r10 ;w
		add rdx, 2 ;w + 2
		inc r8 ;i + 1
		imul rdx, r8 ; (w + 2) * (i + 1)
		dec r8 ;i
		add rdx, rcx
		mov [r9 + rdx], bl ;withFrame[(w + 2) * (i + 1) + j + 1] = bl
		loop W 
	mov rcx, r10
	cmp r8, 0
	jne H

	pop rdx ;rdx = width
	xor rcx, rcx
	mov rcx, rdx; rcx = width
	pop r9 ;r9 = withFrame
	pop r8 ;r8 = height
	push r8
	push r9
	push rcx
	mov rbx, r8 ;rbx = h
	inc r8 ;h + 1
	add rdx, 2 ;w + 2
	imul r8, rdx ;(h + 1) * (w + 2)
	dec rbx ;h - 1
	mov rdx, rcx ;rdx = w
	imul rdx, rbx ;(h - 1) * w
	add rdx, rax 
	add r8, r9

;p�tla kopiuj�ca g�rn� i doln� kraw�d�
W2:
	mov bl, [rax + rcx - 1] ;bl = binary[i]
	mov [r9 + rcx], bl ;withFrame[i + 1] = bl
	mov bl, [rdx + rcx - 1] ;bl = binary[(height - 1) * width + i]
	mov [r8 + rcx], bl ;withFrame[(height + 1) * (width + 2) + 1 + i] = bl
	loop W2

	pop rdx ;rdx = width
	pop r9 ;r9 = withFrame
	pop rcx ;rcx = height
	push rcx
	push r9
	push rdx
	add rcx, 2 ;height + 2
	add rdx, 2 ;width + 2
	mov r10, rdx

;p�tla kopiuj�ca prawy i lewy bok
H2:
	mov rax, r10
	mul rcx
	mov bl, [r9 + rax - 2] ;bl = withFrame[(width + 2) * (i + 1) - 2]
	mov [r9 + rax - 1], bl ;withFrame[(width + 2) * (i + 1) - 1] = bl
	mov rdx, r10
	dec rcx
	imul rdx, rcx
	mov bl, [r9 + rdx + 1] ;bl = withFrame[(width + 2) * i + 1];
	mov [r9 + rdx], bl ;withFrame[(width + 2) * i] = bl
	inc rcx
	loop H2

EndProc:
	pop rdx
	pop r9
	pop r8
	pop rcx
    ret 
asmAddFrame ENDP

;BYTE asmDilationCheckNeighbourhood(BYTE* b, int x, int w)
;Funkcja sprawdzaj�ca s�siedztwo danego punktu x i w zale�no�ci od wyniku zwracaj�ca odpowiedni� warto�� (0 lub 1)
;RCX - BYTE* b - withFrame - wska�nik na tablic� zbinaryzowan� z dodan� ramk�, w kt�rej b�dzie sprawdzane otoczenie piksela
;RDX - int x - punkt centralny, wok� kt�rego b�dzie sprawdzane s�siedztwo
;R8 - int w - szeroko�� obrazu z ramk� (szeroko�� obrazu + 2)
;RAX - zwracany BYTE - 0 lub 1
asmDilationCheckNeighbourhood PROC
	push rbx
	xor rbx, rbx
	xor rax, rax
	mov rax, rdx ; x
	sub rax, r8 ; x - w
	mov bl, [rcx + rax] ;zapisanie zawarto�ci withFrame[x - w] do bl
	cmp bl, 1 ;sprawdzenie czy bl jest r�wne 1
	je NotZero ;je�li jest to skok do NotZero, je�li nie to wyst�puje sprawdzenie kolejnego s�siada
	dec rax ; x - w - 1
	mov bl, [rcx + rax]
	cmp bl, 1
	je NotZero
	add rax, 2 ; x - w + 1
	mov bl, [rcx + rax]
	cmp bl, 1
	je NotZero
	add rax, r8 ; x + 1
	mov bl, [rcx + rax]
	cmp bl, 1
	je NotZero
	sub rax, 2 ; x - 1
	mov bl, [rcx + rax]
	cmp bl, 1
	je NotZero
	add rax, r8 ; x + w - 1
	mov bl, [rcx + rax]
	cmp bl, 1
	je NotZero
	inc rax ; x + w
	mov bl, [rcx + rax]
	cmp bl, 1
	je NotZero
	inc rax ; x + w + 1
	mov bl, [rcx + rax]
	cmp bl, 1
	je NotZero
	mov rax, 0 ;je�li �aden z s�siad�w nie by� jedynk�, punkt centralny jest zerem
	jmp EndProc
NotZero:
	mov rax, 1 ;je�li kt�ry� z s�siad�w by� jedynk�, punkt centralny te� ni� jest
EndProc:
	pop rbx
    ret 
asmDilationCheckNeighbourhood ENDP


;BYTE asmErosionCheckNeighbourhood(BYTE* b, int x, int w);
;Funkcja sprawdzaj�ca s�siedztwo danego punktu x i w zale�no�ci od wyniku zwracaj�ca odpowiedni� warto�� (0 lub 1)
;RCX - BYTE* b - withFrame - wska�nik na tablic� zbinaryzowan� z dodan� ramk�, w kt�rej b�dzie sprawdzane otoczenie piksela
;RDX - int x - punkt centralny, wok� kt�rego b�dzie sprawdzane s�siedztwo
;R8 - int w - szeroko�� obrazu z ramk� (szeroko�� obrazu + 2)
;RAX - zwracany BYTE - 0 lub 1
asmErosionCheckNeighbourhood PROC
	push rbx
	xor rbx, rbx
	xor rax, rax
	mov rax, rdx ; x
	sub rax, r8 ; x - w
	mov bl, [rcx + rax] ;zapisanie zawarto�ci withFrame[x - w] do bl
	cmp bl, 1  ;sprawdzenie czy bl jest r�wne 1
	jne Zero ;je�li jest to skok do Zero, je�li nie to wyst�puje sprawdzenie kolejnego s�siada
	dec rax ; x - w - 1
	mov bl, [rcx + rax]
	cmp bl, 1
	jne Zero
	add rax, 2 ; x - w + 1
	mov bl, [rcx + rax]
	cmp bl, 1
	jne Zero
	add rax, r8 ; x + 1
	mov bl, [rcx + rax]
	cmp bl, 1
	jne Zero
	sub rax, 2 ; x - 1
	mov bl, [rcx + rax]
	cmp bl, 1
	jne Zero
	add rax, r8 ; x + w - 1
	mov bl, [rcx + rax]
	cmp bl, 1
	jne Zero
	inc rax ; x + w
	mov bl, [rcx + rax]
	cmp bl, 1
	jne Zero
	inc rax ; x + w + 1
	mov bl, [rcx + rax]
	cmp bl, 1
	jne Zero
	mov rax, 1 ;je�li wszyscy s�siedzi byli jedynkami, punkt centralny te� ni� jest
	jmp EndProc
Zero:
	mov rax, 0 ;je�li kt�ry� z s�siad�w nie by� jedynk�, punkt centralny jest zerem
EndProc:
	pop rbx
    ret 
asmErosionCheckNeighbourhood ENDP

END