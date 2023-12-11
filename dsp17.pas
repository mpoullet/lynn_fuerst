(*******************  PROGRAM NO.17  ***************************)
(**  NONRECURSIVE FILTER DESIGN BY FOURIER TRANSFORM METHOD  ***)
(*******  WITH RECTANGULAR, VON HANN, OR HAMMING WINDOW  *******)
(******  AND DECIBEL PLOT OF FREQUENCY RESPONSE MAGNITUDE ******)
(************  (IMPULSE RESPONSE HAS (2M+1) TERMS)  ************)
program DSP17;
uses graph3;
var SEE: array[1..200] of real;
var H: array[1..200] of real;
var W: array[1..320] of real;
var H0,A,B,C,FREQ,MAX,DB,W0,W1: real;
var M,X,K,N,Y: integer;
label 1;
begin
  writeln('ENTER CENTER-FREQUENCY (IN DEGREES)'); readln(A);
  W0:=A*3.141593/180;
  writeln('ENTER FILTER BANDWIDTH (IN DEGREES)'); readln(B);
  W1:=B*0.5*3.141593/180;
  writeln('ENTER VALUE OF M'); readln(M);
  writeln('SELECT WINDOW:');
  writeln('0=RECTANGULAR; 1=VON HANN; 2=HAMMING'); readln(X);
(*******************  COMPUTE WINDOW VALUES  *******************)
    if X=0 then begin A:=1;B:=0;C:=1;goto 1 end;
    if X=1 then begin A:=0.5;B:=0.5;C:=M+1;goto 1 end;
      A:=0.54;B:=0.46;C:=M;
  1: for N:=1 to M do begin
       SEE[N]:=A+B*cos(N*3.141593/C);end;
(**************  COMPUTE IMPULSE RESPONSE VALUES  **************)
  H0:=W1/3.141593;
   for N:=1 to M do begin
     H[N]:=(1/(N*3.141593))*sin(N*W1)*cos(N*W0)*SEE[N];end;
(**************  DRAW RECTANGULAR GRID FOR PLOT  ***************)
  graphmode;
    for K:=0 to 5 do begin
      draw(0,30+20*K,320,30+20*K,1);
      draw(64*K,30,64*K,130,1);end;
    draw(319,30,319,130,1);
(***************  COMPUTE FREQUENCY RESPONSE  ******************)
  for N:=1 to 320 do begin
    FREQ:=3.141593*(N-1)/320;W[N]:=H0;
      for K:=1 to M do begin
        W[N]:=W[N]+2*H[K]*COS(K*FREQ);
      end;
  end;
(*****  NORMALISE TO UNITY, CONVERT TO DECIBELS, AND PLOT  *****)
  MAX:=0;
    for N:=1 to 320 do begin
      if abs(W[N])>MAX then MAX:=abs(W[N]);
    end;
  for N:=1 to 320 do begin
    DB:=20*ln(abs(W[N])/MAX)*0.4343;if DB<-50 then DB:=-50;
    draw(N,130,N,round(30-2*DB),1);
  end;
  writeln('ENTER ANY INTEGER TO PRINT h[n] VALUES');
  readln (Y);
  clearscreen;
  writeln('VALUES h[0] TO h[M]):');
  writeln ('(CORRECTED FOR UNITY MAXIMUM GAIN)');
  writeln ( H0/MAX);
    for N:=1 to M do begin writeln(H[N]/MAX);end;
end.
(***************************************************************)