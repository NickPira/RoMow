def wayGen(width, height):
    waypoints = {}   
    BLADELEN = 1
    BOTLEN = 1.5
    pointsOnY = height
    pointsOnX = width/BOTLEN
    count = 0
    maxX = 0
    for i in range(int(pointsOnY)) :
        for j in range(int(pointsOnX)):
            if(i%2 == 1):
                waypoints[count] = [maxX, (i+1)*BLADELEN]
                maxX-=BOTLEN
            else:
                waypoints[count] = [(j+1)*BOTLEN, (i+1)*BLADELEN]
                if((j+1)*BOTLEN > maxX):
                    maxX = (j+1)*BOTLEN   
            count+=1


    return waypoints



