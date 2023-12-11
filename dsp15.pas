(***********************  PROGRAM NO.15  ***********************)
(***  SPECTRAL PROPERTIES OF RECTANGULAR WINDOW (LOG PLOT)  ****)
program DSP15;
uses graph3;
var FREQ,H,DB: real;
var N,M,K: integer;
begin
  writeln('ENTER VALUE OF M');
  readln(M);
  graphmode;
(*************  DRAW RECTANGULAR GRID FOR PLOT  ****************)
  for K:=0 to 5 do
    begin
      draw(0,30+20*K,320,30+20*K,1);
      draw(64*K,30,64*K,130,1);
    end;
  draw(319,30,319,130,1);
(*****  ESTIMATE SPECTRUM, CONVERT TO DECIBELS, AND PLOT  ******)
  for N:=1 to 320 do
    begin
      FREQ:=3.141593*(N-1)/320;H:=1;
        for K:=1 to M do
          begin
            H:=H+2*cos(K*FREQ);
          end;
        H:=H/(1+2*M);
        DB:=20*ln(abs(H))*0.4343;
        if (DB)<-50 then DB:=-50;
        draw(N,130,N,round(30-2*DB),1);
    end;
end.
(***************************************************************)