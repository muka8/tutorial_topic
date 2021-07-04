#include <ros/ros.h>
#include <tutorial_topic/Int32Stamped.h>

//Topicを受信すると呼ばれるコールバック関数
void onNumberSubscribed(const tutorial_topic::Int32Stamped &msg)
{
    //受信したデータを表示
    ROS_INFO("I heard: [%d] ,Timestamp: [%1f]", msg.data, msg.header.stamp.toSec());
}
 int main(int argc, char **argv)
{
    //ROSノードの初期化
    ros::init(argc, argv, "subscriber");
    ros::NodeHandle nh;
    //SubcribeするTopicの設定&コールバック関数の登録
    ros::Subscriber sub = nh.subscribe("number", 10, onNumberSubscribed);
    //コールバックを待機
    ros::spin();
    return 0;
}
