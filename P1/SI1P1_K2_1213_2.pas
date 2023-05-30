Program zad2(input, output);

Var
	s1, s2 : string;
	len1, len2, i, j, k : integer;
	tempjedn, jedn : Boolean;

BEGIN
  writeln('unesite prvi string');
	readln(s1);
	writeln('unesite drugi string');
	readln(s2);
	len1 := ord(s1[0]);
	len2 := ord(s2[0]);
	i := 1;
  while (len1 <> 0) do BEGIN
		while (i <= len1 - len2 + 1) AND (NOT jedn) do BEGIN
			j := i;
			tempjedn := true;
			for k := 1 to len1 do
				if (s1[k] <= 'Z') then
					s1[k] := chr(ord(s1[k]) + ord('a') - ord('A'));
			for k := 1 to len2 do
				if (s2[k] <= 'Z')  then
					s2[k] := chr(ord(s2[k]) + ord('a') - ord('A'));		
			while ((j <= (len2 + i - 1)) AND (tempjedn)) do BEGIN
				if (s1[j] <> s2[j - i + 1]) then
					tempjedn := false;
				INC(j);
			END;
			if tempjedn then
				jedn := true;
			INC(i);
		END;
    if (jedn)  then
      writeln('drugi se sadrzi u prvom')
    else writeln('druge se ne sadrzi u prvom');
		writeln('unesite prvi string');
		readln(s1);
		writeln('unesite drugi string');
		readln(s2);
		len1 := ord(s1[0]);
		len2 := ord(s2[0]);
		i := 1;
		jedn := false;
	END
END.
