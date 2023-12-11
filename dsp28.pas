(*******  PROGRAM N0.28     PROCESSING RANDOM SEQUENCES  *******)
program DSP28;
uses graph3;
var GN: array[1..1200] of real;
var X: array[1..1200] of real;
var Y: array[1..1200] of real;
var H: array[1..10] of real;
var J: array[1..19] of real;
var XACF: array[1..101] of real;
var YACF: array[1..101] of real;
var EST: array[1..101] of real;
var N,K,L,M,P,Q: integer;
var C,SUM,MY,A,B,Z,MYE,VARE: real;
begin
  randomize;
  graphmode;
    for N:=1 to 1200 do begin
      Y[N]:=0;end;
    for N:=1 to 19 do begin
      J[N]:=0;end;
    for N:=1 to 101 do begin
      EST[N]:=0;end;
(************  ENTER PROCESSOR'S IMPULSE RESPONSE  *************)
  H[1]:=1;H[2]:=2;H[3]:=1;H[4]:=-1;H[5]:=-2;
  H[6]:=-1;H[7]:=1;H[8]:=2;H[9]:=1;H[10]:=0;
(*******  FORM GAUSSIAN NOISE, ZERO MEAN, UNIT VARIANCE  *******)
  clearscreen;
  for N:=1 to 1200 do begin
    C:=0;for K:=1 to 12 do begin
           C:=C+random-0.5;
         end;
    GN[N]:=C;
  end;
(******** LOW-PASS FILTER & ADD UNIT MEAN TO FORM X[N]  ********)
  for N:=4 to 1200 do begin
    X[N]:=(GN[N]+GN[N-1]+GN[N-2]+GN[N-3])*0.5+1;
  end;
(*************  PLOT 320 VALUES OF X[N] ON SCREEN  *************)
  for N:=1 to 320 do begin
    draw(N,50,N,round(50-X[N+100]*6),1);
  end;
(*****************  DEFINE AND PLOT INPUT ACF  *****************)
  for K:=1 to 101 do begin
    XACF[K]:=1;
  end;
  XACF[48]:=1.25;XACF[49]:=1.5;XACF[50]:=1.75;XACF[51]:=2;
  XACF[52]:=XACF[50];XACF[53]:=XACF[49];XACF[54]:=XACF[48];
  for N:=1 to 83 do begin
    draw(N,180,N,round(180-XACF[N+9]*25),1);
  end;
(**********  FIND ACF OF PROCESSOR'S IMPULSE RESPONSE **********)
  for K:=1 to 10 do begin
    for L:=1 to K do begin
      J[K]:=J[K]+H[L]*H[10-K+L];
    end;
  end;
    for K:=11 to 19 do begin
      J[K]:=J[20-K];
    end;
(***************  PREDICT MEAN VALUE OF OUTPUT  ****************)
  SUM:=0;for K:=1 to 10 do begin
           SUM:=SUM+H[K];
         end;
  MY:=1*SUM;
(***************  PREDICT AND PLOT OUTPUT ACF  *****************)
  for M:=10 to 92 do begin
    SUM:=0;for K:=1 to 19 do begin
             SUM:=SUM+XACF[M-10+K]*J[K];
           end;
    YACF[M]:=SUM;
  end;
  for N:=1 to 83 do begin
    draw(N+120,180,N+120,round(180-YACF[N+9]*50/YACF[51]),1);
  end;
(************  CONVOLVE X[N] AND H[N] TO FORM Y[N]  ************)
  for N:=15 to 1200 do begin
    for K:=1 to 10 do begin
      Y[N]:=Y[N]+H[K]*X[N-K];
    end;
  end;
(*************  PLOT 320 VALUES OF Y[N] ON SCREEN  *************)
  A:=9/SQRT(YACF[51]);
    for N:=1 to 320 do begin
      draw(N,100,N,round(100-Y[N+100]*A),1);
    end;
(***************  ESTIMATE AND PLOT OUTPUT ACF  ****************)
  B:=20*YACF[51];
    for K:=1 to 100 do begin
      for M:=10 to 92 do begin
        P:=M-51;
          for L:=1 to 10 do begin
            Q:=10*(K-1)+L+60;EST[M]:=EST[M]+Y[Q]*Y[Q+P];
          end;
        draw(M+227,180,M+227,round(180-EST[M]/B),1);
      end;
    end;
  writeln('ENTER A DUMMY VARIABLE TO CONTINUE');readln(Z);
  clearscreen;
(******  PREDICT AND ESTIMATE OUTPUT MEAN AND VARIANCE   ******)
  SUM:=0;for N:=15 to 1200 do begin
           SUM:=SUM+Y[N];
         end;
  MYE:=SUM/1185;
  writeln('OUTPUT MEAN (PREDICTED)=');writeln(MY);
  writeln('OUTPUT MEAN (ESTIMATED)=');writeln(MYE);
  SUM:=0;for N:=15 to 1200 do begin
           SUM:=SUM+(Y[N]-MY)*(Y[N]-MY);
         end;
  VARE:=SUM/1185;
  writeln('OUTPUT VARIANCE (PREDICTED)=');
  writeln(YACF[51]-MY*MY);
  writeln('OUTPUT VARIANCE (ESTIMATED)=');writeln(VARE);
end.
(***************************************************************)




