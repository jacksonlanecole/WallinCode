import sys
import os
import math

def formstring(array):
    s  = ""
    for v in array:
        s = s + str(v) + ","
    s = s[:-1]
    return s

def updateRunString(param, dx, dvx, dy, dvy):
    newparam = []
    for v in param.split(","):
        newparam.append(float(v))
    
    print "--------------------------"
    print param
    print newparam
    newparam[0]= newparam[0] + dx
    newparam[1]= newparam[1] + dy
    newparam[3] = newparam[3] + dvx
    newparam[4] = newparam[4] + dvy
    s = formstring(newparam)
    return s

def dorun(param, dx, dvx, dy, dvy):
    
    s = updateRunString(param, dx, dvx, dy, dvy)
    rs = "./mod_run " + s + " > d1"
    print "s = ", s
    print "dy = ", dy, dvy
    print "---"

    os.system(rs)
 #   print rs
 #   print newparam[0], newparam[3], dx, dvx


def readrun():
    f = open("d1","r")
    for ll in f:
        l = ll
    f.close()
    outparm = []
    for v in  l.strip().split():
        outparm.append(v)

    return outparm


def bisectY(paramS, dy, vyLower, vyUpper, yminOrbit):

    print "bisect y"
    print "inputs ", paramS
    print "inputs ", dy, vyLower, vyUpper, yminOrbit

    dorun(paramS, 0, 0, 0, 0)
    outparm= readrun()
    print "opL", outparm

    dvy = vyLower
    dorun(paramS, 0, 0, dy, dvy)
    outparm= readrun()
    print "opL", outparm
    ylower = outparm[3]  
    print "lowervy = ", vyLower, ylower

    dvy = vyUpper
    dorun(paramS, 0, 0, dy, dvy)
    outparm= readrun()
    print "opU", outparm
    yupper = outparm[3]  
    print "uppervy = ", vyUpper, yupper

    ytol = 0.001
    while (abs(float(vyUpper) - float(vyLower)) > ytol):
        vyMiddle = (vyLower + vyUpper)/2
        dvy = vyMiddle
        dorun(paramS, 0, 0, dy, dvy)
        outparm= readrun()
        ymiddle = outparm[3]
        print "op", outparm
        print "middleyv = ", vyMiddle, ymiddle

    
        print "deltaY = ", dy, dvy
        print "YYY = ", vyLower, vyMiddle, vyUpper, yminOrbit
        #print "param ", param[0], param[1], param[2]

        if math.copysign(1, float(yupper)) * math.copysign(1,float(ylower)) != -1:
            print "not bracketed-- error"
            exit()

        if math.copysign(1,float(yupper)) == math.copysign(1,float(ymiddle)):
            vyUpper = vyMiddle
        else:
            vyLower = vyMiddle
        
    dvy = vyMiddle


    dorun(paramS, 0, 0, dy, dvy)
    outparm= readrun()
    print outparm

    dosim(paramS, 0, 0, dy, dvy, "finalsimY")
    return dy, dvy



def bisectX(param, dx, vxLower, vxUpper, xminOrbit):

    print "bisect x"
    print "inputs ", param
    print "inputs ", dx, vxLower, vxUpper, xminOrbit

    # search for the differential velocity that matches the final position and the xminOrbit
    dvx = vxLower
    dorun(param, dx, dvx, 0, 0)
    outparm= readrun()
    xlower = outparm[2]

    dvx = vxUpper
    dorun(param, dx, dvx, 0, 0)
    outparm= readrun()
    xupper = outparm[2]

    xtol = 0.001
    xcurrent = xupper
    while (abs(float(vxUpper) - float(vxLower)) > xtol):
        vxMiddle = (vxLower + vxUpper)/2
        dvx = vxMiddle
        dorun(param, dx, dvx, 0, 0)
        outparm= readrun()
        xmiddle = outparm[2]
    
        print "XXX = ", vxLower, vxMiddle, vxUpper, xminOrbit
        
        if math.copysign(1, float(xupper)) * math.copysign(1,float(xlower)) != -1:
            print "not bracketed-- error"
            exit()

        if math.copysign(1,float(xupper)) == math.copysign(1,float(xmiddle)):
            vxUpper = vxMiddle
        else:
            vxLower = vxMiddle
        
    dvx = vxMiddle



    dorun(param, dx, dvx, 0, 0)
    outparm= readrun()
    print outparm

    dosim(param, dx, dvx, 0, 0, "finalsimX")
    return dy, dvy









#    print xtarget, xupper, xmiddle, xlower

def updateRunString(param, dx, dvx, dy, dvy):
    newparam = []
    for v in param.split(","):
        newparam.append(float(v))
    
    newparam[0]= newparam[0] + dx
    newparam[1]= newparam[1] + dy
    newparam[3] = newparam[3] + dvx
    newparam[4] = newparam[4] + dvy
    s = formstring(newparam)
    return s

def dosim(param, dx, dvx, dy, dvy, name):

    s = updateRunString(param, dx, dvx, dy, dvy)

#    newparam = []
#    for v in param:
#        newparam.append(v)
    
#    newparam[0]= newparam[0] + dx
#    newparam[1]= newparam[1] + dy
#    newparam[3] = newparam[3] + dvx
#    newparam[4] = newparam[4] + dvy
#    s = formstring(newparam)
    rs = "./basic_run " + s 
    os.system(rs)
    os.system("mv a.101 "+name)


def parmStringToFloats(paramS):
    paramF = []
    vv = paramS.split(",")
    for ii in range(len(vv)):
        paramF.append(float(vv[ii]))
    return paramF

def parmFloatToString(paramF):
    paramS = ""
    for ii in range(len(paramF)):
        ff = paramF[ii]
        paramS = paramS + str(ff) + ","
    paramS = paramS.strip()
    return paramS

def parseInputArguments():

#    param = [ -0.12623,0.35028,3.35743,-0.12979,0.55971,4.02072,0.78258,0.98072,0.30541,0.41196,152.77952,195.62801,147.22542,138.42519,0.3,0.3,0.0,0.0,0.0,0.0,0.0,0.0,0.72115,0,0,45.47487,-0.49999,0.07399,0.0,0.0,0.0,0.0,0.0,0.0 ]
    paramS = "-0.12623,0.35028,3.35743,-0.12979,0.55971,4.02072,0.78258,0.98072,0.30541,0.41196,152.77952,195.62801,147.22542,138.42519,0.3,0.3,0.0,0.0,0.0,0.0,0.0,0.0,0.72115,0,0,45.47487,-0.49999,0.07399,0.0,0.0,0.0,0.0,0.0,0.0"

    xflag = 0
    yflag = 0
    xgoal = 0
    ygoal = 0

    for p in range(1, len(sys.argv)):
        ss = sys.argv[p]

        if ss == "-p":
            s1 = sys.argv[p+1]
            paramS = s1
#            vv = s1.split(",")
#            for ii in range(len(vv)):
#                param[ii] = float(vv[ii])


        if ss == "-x":
            xgoal = float(sys.argv[p+1])
            xflag = 1

        if ss == "-y":
            ygoal = float(sys.argv[p+1])
            yflag = 1


    if xflag == 0:
        xgoal = param[0]

    if yflag == 0:
        ygoal = param[0]
    
    return paramS, xgoal, ygoal



# start the main program

paramS, xgoal, ygoal  = parseInputArguments()
paramF =  parmStringToFloats(paramS)
print "current xy = ", paramF[0], paramF[1]
print "goal xy = ", xgoal, ygoal

dx = 0
dy = 0
dvx =0
dvy = 0
#dosim(paramS, dx, dvx, dy, dvy, "initialsim")
dorun(paramS, dx, dvx, dy, dvy)

initialoutparm = readrun()
print initialoutparm
print "------------"

# this is the closest center of mass (xy) position for the simulation 
xminOrbit = initialoutparm[2]
yminOrbit = initialoutparm[3]

xtarget = paramF[0]
ytarget = paramF[1]





dx = (xgoal - xtarget)
vxLower = -abs(4.5*dx)
vxUpper =  abs(4.5*dx)

dy = (ygoal - ytarget)
vyLower = -abs(4.5*dy)
vyUpper =  abs(4.5*dy)
vyLower = -0.2
vyUpper = 0.2


print "DY" , dy
dorun(paramS, 0, 0, dy, 0)
outparm = readrun()
print outparm
print 


print "DY" , dy
dorun(paramS, 0, 0, dy, dy/0.788)
outparm = readrun()
print outparm

paramS = updateRunString(paramS, dx, dx/0.788, dy, dy/0.788)
dosim(paramS, 0, 0, 0, 0, "finalsimS")

print 

exit()

print "current x", xtarget, xgoal, dx, vxLower, vxUpper
print "current y", ytarget, ygoal, dy, vyLower, vyUpper
print "XXXXXXXXXXXXXXXXXXXX"

#bisectX(param, dx, vxLower, vxUpper, 0, vyLower, vyUpper, xminOrbit, yminOrbit)
#bisectX(param, dx, vxLower, vxUpper, dy, vyLower, vyUpper, xminOrbit, yminOrbit)
#bisectY(param, dx, vxLower, vxUpper, dy, vyLower, vyUpper, xminOrbit, yminOrbit)


#dx, dvx = bisectX(param, dx, vxLower, vxUpper, dy, vyLower, vyUpper, xminOrbit, yminOrbit)

dy, dvy = bisectY(paramS, dy, vyLower, vyUpper, yminOrbit)
paramS = updateRunString(paramS, 0, 0, dy, dvy)
dosim(paramS, 0, 0, 0, 0, "finalsimY1")

#dx, dvx = bisectX(paramS, dx, vxLower, vxUpper, xminOrbit)
#paramS = updateRunString(paramS, dx, dvx, 0, 0)
#dosim(paramS, 0, 0, 0, 0, "finalsimX1")



