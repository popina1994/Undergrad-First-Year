Program domaci1(input, output);
Const MAX_BR_EL = 30000;
Type niz = array [1 .. MAX_BR_EL] of integer;
    nizr = array [1 .. MAX_BR_EL] of real;
Var i, tr, n, kol, zbircif, trkol, trzbircif: integer;    { trkol broj cifara, zbircif zbir}
    kolicnik : real;
    x : niz;
    y : nizr;
Begin
  writeln('unesite broj elemenata');
  readln(n);
  while ((N <= MAX_BR_EL) AND (N > 0)) do BEGIN
    for i := 1 to N do
      read(x[i]);
    kol := 0;
    zbircif := 0;
    for i := 1 to n do BEGIN
      tr := abs(x[i]);
      trkol := 0;
      trzbircif := 0;
      if (tr = 0) THEN
        trkol := 1
      ELSE  while tr > 0 do BEGIN
              trkol :=  trkol + 1;
              trzbircif := trzbircif + tr mod 10;
              tr := tr div 10;
            END;
      y[i] := trzbircif / trkol;
      kol := kol + trkol;
      zbircif := zbircif + trzbircif;
    END;
    kolicnik := zbircif / kol;
    writeln('kolicinik je:', kolicnik : 5 : 2);
    for i := 1 to n do
      if y[i] > kolicnik then
        writeln('element niza:', x[i], ' ', i);
    writeln('unesite broj elemenata:');
    readln(n);
  END
END.
