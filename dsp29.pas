(************  PROGRAM NO.29     MATCHED FILTERING  ************)
program DSP29;
uses graph3;
var X: array[1..420] of real;
var Y: array[1..420] of real;
var H: array[1..100] of real;
var S: array[1..100] of real;
var N,K: integer;
var NV,SUM,MX,MY: real;
begin
  for N:=1 to 420 do begin
  X[N]:=0;Y[N]:=0;end;
  randomize;
  graphmode;
(********************  DEFINE INPUT SIGNAL  ********************)
  S[1]:=1;S[2]:=0.575;
    for N:=3 to 60 do begin
      S[N]:=1.575*S[N-1]-0.9025*S[N-2];
    end;
(********  LOAD TWO VERSIONS OF SIGNAL INTO INPUT ARRAY  *******)
  for N:=1 to 60 do begin
    X[N+110]:=S[N];X[N+280]:=X[N+280]+S[N];
  end;
(********  ADD REQUIRED AMOUNT OF WHITE GAUSSIAN NOISE  ********)
  writeln('ENTER NOISE VARIANCE');readln(NV);
    for N:=1 to 420 do begin
      SUM:=0;
        for K:=1 to 12 do begin
          SUM:=SUM+random-0.5;
        end;
      X[N]:=X[N]+NV*SUM;
    end;
(******************  DEFINE IMPULSE RESPONSE  ******************)
  for N:=1 to 60 do begin
    H[N]:=S[61-N];
  end;
(************  CONVOLVE INPUT AND IMPULSE RESPONSE  ************)
  for N:=101 to 420 do begin
    for K:=1 to 100 do begin
      Y[N]:=Y[N]+H[K]*X[N-K];
    end;
  end;
(******  NORMALISE ARRAYS TO MAX VALUE OF UNITY FOR PLOT  ******)
  MX:=0;MY:=0;
    for N:=101 to 420 do begin
      if abs(X[N])>MX then MX:=abs(X[N]);
      if abs(Y[N])>MY then MY:=abs(Y[N]);
    end;
  for N:=1 to 420 do begin
    X[N]:=X[N]/MX;Y[N]:=Y[N]/MY;
  end;
(************  PLOT INPUT AND OUTPUT SIGNAL ARRAYS  ************)
  clearscreen;
    for N:=101 to 420 do begin
      draw(N-100,50,N-100,round(50-X[N]*22),1);
    end;
    for N:=101 to 420 do begin
      draw(N-100,150,N-100,round(150-Y[N]*22),1);
    end;
end.
(***************************************************************)
