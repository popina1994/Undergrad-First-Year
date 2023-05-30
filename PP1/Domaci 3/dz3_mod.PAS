Program treci_domaci(input, output);

Const MAX_BR_VR = 1000;
	 MAX_BR_KOL = 1000;

Type mat = array [1 .. MAX_BR_VR, 1 .. MAX_BR_KOL] of real;

Var m, n : integer; {m - broj vrsta, n - broj kolona}
	x : mat;
	korektan : Boolean;
	geomsr : real;
function unos(var m, n : integer; var x : mat) : Boolean;
var i, j : integer;
BEGIN
	writeln('unesite broj vrsta');
	readln(m);
	writeln('unesite broj kolona');
	readln(n);
	if (m > MAX_BR_VR) OR (m <= 0) OR (n <= 0) OR (n > MAX_BR_KOL) then
		unos := false
	else BEGIN
			for i := 1 to m do
				for j := 1 to n do
					read(x[i][j]);
			unos := true;
	END;
END;

function obrada(var x : mat; m, n : integer) : real;
var i, j, brojac : integer;
BEGIN
	brojac := 0;
	obrada := 1;
	for i := 1 to m do
		for j := 1 to n do
			if ((i + j) mod 2) = 0 then BEGIN
				INC(brojac);
				obrada := obrada * x[i][j];
			END;
	obrada := exp(ln(obrada) / brojac);
	for i := 1 to m do
		for j := 1 to n do
			if x[i][j] < obrada then
				x[i][j] := sqr(x[i][j]);
END;

procedure rezultat(var x : mat; m, n : integer; geomsr : real);
var i, j : integer;
BEGIN
	writeln('geometrijska sredina je:', geomsr : 5 : 2);
	for i := 1 to m do BEGIN
		for j := 1 to n do
			write(x[i][j] : 0 : 2, ' ');
		writeln;
	END;
END;

procedure zameni(var x, y : real);
var t : real;
BEGIN
	t := x;
	x := y;
	y := t;
END;

procedure transponuj(var x : mat; var m, n : integer);
var i, j, max, t : integer;
BEGIN
	max := m;
	if (n > max) then max := n;
	for i := 1 to max do
		for j := n + 1 to max do
			x[i][j] := 0;
	for i := m + 1 to max do
		for j := 1 to max do
			x[i][j] := 0;
	for i := 1 to max do
		for j := 1 to max do
      if (i > j)  then
        zameni(x[i][j], x[j][i]);
	t := m;
  m := n;
  n := t;
END;

Begin
	korektan := unos(m, n, x);
	while korektan do BEGIN
		transponuj(x, m, n);
    writeln('broj vrsta je', m, 'broj kolona je', n);
		geomsr := obrada(x, m, n);
		rezultat(x, m, n, geomsr);
		korektan := unos(m, n, x);
	END;
end.
