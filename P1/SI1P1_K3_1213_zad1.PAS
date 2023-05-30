
program zad2(input, output);

type ptNode = ^node;
	 node = record
	 	value : integer;
	 	next : ptNode;
	 END;

VAR prvi, posl, ptTmp, i, j, ptCur : ptNode;
	tmp : integer;

procedure ispis(prvi : ptNode);
BEGIN
	while (prvi <> NIL) DO BEGIN
		writeln(prvi^.value, '->');
		prvi := prvi^.next;
	END;
END;

BEGIN
	prvi := NIL; posl := NIL;
	while (NOT (EOLN(input))) DO BEGIN
		new(ptTmp);
		read(ptTmp^.value);
		ptTmp^.next := NIL;
		if (prvi = NIL) then BEGIN
			prvi := ptTmp;
			posl := ptTmp
		END
		else BEGIN 
			posl^.next := ptTmp;
			posl := ptTmp;
		END
	END;
	i := prvi;
	while (i <> NIL) DO BEGIN
		j := i^.next;
		WHILE (j <> NIL) DO BEGIN
			if (i^.value < j^.value) then BEGIN
				tmp := i^.value;
				i^.value := j^.value;
				j^.value := tmp;
			END;
      j := j^.next;
    END;
    i := i^.next;
	END;
	ptCur := prvi;
	if (ptCur = NIL) then
		writeln('niste uneli elemente')
	else BEGIN
		while (ptCur^.next <> NIL) DO
			if (ptCur^.value = ptCur^.next^.value) then BEGIN
				ptTmp := ptCur^.next;
				ptCur^.next := ptCur^.next^.next;
				dispose(ptTmp);
			END
			else ptCur := ptCur^.next;
	END;
	while (prvi <> NIL) DO BEGIN
		write(prvi^.value, ' ');
		ptTmp := prvi;
		prvi := prvi^.next;
		dispose(ptTmp);
	END;
END.
