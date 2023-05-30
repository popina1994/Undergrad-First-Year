program zad2(input, output);

const brojSamoglasnika = 5;

type vowelApp = record
			app : integer;
			vowel : char;
		end;
	niz = array [1 .. brojSamoglasnika] of vowelApp;

var strS : string;

procedure extractStr(strS : string; var i : integer; var strNew : string);
var lenS, lenNew : integer;
BEGIN
	lenS := ord(strS[0]);
	lenNew := 0;
	while (i <= lenS) AND (strS[i] <> ' ') DO BEGIN
		INC(lenNew);
		strNew[lenNew] := strS[i];
		INC(i);
	END;
	strNew[0] := chr(lenNew);
END;

procedure memSet(var x : niz; n, val : integer);
var i : integer;
BEGIN
	for i := 1 to n DO BEGIN
		x[i].app := val;
	END;
END;

procedure petSamoglasnika(strS : string);
var i, j, k, lenS : integer;
	x : niz;
	pet : Boolean;
  	strNew : string;
BEGIN
	lenS := ord(strS[0]);
	i := 1;
	x[1].vowel := 'a'; x[2].vowel := 'e'; x[3].vowel := 'i'; x[4].vowel := 'o'; x[5].vowel := 'u';
	while (strS[i] = ' ') AND (i <= lenS) DO
		INC(i);
	while (i <= lenS) DO BEGIN
		extractStr(strS, i, strNew);
		memSet(x, brojSamoglasnika, 0);
		while (strS[i] = ' ') AND (i <= lenS) DO
			INC(i);
		for k := 1 to ord(strNew[0]) DO
			for j := 1 to brojSamoglasnika do
				if (x[j].vowel = strNew[k]) then
					INC(x[j].app);
    	pet := true;
		for k := 1 to brojSamoglasnika do
			if (x[k].app = 0) then
				 pet := false;
		if pet then writeln(strNew);	
	END;
END;

BEGIN
	readln(strS);
	while (strS <> '') DO BEGIN
		petSamoglasnika(strS);
		readln(strS);
	END;
END.
