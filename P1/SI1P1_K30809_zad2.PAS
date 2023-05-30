program zad2(ulaz, input, output);

const nMax = 50;

type pravougaonik = record
			xLeft, yLeft, xRight, yRight : real;
		end;
	 nizPravougaonika = array [1 .. nMax] of pravougaonik;
Var x : nizPravougaonika;
	n : integer;
	xGiven, yGiven : real;
	rezultat : integer;

procedure unos(var x : nizPravougaonika; var duz : integer);
Var ulaz : text;
BEGIN
	duz := 0;
	assign(ulaz, 'pravougaonici.txt');
	reset(ulaz);
	while (NOT(eof(ulaz))) DO BEGIN
		INC(duz);
		readln(ulaz, x[duz].xLeft, x[duz].yLeft, x[duz].xRight, x[duz].yRight);
	END;
	close(ulaz);
END;

function brojanje(var x : nizPravougaonika; duz : integer; xGiven, yGiven : real) : integer;
Var i : integer;
BEGIN
	brojanje := 0;
	for i := 1 to duz DO BEGIN
		if (x[i].xLeft <= xGiven) AND (xGiven  <= x[i].xRight) AND (yGiven <= x[i].yRight) AND (yGiven >= x[i].yLeft) then
			INC(brojanje);
	END;
END;

Begin
	unos(x, n);
	writeln('unesite koordinatu');
	readln(xGiven, yGiven);
	rezultat := brojanje(x, n, xGiven, yGiven);
	writeln('nalazi se u ', rezultat, 'pravougaonika');
end.
