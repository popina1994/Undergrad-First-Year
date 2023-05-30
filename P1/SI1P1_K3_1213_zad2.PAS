program zad2(input, output);

const imeUlazneDatoteke = 'studenti.txt';

Type
	 ptCvorStudent = ^cvorStudent;
	 cvorStudent = record
		ime, prezime : string;
		prOcena : real;
    next : ptCvorStudent;
	end;

VAR prvi : ptCvorStudent;
	prOcena : real;

procedure extractStr(strS : string; var i : integer; var strNew : string);
var duz, len : integer;
BEGIN
	duz := 0;
	len := ord(strS[0]);
	while (i <= len) AND (strS[i] <> ' ') DO BEGIN
		INC(duz);
		strNew[duz] := strS[i];
		INC(i);
	END;
	strNew[0] := chr(duz);
	INC(i);
END;

procedure extractNum(strS : string; var i : integer; var nNew : integer);
var len : integer;
BEGIN
	len := ord(strS[0]);
	nNew := 0;
	while (i <= len) AND (strS[i] <> ' ') DO BEGIN
		nNew := 10 * nNew + ord(strS[i]) -ord('0');
		INC(i);
	END;
	INC(i);
END;

procedure dodajNaKraj(var prvi, posl : ptCvorStudent; strIme, strPrezime : string; prOcena : real);
var tmpCvorStudent : ptCvorStudent;
BEGIN
	new(tmpCvorStudent);
	tmpCvorStudent^.ime := strIme;
	tmpCvorStudent^.prezime := strPrezime;
	tmpCvorStudent^.prOcena := prOcena;
	tmpCvorStudent^.next := NIL;
	if (prvi = NIL) then BEGIN
		prvi := tmpCvorStudent;
		posl := prvi;
	END
	else BEGIN
		posl^.next :=tmpCvorStudent;
		posl := posl^.next;
	END;
END;


procedure ulaz(var prvi : ptCvorStudent);
var posl : ptCvorStudent;
	ulaz : text;
	strS, strIme, strPrezime : string;
	len, ocena, brOcena, i : integer;
	prOcena : real;
BEGIN
	prvi := NIL;
	posl := NIL;
	assign(ulaz, imeUlazneDatoteke);
	reset(ulaz);
	while NOT (eof (ulaz)) DO BEGIN
		readln(ulaz, strS);
		i := 1;
    len := ord(strS[0]);
		extractStr(strS, i, strIme);
		extractStr(strS, i, strPrezime);
		prOcena := 0;
		brOcena := 0;
		while (i <= len) DO BEGIN
			extractNum(strS, i, ocena);
			INC(brOcena);
			prOcena := prOcena + ocena;
		END;
		prOcena := prOcena / brOcena;
		dodajNaKraj(prvi, posl, strIme, strPrezime, prOcena);
	END;
	close(ulaz);
END;

function srednjaVr(prvi : ptCvorStudent) : real;
var  brOcena : integer;
BEGIN
	srednjaVr := 0;
  brOcena := 0;
	while (prvi <> NIL) DO BEGIN
		srednjaVr := srednjaVr + prvi^.prOcena;
		INC(brOcena);
		prvi := prvi^.next;
	END;
  if (brOcena <> 0) then
    srednjaVr := srednjaVr / brOcena;
END;

procedure ispis(prvi : ptCvorStudent; prOcena : real);
BEGIN
	while (prvi <> NIL) DO BEGIN
		if (prvi^.prOcena > prOcena) then
		with prvi^ do
			writeln('ime: ', ime, prezime, prOcena );
    prvi := prvi^.next;
	END;
END;

procedure dealociraj(var prvi : ptCvorStudent);
var tmpCvorStudent : ptCvorStudent;
BEGIN
	while (prvi <> NIL) DO BEGIN
		tmpCvorStudent := prvi;
		prvi := prvi^.next;
		dispose(tmpCvorStudent);
	END;
END;

BEGIN
	ulaz(prvi);
	prOcena := srednjaVr(prvi);
	ispis(prvi, prOcena);
	dealociraj(prvi);
END.
