(**********  PROGRAM NO.25       FAST CONVOLUTION  *************)
program DSP25;
uses graph3;
var X: array[1..128] of real;
var H: array[1..128] of real;
var Y: array[1..128] of real;
var XR: array[1..128] of real;
var XI: array[1..128] of real;
var VR: array[1..128] of real;
var VI: array[1..128] of real;
var WI: array[1..128] of real;
var WR: array[1..128] of real;
var A,K,N,M,L,P,T,D,LIM1,LIM2,J,I,R,LIM3,XX,YY: integer;
var XHMAG,X1,X2,PI,B1,B2,C1,C2,ARG,COS1,SIN1,MAX,MAG,XT: real;
label 1,2,3,4;
begin
    for K:=1 to 128 do begin X[K]:=0;H[K]:=0;Y[K]:=0;end;
    N:=128;M:=7;
(*****  DEFINE AND PLOT INPUT SIGNAL AND IMPULSE RESPONSE  *****)
    for K:=1 to 64 do begin X[K]:=1;end;
    H[1]:=1;H[2]:=1.5;
    for K:=3 to 64 do begin H[K]:=1.5*H[K-1]-0.85*H[K-2];end;
 graphmode;
    for K:=1 to N do begin
      draw(K,70,K,round(70-25*X[K]),1);end;
    for K:=1 to N do begin
      draw(K+190,70,K+190,round(70-25*H[K]),1);end;
(*************  CONVOLVE IN TIME DOMAIN, THEN PLOT  ************)
    for K:=1 to 128 do begin
      for L:=1 to K do begin
        Y[K]:=Y[K]+X[L]*H[K-L+1];
    end;end;
      for K:=1 to N do begin
        draw(K+100,160,K+100,round(160-8*Y[K]),1);end;
    writeln('ENTER ANY INTEGER TO START FAST CONVOLN');
    readln(A);
 clearscreen;
  for P:=1 to 3 do begin
      if P=1 then begin T:=1;D:=1;
        for K:=1 to N do begin
          XR[K]:=X[K];XI[K]:=0;end end;
      if P=2 then begin T:=1; D:=1;
        for K:=1 to N do begin
          XR[K]:=H[K];XI[K]:=0;end end;
      if P<3 then goto 1;
        T:=-1;D:=N;
        for K:=1 to N do begin
          XR[K]:=VR[K]*WR[K]-VI[K]*WI[K];
          XI[K]:=VI[K]*WR[K]+VR[K]*WI[K];
          XHMAG:=sqrt((VR[K]*VR[K]+VI[K]*VI[K])*
                                      (WR[K]*WR[K]+WI[K]*WI[K]));
          draw(K,160,K,round(160-XHMAG/4),1);
        end;
(*********************  SHUFFLE INPUT DATA  ********************)
 1: LIM1:=N-1;LIM2:=trunc(N/2);J:=1;
    for I:=1 to LIM1 do begin
      if I>J-1 then GOTO 2;
        X1:=XR[J];X2:=XI[J];
        XR[J]:=XR[I];XI[J]:=XI[I];XR[I]:=X1;XI[I]:=X2;
 2: L:=LIM2;
 3: if L>J-1 then goto 4;
      J:=J-L;L:=trunc(L/2);goto 3;
 4: J:=J+L;end;
(******************  IN-PLACE TRANSFORMATION  ******************)
    PI:=3.141593;
    for I:=1 to M do begin
      LIM1:=round(exp((I-1)*ln(2)));
      LIM2:=round(exp((M-I)*ln(2)));
      for L:=1 to LIM2 do begin
        for R:=1 to LIM1 do begin
          LIM3:=(R-1)+(L-1)*2*LIM1+1;
          B1:=XR[LIM3];B2:=XI[LIM3];
          C1:=XR[LIM3+LIM1];C2:=XI[LIM3+LIM1];
          ARG:=2*PI*(R-1)*LIM2/N;COS1:=cos(ARG);SIN1:=sin(ARG);
          X1:=C1*COS1+C2*SIN1*T;X2:=-C1*SIN1*T+C2*COS1;
          XR[LIM3]:=B1+X1;XI[LIM3]:=B2+X2;
          XR[LIM3+LIM1]:=B1-X1;XI[LIM3+LIM1]:=B2-X2;
      end;end;end;
    for K:=1 to N do begin
      XR[K]:=XR[K]/D;XI[K]:=XI[K]/D;end;
(***  SAVE TRANSFORMS OF INPUT SIGNAL AND IMPULSE RESPONSE  ****)
    if P=1 then begin
      for K:=1 to N do begin
        VR[K]:=XR[K];VI[K]:=XI[K];
    end end;
    if P=2 then begin
      for K:=1 to N do begin
        WR[K]:=XR[K];WI[K]:=XI[K];
    end end;
(****************  FIND PEAK VALUE FOR PLOT  *******************)
    MAX:=0;
    for K:=1 to N do begin
      MAG:=sqrt(XR[K]*XR[K]+XI[K]*XI[K]);
      if MAG>MAX then MAX:=MAG;
    end;
(**********************  SET PLOT OFFSETS  *********************)
    if P=1 then begin XX:=0;YY:=70 end;
    if P=2 then begin XX:=190;YY:=70 end;
    if P=3 then begin XX:=190;YY:=160 end;
(********  PLOT MAGNITUDE OF FFT, OR REAL PART OF IFFT  ********)
    for K:=1 to N do begin
        XT:=sqrt(XR[K]*XR[K]+XI[K]*XI[K]);
        if P=3 then XT:=XR[K];
        draw(K+XX,YY,K+XX,round(YY-XT*40/MAX),1);
      end;
  end;
end.
(***************************************************************)