program dz5Pom(input, output, ulazTxt, izlazTxt, izlaz);

Type mobilni = record
	 	oznaka : string;
	 	rez : array [1 .. 3] of real;
	 	cena : real;
	 end;

Var izlaz : file of mobilni;
	  tmpMob : mobilni;
	  izlIme : string;
  	i : integer;
  	izlazTxt, ulazTxt : text;
  	tmpOcena : real;
Begin
	writeln('unesite ime ulazne datoteke');
	readln(izlIme);
	assign(izlazTxt, 'izlaz.txt');
	assign(izlaz, izlIme);
	rewrite(izlaz);
	rewrite(izlazTxt);
	writeln('unesite oznaku');
	readln(input, tmpMob.oznaka);
	while (tmpMob.oznaka <> '') do BEGIN
		writeln('unesite rezultate');
		for i := 1 to 3 do
			read(input, tmpMob.rez[i]);
		readln(input);
		writeln('unesite cenu');
		readln(input, tmpMob.cena);
  	with tmpMob do  BEGIN
      	tmpOcena := cena * 3 / (rez[1] + rez[2] + rez[3]);
			  writeln(izlazTxt, oznaka, ' ', rez[1] : 10 : 2, ' ', rez[2] : 10 : 2, ' ', rez[3] : 10 : 2, ' ', cena : 10 : 2, ' ', tmpOcena : 10 : 2);
    END;
  	write(izlaz, tmpMob);
    writeln('unesite oznaku');
    readln(input, tmpMob.oznaka);
	END;
	close(izlaz);
	close(izlazTxt);
end.
