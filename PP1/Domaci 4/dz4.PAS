program domaci_4(input, output, ulaz, izlaz);

Const naslovmax = 50;
	  portalmax = 20;
	  brclmax = 255;

Type internet = record
					naslov : string;
					portal : string;
					h, m, s : integer;
				END;
	 izdanje = record
	 			naslov, portalPrvi, portalPoslednji : string;
	 			hPrvi, mPrvi, sPrvi, hPosl, mPosl, sPosl : integer;
	 		   end;
Var
	ulIme, izlIme : string;
	korektan : Boolean;

function citajImena(var ulIme, izlIme : string) : Boolean;
BEGIN

	writeln(output, 'unesite ime ulazne datotke');
	readln(input, ulIme);
	writeln(output, 'unesite ime izlazne datoteke');
	readln(input, izlIme);
	citajImena := true;
	if ((ulIme = '') OR (izlIme = '')) then
		citajImena := false;
END;

procedure extractStr(s : string; var i : integer; var sRet : string);
var duz, k : integer;
BEGIN
	duz := 0;
	k := i;
	while (s[i] <> ' ') DO BEGIN
		sRet[i - k + 1] := s[i];
		INC(i);
		INC(duz);
	END;
	sRet[0] := chr(duz);
	INC(i);
END;

procedure extractNum(s : string; var i : integer; var iRet : integer);
BEGIN
	iRet := 0;
	while ((s[i] >= '0') AND (s[i] <= '9')) DO BEGIN
		iRet := iRet * 10 + ord(s[i]) - ord('0');
		INC(i);
	END;
	INC(i);
END;

function uporediVr(h1, m1, s1, h2, m2, s2 : integer) : Boolean;
BEGIN
	uporediVr := false;
	if (h1 > h2) OR ((h1 = h2) AND (m1 > m2)) OR ((h1 = h2) AND (m1 = m2) AND (s1 > s2)) then
		uporediVr := true;
END;

procedure readInternet(var x : internet; var s : string);
var j : integer;
BEGIN
	j := 1;
	extractStr(s, j, x.naslov);
	extractStr(s, j, x.portal);
	extractNum(s, j, x.h);
	extractNum(s, j, x.m);
	extractNum(s, j, x.s);
END;

procedure intToIzd(x : internet; var y : izdanje);

BEGIN
	with y do BEGIN
		naslov := x.naslov;
		portalPrvi := x.portal;
		portalPoslednji := x.portal;
		hPrvi := x.h; mPrvi := x.m; sPrvi := x.s;
		hPosl := x.h; mPosl := x.m; sPosl := x.s;
	END;
END;

procedure obrada(ulIme, izlIme : string);
var ulaz, izlaz : text;
	cur: internet;
	tmpIzd : izdanje;
	s : string;
BEGIN	
	assign(ulaz, ulIme);
	reset(ulaz);
	assign(izlaz, izlIme);
	rewrite(izlaz);
	if NOT(eof(ulaz)) then BEGIN
		readln(ulaz, s);
		readInternet(cur, s);
		intToIzd(cur, tmpIzd);
		while NOT eof(ulaz) DO BEGIN
			readln(ulaz, s);
			readInternet(cur, s);
			if (cur.naslov = tmpIzd.naslov) then BEGIN
				if uporediVr(cur.h, cur.m, cur.s, tmpIzd.hPosl, tmpIzd.mPosl, tmpIzd.sPosl) then
					with tmpIzd do BEGIN
						portalPoslednji := cur.portal;
						hPosl := cur.h; mPosl := cur.m; sPosl := cur.s;
					END
				else if uporediVr(tmpIzd.hPrvi, tmpIzd.mPrvi, tmpIzd.sPrvi, cur.h, cur.m, cur.s) then
					with tmpIzd do BEGIN
						portalPrvi := cur.portal;
						hPrvi := cur.h; mPrvi := cur.m; sPrvi := cur.s;
					END;
			END
			else  BEGIN
					with tmpIzd do
						writeln(izlaz, naslov, ' ', portalPrvi, ' ', portalPoslednji);
					intToIzd(cur, tmpIzd);
			END
		END;
		with tmpIzd do
			writeln(izlaz, naslov, ' ', portalPrvi, ' ', portalPoslednji);
	END;
	close(izlaz);
	close(ulaz);
END;

BEGIN
	korektan := citajImena(ulIme, izlIme);
	while (korektan) DO BEGIN
		obrada(ulIme, izlIme);
		korektan := citajImena(ulIme, izlIme);
	END;
END.
