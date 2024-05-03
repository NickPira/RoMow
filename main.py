import GUI
import sendToArd as send
import start


height, width = GUI.getDims()
turnOn = start.go()

send(turnOn)
send(height)
send(width)