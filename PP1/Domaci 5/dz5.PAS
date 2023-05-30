program dz5Pom(input, output, ulaz, izlaz);

Const maxNum = 1000;
	 brojRez = 3;
	 minInt = -32768;

Type mobilni = record
	 	oznaka : string;
	 	rez : array [1 .. 3] of real;
	 	cena : real;
	 end;

	 mob = record
	 	oznaka : string;
	 	ocena : real;
	 end;

	 ptNode = ^node;
	 node = record
	 		value : mob;
	 		next : ptNode;
	 	end;
	 niz = array [1 .. brojRez + 1] of mob;

Var ulIme, izlIme : string;
	lista : ptNode;
	oMin, oMax : real;


procedure IspisListe(prvi : ptNode);
BEGIN
	while (prvi <> nil) do BEGIN
		writeln(prvi^.value.oznaka, '->');
		prvi := prvi^.next;
	END;
END;

procedure IspisElement(x : mob);
BEGIN
	writeln(x.oznaka, ' ', x.ocena : 10 : 2);
END;

procedure DodajElement(var m : mob; var prvi : ptNode);
var novi, tr : ptNode;
BEGIN
	new(novi);
	novi^.value := m;
	novi^.next := NIL;
	if (prvi = NIL) then
		prvi := novi
	else BEGIN
			tr := prvi;
			while (tr^.next <> NIL) do
				tr := tr^.next;
			tr^.next := novi;
	END;
END;

procedure ObrisiElement(ptElement : ptNode; var prvi : ptNode);
var tmpPt, curPt : ptNode;
BEGIN
	if (ptElement = prvi) then	BEGIN
		prvi := prvi^.next;
		dispose(ptElement);
	END
	else BEGIN 							{Oprezno sa uslovom, sta ako unese curPt = nil}
		new(curPt);
		curPt := prvi;
		while curPt^.next <> ptElement DO
			curPt := curPt^.next;
		new(tmpPt);
		tmpPt := curPt^.next;
		curPt^.next := tmpPt^.next;
		dispose(tmpPt);
	END;
END;

procedure MobileToMob(var tmpMobile : mobilni; var tmpMob : mob);
var avg : real;
	i : integer;
BEGIN
	tmpMob.oznaka := tmpMobile.oznaka;
	avg := 0;
	for i := 1 to brojRez do
		avg := avg + tmpMobile.rez[i];
	avg := avg / brojRez;
	tmpMob.ocena := tmpMobile.cena / avg;
END;


procedure Ulaz(ulIme : string; var prvi : ptNode);
var ulaz : file of mobilni;
	tmpMobile : mobilni;
	tmpMob : mob;
BEGIN
	prvi := NIL;
	assign(ulaz, ulIme);
	reset(ulaz);
	while NOT(eof(ulaz)) DO BEGIN
		read(ulaz, tmpMobile);
		MobileToMob(tmpMobile, tmpMob);
		dodajElement(tmpMob, prvi);
	END;
	close(ulaz);
END;

procedure Obrada(var prvi : ptNode; oMin, oMax : real);
var curPt, tmpPt : ptNode;
BEGIN
	new(curPt);
	curPt := prvi;
	while (curPt <> NIL) DO BEGIN
		tmpPt := curPt^.next;
		if (curPt^.value.ocena > oMax) OR (curPt^.value.ocena < oMin) then
			ObrisiElement(curPt, prvi);
		curPt := tmpPt;
	END;
END;

procedure Swap(var x, y : mob);
var tmp : mob;
BEGIN
	tmp := x;
	x := y;
	y := tmp;
END;

procedure MemSet(var x : niz; n : integer; val : real);
var i : integer;
BEGIN
	for i := 1 to n do BEGIN
	 x[i].oznaka := '';
	 x[i].ocena := val;
	END
END;


procedure InsertionSort(var x : niz; n : integer; val : mob);
var i : integer;
BEGIN
	i := n - 1;
	x[n] := val;
	while (i > 0)  AND (x[i].ocena < x[i + 1].ocena) DO BEGIN
		Swap(x[i], x[i + 1]);
		DEC(i);
	END;
END;

procedure Izlaz(izlIme : string; prvi : ptNode);
var count : integer;
	x : niz;
  	izlDat : text;
  	i : integer;
BEGIN
	MemSet(x, brojRez + 1, minInt);
	assign(izldat, izlIme);
	rewrite(izldat);
	while (prvi <> NIL) DO BEGIN
		InsertionSort(x, brojRez + 1, prvi^.value);
		prvi := prvi^.next;
		DEC(count);
	END;
	for i := 1 to brojRez do
		if (x[i].oznaka <> '') then
			writeln(izlDat, x[i].oznaka);
	close(izlDat);
END;

procedure obrisiListu(var prvi : ptNode);
var tmpPt : ptNode;
BEGIN
	while (prvi <> NIL) DO BEGIN
		tmpPt := prvi;
		prvi := prvi^.next;
		dispose(tmpPt);
	END;
END;

Begin
	writeln('unesite ime ulazne datoteke');
	readln(ulIme);
	writeln('unesite ime izlazne datoteke');
	readln(izlIme);
	while (ulIme <> '') AND (izlIme <> '') DO BEGIN
			writeln('unesite omin i omax');
			readln(oMin, oMax);
			ulaz(ulIme, lista);
			Obrada(lista, oMin, oMax);
			Izlaz(izlIme, lista);
			ObrisiListu(lista);
			writeln('unesite ime ulazne datoteke');
			readln(ulIme);
			writeln('unesite ime izlazne datoteke');
			readln(izlIme);
	END;
end.
