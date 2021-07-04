#include <ros/ros.h>
#include <tutorial_topic/Int32Stamped.h>
//グローバル変数の定義
static tutorial_topic::Int32Stamped g_number;

//Topicを受信すると呼ばれるコールバック関数
void onNumberSubscribed(const tutorial_topic::Int32Stamped &msg)
{
//受信したTopicをグローバル変数にコピー
 g_number = msg;
}

int main(int argc, char **argv)
{
 //ROSノードの初期化
 ros::init(argc, argv, "Subscriber");
 ros::NodeHandle nh;
 //SubscriberするTopicの設定&コールバック関数の登録
 ros::Subscriber sub = nh.subscribe("number", 10, onNumberSubscribed);
//ループ関数の設定
 ros::Rate loop_rate(1);
 //無限ループ
 while(ros::ok()){
 //コールバックキューの確認
 ros::spinOnce();
 //受信したTopicデータの表示
 ROS_INFO("Number :%d, Time : %1f", g_number.data, g_number.header.stamp.toSec());
//周期が1秒になるように待機
 loop_rate.sleep();
 }
 return 0;
}
