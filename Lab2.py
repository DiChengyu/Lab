import rospy
from std_msgs.msg import Float64MultiArray

kp = 1.2
ki = 0.35


def computepid(input):
    i = 0
    previousTime = 0
    currentTime = i;               
    elapsedTime = currentTime - previousTime;      

    error = input;                                
    cumError = error * elapsedTime;                 
 
    out = kp*error + ki*cumError;                              
                               
    previousTime = currentTime
    return out

   

def talker():
    pub = rospy.Publisher('youbot_base/joints_vel_controller/command', Float64MultiArray, queue_size=10)
    rospy.init_node('pubListener', anonymous=False)
    rate = rospy.Rate(10) # 10hz

    R = 0.1
    vx = 0
    vy = 0
    ax = 0.025
    ay = 0.025
    w = 1
    i = 0
    
    global f1, f2, f3, f4
    f1=-(1/R) * (vx+vy-w*(ax+ay))
    f2=(1/R) * (-vx+vy+w*(ax+ay))
    f3=-(1/R) * (-vx+vy-w*(ax+ay))
    f4=(1/R) * (vx+vy+w*(ax+ay))

    vx1 = (1/R)*(f1+f2-f3-f4)
    vy1 = (1/R)*(f1-f2+f3-f4)
    
    global pid_vx, pid_vy

    
    msg = Float64MultiArray() 
    
    while i <=250:
        msg.data = [f1,-f2,f3,-f4]

        pid_vx = computepid(vx1)
        pid_vy = computepid(vy1)
        vx = vx1-pid_vx
        vy = vy1-pid_vy

        f1=-(1/R) * (vx+vy-w*(ax+ay))
        f2=(1/R) * (-vx+vy+w*(ax+ay))
        f3=-(1/R) * (-vx+vy-w*(ax+ay))
        f4=(1/R) * (vx+vy+w*(ax+ay))
        msg.data = [f1,-f2,f3,-f4]

        rospy.loginfo(msg.data)
        rospy.loginfo(i)
        pub.publish(msg)
        rate.sleep()
        i=i+1
        
    while i>250 and i <=500:
        msg.data = [-f1,f2,-f3,f4]

        pid_vx = computepid(vx1)
        pid_vy = computepid(vy1)
        vx = vx1-pid_vx
        vy = vy1-pid_vy
        f1=-(1/R) * (vx+vy-w*(ax+ay))
        f2=(1/R) * (-vx+vy+w*(ax+ay))
        f3=-(1/R) * (-vx+vy-w*(ax+ay))
        f4=(1/R) * (vx+vy+w*(ax+ay))
        msg.data = [f1,f2,-f3,-f4]
            
        rospy.loginfo(msg.data)
        rospy.loginfo(i)
        pub.publish(msg)
        rate.sleep()
        i=i+1
        
    while i>500 and i <=750:
        msg.data = [-f1,f2,-f3,f4]

        pid_vx = computepid(vx1)
        pid_vy = computepid(vy1)
        vx = vx1-pid_vx
        vy = vy1-pid_vy
        f1=-(1/R) * (vx+vy-w*(ax+ay))
        f2=(1/R) * (-vx+vy+w*(ax+ay))
        f3=-(1/R) * (-vx+vy-w*(ax+ay))
        f4=(1/R) * (vx+vy+w*(ax+ay))
        msg.data = [-f1,f2,-f3,f4]

            
        rospy.loginfo(msg.data)
        rospy.loginfo(i)
        pub.publish(msg)
        rate.sleep()
        i=i+1
        
    while i>750 and i <=1000:
        msg.data = [-f1,-f2,f3,f4]

        pid_vx = computepid(vx1)
        pid_vy = computepid(vy1)
        vx = vx1-pid_vx
        vy = vy1-pid_vy
        f1=-(1/R) * (vx+vy-w*(ax+ay))
        f2=(1/R) * (-vx+vy+w*(ax+ay))
        f3=-(1/R) * (-vx+vy-w*(ax+ay))
        f4=(1/R) * (vx+vy+w*(ax+ay))
            
        rospy.loginfo(msg.data)
        rospy.loginfo(i)
        pub.publish(msg)
        rate.sleep()
        i=i+1
    while i == 1001:
        msg.data = [0, 0, 0, 0]
                
        rospy.loginfo(msg.data)
        rospy.loginfo(i)
        pub.publish(msg)
        rate.sleep()
        i=i+1
    while i == 1001:
        break


    #keeps python from exiting until this node is stopped
    #rospy.spin()
if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
