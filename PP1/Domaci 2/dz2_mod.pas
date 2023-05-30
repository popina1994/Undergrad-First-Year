Program domaci1(input, output);
Const
      MAX_BR_EL = 30000;
      minint = -32768;
Type niz = array [1 .. MAX_BR_EL] of integer;
    nizr = array [1 .. MAX_BR_EL] of real;
Var i, tr, n, kol, zbircif, trkol, trzbircif, min, max, brojac : integer;    { trkol broj cifara, trzbircif zbir}
    kolicnik : real;
    x : niz;
    y : nizr;
BEGIN
  writeln('unesi broj elemenata');
  readln(n);
  while ((N <= MAX_BR_EL) and (N > 0)) do BEGIN
    i := 1;

    for i := 1 to n do
        read(input, x[i]);
    kol := 0;
    zbircif := 0;

    for i := 1 to n do BEGIN
      tr := abs(x[i]);
      trkol := 0;
      trzbircif := 0;
      if tr = 0 THEN
        trkol := 1
      else  while tr > 0 do BEGIN
              trkol :=  trkol + 1;
              trzbircif := trzbircif + tr mod 10;
              tr := tr div 10;
            END;
      y[i] := trzbircif / trkol;
      kol := kol + trkol;
      zbircif := zbircif + trzbircif;
    END;

    kolicnik := zbircif / kol;
    writeln('kolicnike je:', kolicnik : 5 : 2);
    writeln('elementi koji ispunjavanju:');
    for i := 1 to n do BEGIN
      if y[i] > kolicnik then
        writeln('element:', x[i], 'indeks:', i);
    END;
    min := maxint;
    max := minint;
    for i := 1 to n do BEGIN
      if x[i] > max then
        max := x[i];
      if x[i] < min then
        min := x[i]
    END;
    brojac := 0;
    for i := 1 to n do
      if (x[i] <> max) and (x[i] <> min) then BEGIN
        brojac := brojac + 1;
        x[brojac] := x[i];
       END;
    if brojac = 0  then
      writeln('svi elementi su izbaceni')
    else BEGIN
          writeln('broj elemenata niza je:', brojac);
           write('slede elementi ');
          for i := 1 to brojac do
            writeln(x[i], ' ');
          writeln;
    END;

    writeln('unesi broj elemenata niza');
    readln(n);

  END;
END.

