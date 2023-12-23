import rospy
from std_msgs.msg import Float64MultiArray

def talker():
    pub = rospy.Publisher('youbot_base/joints_vel_controller/command', Float64MultiArray, queue_size=10)
    rospy.init_node('pubListener', anonymous=False)
    rate = rospy.Rate(10) # 10hz

    R = 0.1
    vx = 0.05
    vy = 0
    ax = 0.2
    ay = 0.15
    w = 0
    i = 0

    global f1, f2, f3, f4
    f1=(1/R) * (vx+vy-w*(ax+ay))
    f2=(1/R) * (-vx+vy+w*(ax+ay))
    f3=-(1/R) * (-vx+vy-w*(ax+ay))
    f4=-(1/R) * (vx+vy+w*(ax+ay))

    msg = Float64MultiArray() 
    
    while i <=250:
        msg.data = [f1,f2,f3,f4]
                
        rospy.loginfo(msg.data)
        rospy.loginfo(i)
        pub.publish(msg)
        rate.sleep()
        i=i+1
    while i>250 and i <=500:
        msg.data = [f1,-f2,-f3,f4]
                
        rospy.loginfo(msg.data)
        rospy.loginfo(i)
        pub.publish(msg)
        rate.sleep()
        i=i+1
    while i>500 and i <=750:
        msg.data = [-f1,-f2,-f3,-f4]
                
        rospy.loginfo(msg.data)
        rospy.loginfo(i)
        pub.publish(msg)
        rate.sleep()
        i=i+1
    while i>750 and i <=1000:
        msg.data = [-f1,f2,f3,-f4]
                
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
