import ROOT
from ROOT import TF2, TCanvas

theta = 0.0
lam = 2.0
gamma = 0.5
psi = 0 
sigma =0.785

xp = f"x*cos({theta})+y*sin({theta})"
yp = f"-x*sin({theta})+y*cos({theta})"
fun_gf_real = f"exp(-(({xp})**2+{gamma}**2*({yp})**2)/(2*{sigma}**2))*cos(6.28*({xp})/{lam} + {psi})"

print(fun_gf_real)
f_real = TF2("f_real", fun_gf_real, -10, 10, -10, 10)
c0 = TCanvas()
f_real.Draw("surf2")

