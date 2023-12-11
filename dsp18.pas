(********************  PROGRAM NO.18  **************************)
(*****  NONRECURSIVE FILTER DESIGN WITH THE KAISER WINDOW  *****)
program DSP18;
uses graph3;
var SEE: array[0..200] of real;
var H: array[0..200] of real;
var W: array[0..320] of real;
var P,Q,R,S,T,A,I,B,C,D: real;
var ALPHA,BETA,A0,H0,W0,W1,FREQ,MAX,DB,MREAL: real;
var X,N,K,M,Y: integer;
label 1,2;
begin
  1:writeln('ENTER CENTER-FREQUENCY (IN DEGREES)'); readln(P);
    W0:=P*3.141593/180;
    writeln('ENTER FILTER BANDWIDTH (IN DEGREES)'); readln(Q);
    W1:=Q*0.5*3.141593/180;
    writeln('ENTER KAISER DESIGN PARAMETERS:');
    writeln('RIPPLE (AS A FRACTION):'); readln(R);
    writeln('TRANSITION WIDTH (DEGREES):'); readln(S); T:=S/360;
(***************  ESTIMATE KAISER PARAMETERS  ******************)
 A:=-20*ln(R)*0.4343;MREAL:=(A-7.95)/(28.72*T);M:=trunc(MREAL+1);
  writeln('NO. OF IMPULSE RESPONSE TERMS=',2*M+1);
  writeln('CHANGE  PARAMETERS, OR CONTINUE (0/1)?');
  readln(X); if X=0 then GOTO 1;
    if A>49 then begin ALPHA:=0.1102*(A-8.7);goto 2 end;
    if A>21 then begin
     ALPHA:=(0.5842*exp(0.4*ln(A-21))+(0.07886*(A-21)));goto 2
    end;ALPHA:=0;
  2:writeln('FOR THIS WINDOW, ALPHA=',ALPHA);
    writeln('ENTER ANY INTEGER TO START PLOT'); readln(X);
(*******************  COMPUTE WINDOW VALUES  *******************)
  for N:=0 to M do begin
    BETA:=ALPHA*sqrt(1-(N/M)*(N/M));I:=1;B:=1;
      for K:=1 to 20 do begin
        C:=B*BETA*BETA/4;D:=C/(K*K);I:=I+D;B:=D;end;SEE[N]:=I;
  end;A0:=SEE[0]; for N:=0 to M do begin
                    SEE[N]:=SEE[N]/A0;end;
(**************  COMPUTE IMPULSE RESPONSE VALUES  **************)
  H0:=W1/3.141593;
    for N:=1 to M do begin
      H[N]:=(1/(N*3.141593))*sin(N*W1)*cos(N*W0)*SEE[N];end;
(**************  DRAW RECTANGULAR GRID FOR PLOT  ***************)
  graphmode;
    for K:=0 to 5 do begin draw(0,30+20*K,320,30+20*K,1);
             draw(64*K,30,64*K,130,1);end;draw(319,30,319,130,1);
(***************  COMPUTE FREQUENCY RESPONSE  ******************)
  for N:=1 to 320 do begin
    FREQ:=3.141593*(N-1)/320;W[N]:=H0;
      for K:=1 to M do begin
        W[N]:=W[N]+2*H[K]*cos(K*FREQ);end;end;
(*****  NORMALISE TO UNITY, CONVERT TO DECIBELS, AND PLOT  *****)
  MAX:=0;
  for N:=1 to 320 do begin
    if abs(W[N])>MAX then MAX:=abs(W[N]);end;
      for N:=1 to 320 do begin
        DB:=20*ln(abs(W[N])/MAX)*0.4343;if DB<-50 then DB:=-50;
        draw(N,130,N,round(30-2*DB),1);end;
    writeln('ENTER ANY INTEGER TO PRINT h[n] VALUES');readln(Y);
  clearscreen;
    writeln('VALUES h[0] TO h[M]:');
    writeln('(CORRECTED FOR UNITY MAXIMUM GAIN)');
    writeln(H0/MAX);
  for N:=1 to M do begin writeln(H[N]/MAX);end;
end.
(***************************************************************)