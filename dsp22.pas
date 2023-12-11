(********  PROGRAM NO.22    FREQUENCY-SAMPLING FILTER  *********)
program DSP22;
uses graph3;
var X: array[1..320] of real;
var Y: array[1..320] of real;
var W: array[1..320] of real;
var P: array[1..320] of real;
var Q: array[1..320] of real;
var R: array[1..320] of real;
var S: array[1..320] of real;
var T: array[1..320] of real;
var U: array[1..320] of real;
var V: array[1..320] of real;
var N,M,K: integer;
var FREQ,HR,HI,H: real;
begin
  for N:=1 to 320 do
    begin
      X[N]:=0;Y[N]:=0;W[N]:=0;P[N]:=0;Q[N]:=0;
      R[N]:=0;S[N]:=0;T[N]:=0;U[N]:=0;V[N]:=0;
    end;
  graphmode;
(**************  LOAD IMPULSE INTO INPUT ARRAY  ****************)
  X[120]:=1;
    for N:=120 to 280 do
      begin
        W[N]:=X[N]-0.886867*X[N-120];
        P[N]:=0.5171211*P[N-1]-0.998001*P[N-2]+0.5*W[N];
        Q[N]:=0.415408*Q[N-1]-0.998001*Q[N-2]-W[N];
        R[N]:=0.312556*R[N-1]-0.998001*R[N-2]+W[N];
        S[N]:=0.208848*S[N-1]-0.998001*S[N-2]-W[N];
        T[N]:=0.104567*T[N-1]-0.998001*T[N-2]+W[N];
        U[N]:=-0.998001*U[N-2]-0.666667*W[N];
        V[N]:=-0.104567*V[N-1]-0.998001*V[N-2]+0.333333*W[N];
        Y[N]:=P[N]+Q[N]+R[N]+S[N]+T[N]+U[N]+V[N];
(***************  PLOT IMPULSE RESPONSE VALUE  *****************)
        M:=(N-120)*2;
        draw(M,70,M,round(70-Y[N]*7),1);
      end;
  for N:=1 to 320 do
    begin
      FREQ:=(N-1)*3.141593/320;HR:=0;HI:=0;H:=0;
        for K:=1 to 120 do
          begin
            HR:=HR+Y[119+K]*cos(K*FREQ);
            HI:=HI+Y[119+K]*sin(K*FREQ);
          end;
        H:=sqrt(HR*HR+HI*HI);
(**************  PLOT FREQUENCY RESPONSE VALUE  ****************)
      draw(N,170,N,round(170-0.75*H),1);
    end;
end.
(***************************************************************)