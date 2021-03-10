// FORMS MANAGER
// VERSIONE 1.0.6 per Aristos, con intervalli data cambiati in 1900, 2050 o 9/9/9999
// by ANDREA CASSA, 18 Settembre 2000
// Compatibile con Javascript 1.2


_g=new Array(); 

 

C=new Array(); 
C["NA"]=1;
C["NN"]=2;
C["ND"]=3;
C["NP"]=4;
C["CONT"]=5;



numerr=new Array(); 
numerr['xp']=27;
numerr['xn']=26;
numerr['xa']=12;
numerr['np']=29;
numerr['nn']=28;
numerr['na']=19;





M=new Array(); 
M[0]=new Array(); 
M[1]=new Array(); 

A="\n"+"Usare un numero ";
M[0][5]=A+"fra 1 e 31.";
M[0][6]=M[0][17]=M[0][25]=M[0][1]=A+"fra 1900 e 2050.";
M[0][7]=M[0][4]=": il giorno non e' coerente con il mese.";
M[0][8]=M[0][30]=M[0][10]=M[0][11]=M[0][13]=M[0][20]=M[0][3]="\n"+"non puo' essere lasciato in bianco.";
M[0][9]=":\n"+"l'anno non e' bisestile.";
M[0][12]=A;
M[0][14]="\n"+"Per le iniziali delle persone usare 3 caratteri"+
             " come nei seguenti esempi\n"+
             "N-C per Nome Cognome (separate dal trattino!)\n"+
             "NSC Nome Secondonome Cognome"+"\n"+
             "oppure 2 caratteri come nel seguente esempio\n"+
             "NC per Nome Cognome";
M[0][15]=A+"fra 0 e 23";
M[0][16]=A+"fra 0 e 59";
M[0][18]=M[0][24]=M[0][2]=A+"fra 1 e 12";
M[0][21]="\n"+"E' fuori dal range permesso.";
M[0][22]=M[0][19]=A+"intero";
M[0][23]="\n"+"Si � usato un codice non permesso.";
M[0][26]=A+"reale <=0";
M[0][27]=A+"reale >=0";
M[0][28]=A+"intero <=0";
M[0][29]=A+"intero >=0";
M[0][35]="\n"+"Questo campo deve essere lasciato vuoto!";
M[0][36]="\n"+"Questo casella deve essere lasciata bianca!";
M[0][38]=M[0][37]="\n"+"Questo campo deve avere valore ";
M[0][50]="Attenzione prego. Formato non corretto nel campo\n";
M[0][51]="\n"+"Puoi anche usare i seguenti codici\n";
M[0][52]="diverso da ";

A="\n"+"Use a number ";
M[1][5]=A+"between 1 and 31.";
M[1][6]=M[1][17]=M[1][25]=M[1][1]=A+"between 1900 and 2050.";
M[1][7]=M[1][4]=": day and month are not coherent.";
M[1][8]=M[1][30]=M[1][10]=M[1][11]=M[1][13]=M[1][20]=M[1][3]=":\n"+"cannot be blank.";
M[1][9]=":\n"+"year is not a leap-year.";
M[1][12]=A;
M[1][14]="\n"+"Follow this example please:\n"+ 
             "N-S for Name Surname (separated by the dash!)\n"+
             "NSS for Name Secondname Surname"+
             "\n"+"or simply NS for Name Surname";
M[1][15]=A+"between 0 and 23";
M[1][16]=A+"between 0 and 59";
M[1][18]=M[1][24]=M[1][2]=A+"between 1 and 12";
M[1][21]="\n"+"is out of range.";
M[1][22]=M[1][19]=A+"|integer|";
M[1][23]="\n"+"You used a forbidden code.";
M[1][26]=A+"|real <=0|";
M[1][27]=A+"|real >=0|";
M[1][28]=A+"|integer <=0|";
M[1][29]=A+"|integer >=0|";
M[1][35]="\n"+"This field must be blank!";
M[1][36]="\n"+"Please uncheck this checkbox.";
M[1][38]=M[1][37]="\n"+"This field must have value ";
M[1][50]="Attention please. Uncorrect format in the field\n";
M[1][51]="\n"+"You can also use following codes\n";
M[1][52]="different from ";



tip=new Array(); 
tip['x']=tip['n']=x; 
tip['d']=d; 
tip['h']=h; 
tip['g']=g; 
tip['s']=s; 
tip['i']=i; 
tip['b']=b; 
tip['t']=t; 
tip['r']=r; 
tip['f']=f; 
tip['c']=c; 
tip['k']=k; 
tip['v']=v; 



num=new Array(); 
num['xp']=is_real_not_negative; 
num['xn']=is_real_not_positive; 
num['xa']=is_real; 
num['np']=is_nat; 
num['nn']=is_integer_not_positive; 
num['na']=is_integer; 



z=new Array(); 
z[1]=z[6]=z[9]=z[17]=z[25]='Y'; 
z[2]=z[16]=z[18]=z[24]='M'; 
z[4]=z[5]=z[7]=z[8]=z[10]=z[22]='D'; 
z[11]=z[12]=z[14]=z[19]=z[20]=z[21]=z[23]=z[26]=z[27]=z[28]=z[29]=z[35]=z[37]=''; 
z[15]=z[30]='H'; 



function f(tau) { 




var err, T, tL, N, val;
err=37; 
spf=tau.split('###'); 
tL=spf[0].charAt(1); 
N=spf[1]; 

switch (tL) {

case 'd': 
if (is_empty_date(N)) {
clear_date(N); 
return 0; 
} 
break; 

case 'h': 
if (is_empty_hour(N)) {
clear_hour(N); 
return 0; 
} 
break; 

case 'x': 
if (!el[N].value) {return 0} 
break; 

case 'n': 
if (!el[N].value) {return 0} 
break; 

case 'g': 
if (!el[N].value) {return 0} 
break; 

case 'v': 

T='r'; 

if (el[N].type) {

T=el[N].type.charAt(0); 
} 

switch (T) {

case 't': 
val=el[N].value; 
break; 

case 's': 
val=selval(N); 
break; 

case 'r': 
val=radiovalue(N); 
err=38; 
break; 

} 

if (!val) {return 0} 
break; 

} 



tau1=tau.substring(1,tau.length); 
err=tip[tL](tau1); 
if (err) {return err} 
return 0; 
} 



function x(tau) {



var v, tL, t2, L;
spx=tau.split('###'); 
L=spx[0].length; 
tL=spx[0].substring(0,L-2); 
t2=spx[0].substring(L-2,L); 
v=(el[spx[1]].value).toUpperCase(); 
if (num[tL](v)||is_gc(t2,v)){return 0} 
if (is_gc(15,v)) {return 23} 
else {
return numerr[tL]; 
} 

return 0; 
} 



function g(tau) { 




var err, nome, tipo, min, max, val;
tau1=tau.substring(1,tau.length); 
err=x(tau1); 
if (err) {return err} 

spg=tau.split('###'); 
tipo=spg[0]; 
nome=spg[1]; 
val=(el[nome].value).toUpperCase(); 
if (is_gc(15,val)) {return 0} 

spg1=spg[2].split('#'); 
min=spg1[0]; 
max=spg1[1]; 
return check_range(val,min,max); 
} 



function v(tau) { 






var tL, t2, err, N, TH, desc, U, V, Y, T, L;


spv=tau.split('###'); 
tL=spv[0].charAt(0); 
L=spv[0].length; 
t2=spv[0].substring(L-2,L); 
N=spv[1]; 
spv2=spv[2].split('#'); 
Y=spv2[0]; 
V=spv2[1].toUpperCase();  
err=37; 
TH='r'; 
if (el[N].type) {

TH=el[N].type.charAt(0); 
} 

if (TH=='t'||TH=='h') {
U=el[N].value.toString().toUpperCase(); 
} 

if (TH=='s') {
U=selval(N).toUpperCase(); 
} 

if (TH=='r') {
U=radiovalue(N); 
if (U==null) {U=''} 
else {U=U.toUpperCase()} 
err=38; 
} 

T=(U==V&&Y=='=')||(U!=V&&Y=='!')||is_gc(t2,U); 
if (T) {return 0} 
else {return err}; 
} 



function k(tau) { 






var E;
spk=tau.split('###'); 
spk1=spk[2].split('$$$'); 
tau=spk1[0].replace(/&&&/g,'###'); 

E=tip[tau.charAt(0)](tau); 
if (!E) {
tau=spk[0]+'###'+spk[1]+'###'+spk1[1]; 
tau=tau.substring(1,tau.length); 
E=tip[tau.charAt(0)](tau); 
if (E) {return E} 
} 
return 0; 
} 



function d(tau) {



var dd, mm, yy, err, tn, L;
spd=tau.split('###'); 
if (is_empty_date(spd[1])) {return 8} 
dd=(el[spd[1]+'D'].value).toUpperCase(); 
mm=(el[spd[1]+'M'].value).toUpperCase(); 
yy=(el[spd[1]+'Y'].value).toUpperCase(); 
if (!yy) {return 17} 
L=spd[0].length; 
tn=spd[0].substring(L-2,L); 
if (!is_nat(yy)&&!is_gc(tn,yy)) {return 25} 
if (yy=='CONT') {
el[spd[1]+'D'].value=''; 
el[spd[1]+'M'].value=''; 
if (el[spd[1]] && el[spd[1]+'RC']) {
hidden_date(mm,dd,yy,spd[1]) 
} 
return 0; 
} 


if (!dd) {return 10} 
if (!mm) {return 18} 
if (!is_nat(dd)&&!is_gc(tn,dd)){return 22} 
if (!is_nat(mm)&&!is_gc(tn,mm)){return 24} 



if (is_nat(dd)&&is_nat(mm)&&is_nat(yy)) {
err=check_date(dd,mm,yy) 
if (err) {return err} 
} 
else {
if (is_nat(dd)) {if (dd<1||dd>31) {return 5}} 
if (is_nat(mm)) {if (mm<1||mm>12) {return 2}} 
if (is_nat(yy)) {if ((yy<1900||yy>2050) && (dd!=9 && mm!=9 && yy!=9999)) {return 6}} 
} 


if (el[spd[1]] || el[spd[1]+'RC']) {
hidden_date(mm,dd,yy,spd[1]) 
} 
return 0; 
} 



function h(tau) {



var mm, hh, t2, err, tn, L;
sph=tau.split('###'); 
if (is_empty_hour(sph[1])) {return 30} 
mm=(el[sph[1]+'M'].value).toUpperCase(); 
hh=(el[sph[1]+'H'].value).toUpperCase(); 
L=sph[0].length; 
tn=sph[0].substring(L-2,L); 
if (!is_nat(mm)&&!is_gc(tn,mm)) {return 16} 
if (!is_nat(hh)&&!is_gc(tn,hh)) {return 15} 


if (is_nat(hh)&&is_nat(mm)) {
err=check_hour(mm,hh) 
if (err) {return err} 
} 
else {
if (is_nat(hh)) {if (hh<0||hh>23) {return 15}} 
if (is_nat(mm)) {if (mm<0||mm>59) {return 16}} 
} 


if (el[sph[1]] || el[sph[1]+'RC']) {
hidden_hour(hh,mm,sph[1]) 
} 
return 0; 
} 



function s(tau) { 





sp3=tau.split('###'); 
if (sp3[0]=='si'&&el[sp3[1]].selectedIndex>0){return 0} 
if (sp3[0]=='sv' && selval(sp3[1])) {return 0} 
if (sp3[0]=='st' && seltext(sp3[1])) {return 0} 
return 11; 
} 



function r(tau) {




var  N, I;
spr=tau.split('###'); 
N=el[spr[1]].length; 
for (I=0;I<N;I++) {
if (el[spr[1]][I].checked){return 0} 
} 
return 13; 
} 



function c(tau) {



spc=tau.split('###'); 
if (el[spc[1]].checked) {return 0} 
return 3 
} 



function t(tau) {



sp3=tau.split('###'); 
if (el[sp3[1]].value) {return 0} else {return 20} 
} 



function b(tau) {



var jst, check;
spb=tau.split('###'); 
jst=el[spb[1]].type; 
if (jst=='text'||jst=='textarea') {
if (!el[spb[1]].value) {return 0} else {return 35} 
} 

if (jst=='checkbox') {
if (el[spb[1]].checked) {return 36} 
return 0; 
} 

} 



function i(tau) {



sp3=tau.split('###'); 
return contr_iniz((el[sp3[1]].value).toUpperCase()); 
} 



function is_car_perm(A,C) {




var I, P;
if (!A.length) {return false} 
for (I=0;I<A.length;I++) {
P=C.indexOf(A.charAt(I)); 
if (P==-1) {return false} 
} 
return true 
} 



function is_gc(t2,v) {





var A, B, V, T;
V=v.toUpperCase(); 
if (!C[V]) {return false} 
A=Math.pow(2,C[V]); 
B=A/2; 
T=(t2%A)>=B; 
return T; 
} 



function check_date(DD,MM,YYYY) {




var f4, f400, f100, D, M, Y;
D=Math.floor(DD); 
M=Math.floor(MM); 
Y=Math.floor(YYYY); 
if (M<1||M>12) {return 2} 
if (D<1||D>31) {return 5} 
if ((Y<1900||Y>2050) && (D!=9 && M!=9 && Y!=9999)) {return 6} 
if ((M==4||M==6||M==9||M==11)&&(D==31)) {return 7} 
if (M==2) {
if (D>29) {return 7} 
if (D==29) {
f4=Y%4; 
f400=Y%400; 
f100=Y%100; 

if (!((!f4&&f100)||!f400)) {return 9} 
} 
} 
return 0; 
} 



function is_nat(val) {



if (val.toString()=='') {return false}  
if (!isFinite(val)) {return false} 
if ( (val-0)<0 ) {return false} 

return ((val-0)==Math.floor(val)); 
} 



function is_integer_not_positive(val) {



if (val.toString()=='') {return false}  
if (!isFinite(val)) {return false} 
if ( (val-0)>0 ) {return false} 

return ((val-0)==Math.floor(val)); 
} 



function is_integer(val) {




if (val.toString()=='') {return false}  
if (!isFinite(val)) {return false} 

return ((val-0)==Math.floor(val)); 
} 



function is_real(val) {




if (val.toString()=='') {return false}  
return isFinite(val); 
} 



function is_real_not_negative(val) {



if (val.toString()=='') {return false}  
if (!isFinite(val)) {return false} 
return ((val-0)>=0); 
} 



function is_real_not_positive(val) {



if (val.toString()=='') {return false}  
if (!isFinite(val)) {return false} 
return ((val-0)<=0); 
} 



function check_hour(mm,hh) {
if (mm<0 || mm>59) {return 16} 
if (hh<0 || hh>23) {return 15} 
return 0; 
} 



function contr_iniz(val) {




var L, alf;
alf="QWERTYUIOPASDFGHJKLZXCVBNM"; 
L=val.length; 
if (L!=3 && L!=2) {return 14} 
if (L==2&&!is_car_perm(val,alf)) {return 14} 
if (L==3) {
if (!is_car_perm(val.charAt(0),alf)) {return 14} 
if (!is_car_perm(val.charAt(2),alf)) {return 14} 
alf+="-"; 
if (!is_car_perm(val.charAt(1),alf)) {return 14} 
} 
return 0; 
} 



function contr(c1,spec) {


var j, err, tau;
trip=new Array(); 
_g['A']='ON'; 
_g['F']=0; 
_g['L']=0; 
if (spec) {

ridefine_pars(spec); 
} 

f=self.document.forms[_g['F']]; 
el=f.elements; 

c2=c1.substring(2,c1.length-2); 
trip=c2.split('>><<'); 
for (j=0;j<trip.length;j++) {
tau=trip[j]; 

if (!tip[tau.charAt(0)]) {
//alert('I dati verranno inviati');
return 0; 
} 
err=tip[tau.charAt(0)](tau);
if (err) {mes_er(err,tau);return err} 
} 
return 0; 
} 












































    
    var agt=navigator.userAgent.toLowerCase(); 

    
    
    var is_major = parseInt(navigator.appVersion); 
    var is_minor = parseFloat(navigator.appVersion); 

    
    
    var is_nav  = ((agt.indexOf('mozilla')!=-1) && (agt.indexOf('spoofer')==-1) 
                && (agt.indexOf('compatible') == -1) && (agt.indexOf('opera')==-1) 
                && (agt.indexOf('webtv')==-1)); 
    var is_nav2 = (is_nav && (is_major == 2)); 
    var is_nav3 = (is_nav && (is_major == 3)); 
    var is_nav4 = (is_nav && (is_major == 4)); 
    var is_nav4up = (is_nav && (is_major >= 4)); 
    var is_navonly      = (is_nav && ((agt.indexOf(";nav") != -1) || 
                          (agt.indexOf("; nav") != -1)) ); 
    var is_nav5 = (is_nav && (is_major == 5)); 
    var is_nav5up = (is_nav && (is_major >= 5)); 

    var is_ie   = (agt.indexOf("msie") != -1); 
    var is_ie3  = (is_ie && (is_major < 4)); 
    var is_ie4  = (is_ie && (is_major == 4) && (agt.indexOf("msie 5.0")==-1) ); 
    var is_ie4up  = (is_ie  && (is_major >= 4)); 
    var is_ie5  = (is_ie && (is_major == 4) && (agt.indexOf("msie 5.0")!=-1) ); 
    var is_ie5up  = (is_ie  && !is_ie3 && !is_ie4); 

    
    
    
    var is_aol   = (agt.indexOf("aol") != -1); 
    var is_aol3  = (is_aol && is_ie3); 
    var is_aol4  = (is_aol && is_ie4); 

    var is_opera = (agt.indexOf("opera") != -1); 
    var is_webtv = (agt.indexOf("webtv") != -1); 

    
    var is_js; 
    if (is_nav2 || is_ie3) is_js = 1.0 
    else if (is_nav3 || is_opera) is_js = 1.1 
    else if ((is_nav4 && (is_minor <= 4.05)) || is_ie4) is_js = 1.2 
    else if ((is_nav4 && (is_minor > 4.05)) || is_ie5) is_js = 1.3 
    else if (is_nav5) is_js = 1.4 
    
    
    
    
    
    else if (is_nav && (is_major > 5)) is_js = 1.4 
    else if (is_ie && (is_major > 5)) is_js = 1.3 
    
    else is_js = 0.0; 

    
    var is_win   = ( (agt.indexOf("win")!=-1) || (agt.indexOf("16bit")!=-1) );
    
    
    var is_win95 = ((agt.indexOf("win95")!=-1) || (agt.indexOf("windows 95")!=-1));

    
    var is_win16 = ((agt.indexOf("win16")!=-1) || 
               (agt.indexOf("16bit")!=-1) || (agt.indexOf("windows 3.1")!=-1) || 
               (agt.indexOf("windows 16-bit")!=-1) );  

    var is_win31 = ((agt.indexOf("windows 3.1")!=-1) || (agt.indexOf("win16")!=-1) ||
                    (agt.indexOf("windows 16-bit")!=-1));

    
    
    
    
    var is_win98 = ((agt.indexOf("win98")!=-1) || (agt.indexOf("windows 98")!=-1));
    var is_winnt = ((agt.indexOf("winnt")!=-1) || (agt.indexOf("windows nt")!=-1));
    var is_win32 = (is_win95 || is_winnt || is_win98 || 
                    ((is_major >= 4) && (navigator.platform == "Win32")) ||
                    (agt.indexOf("win32")!=-1) || (agt.indexOf("32bit")!=-1));

    var is_os2   = ((agt.indexOf("os/2")!=-1) || 
                    (navigator.appVersion.indexOf("OS/2")!=-1) ||   
                    (agt.indexOf("ibm-webexplorer")!=-1));

    var is_mac    = (agt.indexOf("mac")!=-1);
    var is_mac68k = (is_mac && ((agt.indexOf("68k")!=-1) || 
                               (agt.indexOf("68000")!=-1)));
    var is_macppc = (is_mac && ((agt.indexOf("ppc")!=-1) || 
                                (agt.indexOf("powerpc")!=-1)));


    

function radiovalue(N) {




var I, L;

L=el[N].length; 
for (I=0;I<L;I++) { 
if (el[N][I].checked){
return el[N][I].value; 
} 
} 
return null; 
} 



function selval(NS) {



var V, I;
I=el[NS].selectedIndex; 
if (I!=-1) {
V=el[NS].options[I].value; 
} 
else {V=''} 
return V; 
} 



function seltext(NS) {



var T, I;
I=el[NS].selectedIndex; 
if (I!=-1) {
T=el[NS].options[I].text; 
} 
else {T=''} 
return T; 
} 



function check_range(val,min,max) {



val-=0; 
min-=0; 
max-=0; 
if (val<min || val>max) {return 21} 
return 0 
} 



function mes_er(er,tau) {



var er2, TL, des, dec, T, L, N, tn, Y;

if (_g['A'].toUpperCase()=='OFF') {return er} 

sp3=tau.split('###'); 
T=sp3[0]; 
L=T.length; 
N=sp3[1]; 
des=sp3[2]; 
dec=''; 
if (L>=3) {
tn=T.substring(L-2,L); 
} 
else {tn=''} 
TL=T.charAt(0); 

if (TL=='k') {
T=T.substring(1,L); 
TL=T.charAt(0); 
D=des.split('$$$'); 
des=D[1]; 
} 

if (TL=='f') {
T=T.substring(1,L); 
TL=T.charAt(0); 
} 

if (TL=='g') {
D2=des.split('#'); 
des=D2[2]; 
} 

if (TL=='v') {
D2=des.split('#'); 
Y=D2[0]; 
dec=D2[2]+'\n'; 
if (Y=='!') {
dec=M[_g['L']][52]+dec; 
} 
des=D2[3]; 
} 

alert(M[_g['L']][50]+des+M[_g['L']][er]+dec+c_p(tn)); 
if (is_opera) {return err} 
if (er!=13&&er!=3&&er!=36&&er!=38) {
er2=er; 
if (er==8&&_g['L']==1) {er2=2} 
jst=el[N+z[er2]].type; 
if (jst!='hidden'){el[N+z[er2]].focus()}
} 
else {
if (er==3||er==36) {
jst=el[N].type; 
if (jst!='hidden'){el[N].focus()}
} 
else {
if (jst!='hidden'){el[N][0].focus()}
} 
} 

return er; 
} 



function hidden_date(M,D,Y,N) {







var V,V2,ds,ds2,ms,ms2,ys,ys2;
if (C[D]) {ds='01';ds2=D} 
else {ds2='OK'; 
if (D.length==1){ds='0'+D} 
else {ds=D+''} 
} 
if (C[M]) {ms='06';ms2=M} 
else {ms2='OK'; 
if (M.length==1){ms='0'+M} 
else {ms=M+''} 
} 
if (C[Y]) {ys='1777';ys2=Y} 
else {ys=Y+'';ys2='OK'} 
if (Y=='CONT') {ds='01';ms='06';ys='1666';ds2='CO';ms2='NT';ys2='IN'} 
V=ds+ms+ys; 
V2=ds2+ms2+ys2; 
el[N].value=V; 
el[N+'RC'].value=V2; 
return true; 
} 



function hidden_hour(H,M,N) {







var V,V2,hs,ms,hs2,ms2;

if (C[H]) {hs='12';hs2=H} 
else {hs2='OK'; 
if (H.length==1){hs='0'+H} 
else {hs=H+''} 
} 
if (C[M]) {ms='30';ms2=M} 
else {ms2='OK'; 
if (M.length==1){ms='0'+M} 
else {ms=M+''}  
} 
V=hs+ms; 
V2=hs2+ms2; 
el[N].value=V; 
el[N+'RC'].value=V2; 
return true; 
} 



function c_p(tn) {



var A, I;
A=''; 
if (!is_nat(tn)||tn=='00'||tn=='0') {return A} 
A=M[_g['L']][51]; 
if (is_gc(tn,'NA')) {A+='NA '} 
if (is_gc(tn,'NN')) {A+='NN '} 
if (is_gc(tn,'ND')) {A+='ND '} 
if (is_gc(tn,'NP')) {A+='NP '} 
if (is_gc(tn,'CONT')) {A+='CONT '} 
return A; 
} 



function is_empty_date(N) {



if (!el[N+'D'].value&&!el[N+'M'].value&&!el[N+'Y'].value) {
return true; 
} 
return false; 
} 



function clear_date(N) {




el[N+'D'].value=''; 
el[N+'M'].value=''; 
el[N+'Y'].value=''; 
if (el[N]) {
el[N].value=''; 
} 
if (el[N+'RC']) {
el[N+'RC'].value=''; 
} 
return true; 
} 



function is_empty_hour(N) {



if (!el[N+'H'].value&&!el[N+'M'].value) {
return true; 
} 
return false; 
} 



function clear_hour(N) {




el[N+'H'].value=''; 
el[N+'M'].value=''; 
if (el[N]) {
el[N].value=''; 
} 
if (el[N+'RC']) {
el[N+'RC'].value=''; 
} 
return true; 
} 



function ridefine_pars(S) {


var I;
sp=S.toUpperCase().split('&'); 
for (I=0;I<sp.length;I++) {
sp2=sp[I].split('='); 
_g[sp2[0]]=sp2[1]; 
} 
return true; 
} 


function is_hypernet_compliant() {



return ( (is_win&&(is_ie4up||is_nav4up) ) || (is_mac&&is_ie5up) );
} // **************************************************************** Fine funzione
