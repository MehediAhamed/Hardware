# from pyfirmata import Arduino
# import time

# board = Arduino("com5")

# looptimes= input("How many ti,es would you like to led blink?")

# print("Blinking" + looptimes +"times")

# for x in range(int (looptimes)):

#     board.digital[13].write(1)
#     time.sleep(0.2)
#     board.digital[13].write(0)
#     time.sleep(0.2)


import pyfirmata as pf
import time

r1= 4
r2= 2
rEna=5

l1=7
l2=8
lEna=9
pwm=1

board=pf.Arduino("com3")

# Analog Enable 
Enable_R=board.digital[rEna]
# Enable_R.mode= pf.PWM

Enable_L=board.digital[lEna]
# Enable_L.mode= pf.PWM

def zero():
    Enable_R.write(pwm)
    Enable_L.write(pwm)

    board.digital[r1].write(0)
    board.digital[r2].write(0)

    board.digital[l1].write(0)
    board.digital[l2].write(0)
    
    

def Forward():

    Enable_R.write(pwm)
    Enable_L.write(pwm)

    board.digital[r1].write(1)
    board.digital[r2].write(0)

    board.digital[l1].write(1)
    board.digital[l2].write(0)
   

    time.sleep(5)
    zero()

def Backward():

    Enable_R.write(pwm)
    Enable_L.write(pwm)

    board.digital[r1].write(0)
    board.digital[r2].write(1)

    board.digital[l1].write(0)
    board.digital[l2].write(1)
    
   

    time.sleep(5)
    zero()
   

while(True):
    ch=input("Give input:")
    if(ch=="a"):
        Forward()
    elif(ch=="d"):
        Backward()
    else:
        Forward()








