(*********  PROGRAM NO.19     DIGITAL DIFFERENTIATOR  **********)
program DSP19;
uses graph3;
var SEE: array[1..200] of real;
var H: array[1..200] of real;
var A,B,W,HF,C: real;
var M,N,K,X,Y: integer;
label 1,2,3;
begin
  writeln('ENTER VALUE OF M');
  readln(M);
  writeln('SELECT WINDOW:');
  writeln('1=RECTANGULAR; 2=HAMMING');
  readln(X);
(*******************  COMPUTE WINDOW VALUES  *******************)
    if (X=1) then begin A:=1;B:=0;C:=1;goto 1 end
             else begin A:=0.54;B:=0.46;C:=M end;
  1: for N:=1 to M do
       begin
         SEE[N]:=A+B*cos(N*3.141593/C);
       end;
(*****************  COMPUTE IMPULSE RESPONSE  ******************)
     for N:=1 to M do
       begin
         if odd(N) then goto 2;
           H[N]:=(1/N)*SEE[N];goto 3;
  2: H[N]:=-(1/N)*SEE[N];
  3: end;
(*****  COMPUTE AND PLOT FREQUENCY RESPONSE (LINEAR SCALE) *****)
  graphmode;
  for N:=1 to 320 do
    begin
      W:=(N-1)*3.141593/320;HF:=0;
        for K:=1 to M do
          begin
            HF:=HF-2*H[K]*sin(K*W);
          end;
        draw(N,150,N,round(150-20*HF),1);
    end;
  writeln('ENTER ANY INTEGER TO PRINT h[n]');
  writeln('  (REMEMBER THAT h(0) IS ZERO!)'); readln(Y);
  clearscreen;
  writeln('VALUES H(1) TO H(M) ARE:');
    for N:=1 to M do
      begin
        writeln (H[N]);
      end;
end.
(***************************************************************)