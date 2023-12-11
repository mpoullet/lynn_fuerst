(**********************  PROGRAM NO.14  ************************)
(****************  TIME-DOMAIN PERFORMANCE OF  *****************)
(***********  21-TERM LINEAR-PHASE BANDPASS FILTER  ************)
program DSP14;
uses graph3;
var X: array[1..320] of real;
var Y: array[1..320] of real;
var H: array[0..20] of real;
var N,K: integer;
begin
  for N:=1 to 320 do
    begin
      X[N]:=0;Y[N]:=0;
    end;
(***  DEFINE IMPULSE RESPONSE VALUES, STARTING WITH CENTRAL  ***)
(********  VALUE AND WORKING TOWARDS ONE OF THE "TAILS"  *******)
  H[10]:=0.083333;H[11]:=0.041192;H[12]:=-0.039789;
  H[13]:=-0.075026;H[14]:=-0.034458;H[15]:=0.030746;
  H[16]:=0.053052;H[17]:=0.021962;H[18]:=-0.017229;
  H[19]:=-0.025009;H[20]:=-0.007958;
  for N:=10 to 20 do
    begin
      H[20-N]:=H[N];
    end;
(********  LOAD INPUT ARRAY WITH TWO SIGNAL COMPONENTS  ********)
  for N:=108 to 180 do
    begin
      X[N]:=cos(N*5*3.141593/18)+cos(N*7*3.141593/18);
    end;
(**************************  PLOT  *****************************)
  graphmode;
  for N:=1 to 320 do
    begin
      draw(N,30,N,round(30-10*X[N]),1);
    end;
(*******  ADD TWO OUT-OF-BAND COMPONENTS TO INPUT SIGNAL  ******)
  for N:=1 to 320 do
    begin
      X[N]:=X[N]+sin(N*3.141593/8)+sin(N*3.141593/1.8);
    end;
(**************************  PLOT  *****************************)
  for N:=1 to 320 do
    begin
      draw(N,90,N,round(90-10*X[N]),1);
    end;
(****  CONVOLVE INPUT SIGNAL AND IMPULSE RESPONSE, AND PLOT  ***)
  for N:=22 to 320 do
    begin
      Y[N]:=0;
        for K:=0 to 20 do
          begin
            Y[N]:=Y[N]+H[K]*X[N-K];
          end;
			 draw(N,150,N,round(150-25*Y[N]),1);
    end;
end.
(***************************************************************)