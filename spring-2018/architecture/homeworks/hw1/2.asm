; eax: return value

mov eax, 0;
mov ecx, 0;
iterate:
	cmp ecx, 6
	jge stopIter

	add eax,ecx;
	add ecx,1;
	jmp iterate;
stopIter:

ret;
